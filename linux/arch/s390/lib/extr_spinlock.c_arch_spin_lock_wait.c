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
typedef  int /*<<< orphan*/  arch_spinlock_t ;

/* Variables and functions */
 int /*<<< orphan*/  CIF_DEDICATED_CPU ; 
 int /*<<< orphan*/  arch_spin_lock_classic (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arch_spin_lock_queued (int /*<<< orphan*/ *) ; 
 scalar_t__ test_cpu_flag (int /*<<< orphan*/ ) ; 

void arch_spin_lock_wait(arch_spinlock_t *lp)
{
	/* Use classic spinlocks + niai if the steal time is >= 10% */
	if (test_cpu_flag(CIF_DEDICATED_CPU))
		arch_spin_lock_queued(lp);
	else
		arch_spin_lock_classic(lp);
}