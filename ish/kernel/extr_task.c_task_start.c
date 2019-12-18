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
struct task {int /*<<< orphan*/  thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct task*) ; 
 int /*<<< orphan*/  task_run ; 
 int /*<<< orphan*/  task_thread_attr ; 

void task_start(struct task *task) {
    if (pthread_create(&task->thread, &task_thread_attr, task_run, task) < 0)
        die("could not create thread");
}