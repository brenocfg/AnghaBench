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
struct task {int /*<<< orphan*/  pid; int /*<<< orphan*/  siblings; } ;
struct TYPE_2__ {int /*<<< orphan*/ * task; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct task*) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *) ; 
 TYPE_1__* pid_get (int /*<<< orphan*/ ) ; 

void task_destroy(struct task *task) {
    list_remove(&task->siblings);
    pid_get(task->pid)->task = NULL;
    free(task);
}