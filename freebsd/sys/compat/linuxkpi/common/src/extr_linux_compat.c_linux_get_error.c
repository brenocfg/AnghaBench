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
 int EINTR ; 
 int ERESTART ; 
 int ERESTARTSYS ; 
 int linux_schedule_get_interrupt_value (struct task_struct*) ; 

__attribute__((used)) static int
linux_get_error(struct task_struct *task, int error)
{
	/* check for signal type interrupt code */
	if (error == EINTR || error == ERESTARTSYS || error == ERESTART) {
		error = -linux_schedule_get_interrupt_value(task);
		if (error == 0)
			error = EINTR;
	}
	return (error);
}