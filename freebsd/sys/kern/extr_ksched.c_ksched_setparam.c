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
struct thread {int dummy; } ;
struct sched_param {int dummy; } ;
struct ksched {int dummy; } ;

/* Variables and functions */
 int getscheduler (struct ksched*,struct thread*,int*) ; 
 int ksched_setscheduler (struct ksched*,struct thread*,int,struct sched_param const*) ; 

int
ksched_setparam(struct ksched *ksched,
    struct thread *td, const struct sched_param *param)
{
	int e, policy;

	e = getscheduler(ksched, td, &policy);
	if (e == 0)
		e = ksched_setscheduler(ksched, td, policy, param);
	return (e);
}