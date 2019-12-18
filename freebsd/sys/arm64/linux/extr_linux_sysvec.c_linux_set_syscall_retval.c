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
struct thread {TYPE_1__* td_frame; int /*<<< orphan*/ * td_retval; } ;
struct TYPE_2__ {int /*<<< orphan*/ * tf_x; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_set_syscall_retval (struct thread*,int) ; 

__attribute__((used)) static void
linux_set_syscall_retval(struct thread *td, int error)
{

	td->td_retval[1] = td->td_frame->tf_x[1];
	cpu_set_syscall_retval(td, error);
}