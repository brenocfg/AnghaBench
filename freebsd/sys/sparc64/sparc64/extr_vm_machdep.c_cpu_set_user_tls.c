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
typedef  scalar_t__ uint64_t ;
struct thread {TYPE_1__* td_frame; } ;
struct TYPE_2__ {scalar_t__* tf_global; } ;

/* Variables and functions */
 struct thread* curthread ; 
 int /*<<< orphan*/  flushw () ; 

int
cpu_set_user_tls(struct thread *td, void *tls_base)
{

	if (td == curthread)
		flushw();
	td->td_frame->tf_global[7] = (uint64_t)tls_base;
	return (0);
}