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
struct TYPE_2__ {int /*<<< orphan*/  cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_run (int /*<<< orphan*/ *) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  task_run_hook () ; 

__attribute__((used)) static void *task_run(void *task) {
    current = task;
    if (task_run_hook)
        task_run_hook();
    else
        cpu_run(&current->cpu);
    die("task_run returned"); // above function call should never return
}