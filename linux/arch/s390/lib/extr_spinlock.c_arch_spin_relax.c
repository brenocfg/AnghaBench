#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ arch_spinlock_t ;

/* Variables and functions */
 scalar_t__ MACHINE_IS_LPAR ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int _Q_LOCK_CPU_MASK ; 
 int /*<<< orphan*/  arch_vcpu_is_preempted (int) ; 
 int /*<<< orphan*/  smp_yield_cpu (int) ; 

void arch_spin_relax(arch_spinlock_t *lp)
{
	int cpu;

	cpu = READ_ONCE(lp->lock) & _Q_LOCK_CPU_MASK;
	if (!cpu)
		return;
	if (MACHINE_IS_LPAR && !arch_vcpu_is_preempted(cpu - 1))
		return;
	smp_yield_cpu(cpu - 1);
}