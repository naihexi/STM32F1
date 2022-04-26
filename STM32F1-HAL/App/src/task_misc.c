#include "FreeRTOS.h"
#include "task_manage.h"
#include "misc.h"
#include "button.h"

//#define TASK_MISC_NAME "taskMisc"
//#define TASK_MISC_STACK ( configMINIMAL_STACK_SIZE * 2 )
//#define TASK_MISC_PRIORITY ( tskIDLE_PRIORITY + 2 )

static void task_misc(void* param);

taskDef_t gtTaskMisc = {
    .task_id = TASK_ID_MISC,
    .task_name = "taskMisc",
    .stack_depth = 32,
    .task_handle = NULL,
    .task_priority = 1,
    .task_func = task_misc,
};

void task_misc_init(void)
{
    task_create(&gtTaskMisc);
}

void task_misc_deInit(void)
{
	vTaskDelete(gtTaskMisc.task_handle);
}

extern void flex_btn_init(void);
extern void flex_button_event_handler(void);
static void task_misc(void* param)
{
	UNUSED(param);
    button_init();
    flex_btn_init();

	while (1)
	{
        flex_button_event_handler();
		vTaskDelay(2000/portTICK_RATE_MS);
	}
}