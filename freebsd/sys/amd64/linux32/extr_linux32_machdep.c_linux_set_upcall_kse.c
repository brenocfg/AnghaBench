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
struct thread {TYPE_1__* td_frame; } ;
typedef  scalar_t__ register_t ;
struct TYPE_2__ {scalar_t__ tf_rax; scalar_t__ tf_rsp; } ;

/* Variables and functions */

int
linux_set_upcall_kse(struct thread *td, register_t stack)
{

	if (stack)
		td->td_frame->tf_rsp = stack;

	/*
	 * The newly created Linux thread returns
	 * to the user space by the same path that a parent do.
	 */
	td->td_frame->tf_rax = 0;
	return (0);
}