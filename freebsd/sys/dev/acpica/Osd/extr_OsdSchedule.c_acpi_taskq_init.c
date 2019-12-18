#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  at_task; int /*<<< orphan*/  at_flag; } ;

/* Variables and functions */
 int ACPI_TASK_ENQUEUED ; 
 int ACPI_TASK_USED ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  PWAIT ; 
 int acpi_max_tasks ; 
 int /*<<< orphan*/  acpi_max_threads ; 
 scalar_t__ acpi_task_count ; 
 int /*<<< orphan*/  acpi_taskq ; 
 int acpi_taskq_started ; 
 TYPE_1__* acpi_tasks ; 
 scalar_t__ atomic_cmpset_int (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  printf (char*,scalar_t__) ; 
 int /*<<< orphan*/  taskqueue_create_fast (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_start_threads (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  taskqueue_thread_enqueue ; 

__attribute__((used)) static void
acpi_taskq_init(void *arg)
{
    int i;

    acpi_taskq = taskqueue_create_fast("acpi_task", M_NOWAIT,
	&taskqueue_thread_enqueue, &acpi_taskq);
    taskqueue_start_threads(&acpi_taskq, acpi_max_threads, PWAIT, "acpi_task");
    if (acpi_task_count > 0) {
	if (bootverbose)
	    printf("AcpiOsExecute: enqueue %d pending tasks\n",
		acpi_task_count);
	for (i = 0; i < acpi_max_tasks; i++)
	    if (atomic_cmpset_int(&acpi_tasks[i].at_flag, ACPI_TASK_USED,
		ACPI_TASK_USED | ACPI_TASK_ENQUEUED))
		taskqueue_enqueue(acpi_taskq, &acpi_tasks[i].at_task);
    }
    acpi_taskq_started = 1;
}