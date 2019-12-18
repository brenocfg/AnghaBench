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
struct hub_irq_data {int cpu; void** irq_mask; } ;
struct cpumask {int dummy; } ;
typedef  int /*<<< orphan*/  nasid_t ;

/* Variables and functions */
 int /*<<< orphan*/  COMPACT_TO_NASID_NODEID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PI_INT_MASK0_A ; 
 int /*<<< orphan*/  PI_INT_MASK0_B ; 
 int /*<<< orphan*/  PI_INT_MASK1_A ; 
 int /*<<< orphan*/  PI_INT_MASK1_B ; 
 void* REMOTE_HUB_PTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_online_mask ; 
 int /*<<< orphan*/  cpu_to_node (int) ; 
 int cpumask_first_and (struct cpumask const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cputoslice (int) ; 

__attribute__((used)) static void setup_hub_mask(struct hub_irq_data *hd, const struct cpumask *mask)
{
	nasid_t nasid;
	int cpu;

	cpu = cpumask_first_and(mask, cpu_online_mask);
	nasid = COMPACT_TO_NASID_NODEID(cpu_to_node(cpu));
	hd->cpu = cpu;
	if (!cputoslice(cpu)) {
		hd->irq_mask[0] = REMOTE_HUB_PTR(nasid, PI_INT_MASK0_A);
		hd->irq_mask[1] = REMOTE_HUB_PTR(nasid, PI_INT_MASK1_A);
	} else {
		hd->irq_mask[0] = REMOTE_HUB_PTR(nasid, PI_INT_MASK0_B);
		hd->irq_mask[1] = REMOTE_HUB_PTR(nasid, PI_INT_MASK1_B);
	}
}