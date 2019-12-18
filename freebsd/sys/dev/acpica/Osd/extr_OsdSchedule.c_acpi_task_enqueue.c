#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct acpi_task_ctx {int at_flag; int /*<<< orphan*/  at_task; void* at_context; int /*<<< orphan*/  at_function; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_OSD_EXEC_CALLBACK ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_TASK_ENQUEUED ; 
 int ACPI_TASK_FREE ; 
 int ACPI_TASK_USED ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct acpi_task_ctx*) ; 
 int acpi_max_tasks ; 
 int /*<<< orphan*/  acpi_task_count ; 
 int /*<<< orphan*/  acpi_task_execute ; 
 int /*<<< orphan*/  acpi_taskq ; 
 scalar_t__ acpi_taskq_started ; 
 struct acpi_task_ctx* acpi_tasks ; 
 int acpi_tasks_hiwater ; 
 int /*<<< orphan*/  atomic_cmpset_int (int*,int,int) ; 
 int /*<<< orphan*/  atomic_set_int (int*,int /*<<< orphan*/ ) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ACPI_STATUS
acpi_task_enqueue(int priority, ACPI_OSD_EXEC_CALLBACK Function, void *Context)
{
    struct acpi_task_ctx *at;
    int i;

    for (at = NULL, i = 0; i < acpi_max_tasks; i++)
	if (atomic_cmpset_int(&acpi_tasks[i].at_flag, ACPI_TASK_FREE,
	    ACPI_TASK_USED)) {
	    at = &acpi_tasks[i];
	    acpi_task_count++;
	    break;
	}

    if (i > acpi_tasks_hiwater)
	atomic_cmpset_int(&acpi_tasks_hiwater, acpi_tasks_hiwater, i);

    if (at == NULL) {
	printf("AcpiOsExecute: failed to enqueue task, consider increasing "
	    "the debug.acpi.max_tasks tunable\n");
	return (AE_NO_MEMORY);
    }

    TASK_INIT(&at->at_task, priority, acpi_task_execute, at);
    at->at_function = Function;
    at->at_context = Context;

    /*
     * If the task queue is ready, enqueue it now.
     */
    if (acpi_taskq_started) {
	atomic_set_int(&at->at_flag, ACPI_TASK_ENQUEUED);
	taskqueue_enqueue(acpi_taskq, &at->at_task);
	return (AE_OK);
    }
    if (bootverbose)
	printf("AcpiOsExecute: task queue not started\n");

    return (AE_OK);
}