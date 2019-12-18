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

/* Variables and functions */
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  cpuidle_coupled_poke_pending ; 
 scalar_t__ cpumask_test_cpu (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 

__attribute__((used)) static int cpuidle_coupled_clear_pokes(int cpu)
{
	if (!cpumask_test_cpu(cpu, &cpuidle_coupled_poke_pending))
		return 0;

	local_irq_enable();
	while (cpumask_test_cpu(cpu, &cpuidle_coupled_poke_pending))
		cpu_relax();
	local_irq_disable();

	return 1;
}