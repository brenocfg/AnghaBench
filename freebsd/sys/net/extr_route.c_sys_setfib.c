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
struct thread {TYPE_1__* td_proc; } ;
struct setfib_args {scalar_t__ fibnum; } ;
struct TYPE_2__ {scalar_t__ p_fibnum; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ rt_numfibs ; 

int
sys_setfib(struct thread *td, struct setfib_args *uap)
{
	if (uap->fibnum < 0 || uap->fibnum >= rt_numfibs)
		return EINVAL;
	td->td_proc->p_fibnum = uap->fibnum;
	return (0);
}