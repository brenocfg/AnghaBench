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
 int /*<<< orphan*/  MPASS (int) ; 
 long TASK_INTERRUPTIBLE ; 
 long TASK_NORMAL ; 
 int linux_signal_pending (struct task_struct*) ; 

bool
linux_signal_pending_state(long state, struct task_struct *task)
{

	MPASS((state & ~TASK_NORMAL) == 0);

	if ((state & TASK_INTERRUPTIBLE) == 0)
		return (false);
	return (linux_signal_pending(task));
}