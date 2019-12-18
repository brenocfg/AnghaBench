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
struct powerpc_intr {int /*<<< orphan*/  priv; int /*<<< orphan*/  pi_cpuset; int /*<<< orphan*/  intline; int /*<<< orphan*/ * pic; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_SETOF (int,int /*<<< orphan*/ *) ; 
 int EOPNOTSUPP ; 
 int NOCPU ; 
 int /*<<< orphan*/  PIC_BIND (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  all_cpus ; 
 int /*<<< orphan*/  cold ; 
 int /*<<< orphan*/ * root_pic ; 

__attribute__((used)) static int
powerpc_assign_intr_cpu(void *arg, int cpu)
{
#ifdef SMP
	struct powerpc_intr *i = arg;

	if (cpu == NOCPU)
		i->pi_cpuset = all_cpus;
	else
		CPU_SETOF(cpu, &i->pi_cpuset);

	if (!cold && i->pic != NULL && i->pic == root_pic)
		PIC_BIND(i->pic, i->intline, i->pi_cpuset, &i->priv);

	return (0);
#else
	return (EOPNOTSUPP);
#endif
}