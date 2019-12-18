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
struct task_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  THREAD_NOTIFY_EXIT ; 
 int /*<<< orphan*/  task_thread_info (struct task_struct*) ; 
 int /*<<< orphan*/  thread_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void exit_thread(struct task_struct *tsk)
{
	thread_notify(THREAD_NOTIFY_EXIT, task_thread_info(tsk));
}