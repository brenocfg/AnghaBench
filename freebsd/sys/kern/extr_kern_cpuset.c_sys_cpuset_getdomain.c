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
struct cpuset_getdomain_args {int /*<<< orphan*/  policy; int /*<<< orphan*/  mask; int /*<<< orphan*/  domainsetsize; int /*<<< orphan*/  id; int /*<<< orphan*/  which; int /*<<< orphan*/  level; } ;

/* Variables and functions */
 int kern_cpuset_getdomain (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
sys_cpuset_getdomain(struct thread *td, struct cpuset_getdomain_args *uap)
{

	return (kern_cpuset_getdomain(td, uap->level, uap->which,
	    uap->id, uap->domainsetsize, uap->mask, uap->policy));
}