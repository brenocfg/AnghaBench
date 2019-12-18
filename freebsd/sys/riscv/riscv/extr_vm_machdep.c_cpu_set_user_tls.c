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
struct TYPE_2__ {scalar_t__ tf_tp; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ TP_OFFSET ; 
 uintptr_t VM_MAXUSER_ADDRESS ; 

int
cpu_set_user_tls(struct thread *td, void *tls_base)
{

	if ((uintptr_t)tls_base >= VM_MAXUSER_ADDRESS)
		return (EINVAL);

	/*
	 * The user TLS is set by modifying the trapframe's tp value, which
	 * will be restored when returning to userspace.
	 */
	td->td_frame->tf_tp = (register_t)tls_base + TP_OFFSET;

	return (0);
}