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
struct rw_semaphore {int /*<<< orphan*/  sx; } ;

/* Variables and functions */
 int EINTR ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  linux_schedule_save_interrupt_value (int /*<<< orphan*/ ,int) ; 
 int sx_xlock_sig (int /*<<< orphan*/ *) ; 

int
linux_down_write_killable(struct rw_semaphore *rw)
{
	int error;

	error = -sx_xlock_sig(&rw->sx);
	if (error != 0) {
		linux_schedule_save_interrupt_value(current, error);
		error = -EINTR;
	}
	return (error);
}