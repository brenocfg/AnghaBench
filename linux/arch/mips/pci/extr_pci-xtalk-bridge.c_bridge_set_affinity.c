#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct irq_data {int hwirq; TYPE_1__* parent_data; struct bridge_irq_chip_data* chip_data; } ;
struct cpumask {int dummy; } ;
struct bridge_irq_chip_data {TYPE_2__* bc; } ;
typedef  int nasid_t ;
struct TYPE_7__ {int /*<<< orphan*/  addr; } ;
struct TYPE_6__ {int intr_addr; } ;
struct TYPE_5__ {int hwirq; } ;

/* Variables and functions */
 int COMPACT_TO_NASID_NODEID (int /*<<< orphan*/ ) ; 
 TYPE_4__* b_int_addr ; 
 int /*<<< orphan*/  b_wid_tflush ; 
 int /*<<< orphan*/  bridge_read (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bridge_write (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cpu_online_mask ; 
 int /*<<< orphan*/  cpu_to_node (int) ; 
 int cpumask_first_and (struct cpumask const*,int /*<<< orphan*/ ) ; 
 int irq_chip_set_affinity_parent (struct irq_data*,struct cpumask const*,int) ; 

__attribute__((used)) static int bridge_set_affinity(struct irq_data *d, const struct cpumask *mask,
			       bool force)
{
#ifdef CONFIG_NUMA
	struct bridge_irq_chip_data *data = d->chip_data;
	int bit = d->parent_data->hwirq;
	int pin = d->hwirq;
	nasid_t nasid;
	int ret, cpu;

	ret = irq_chip_set_affinity_parent(d, mask, force);
	if (ret >= 0) {
		cpu = cpumask_first_and(mask, cpu_online_mask);
		nasid = COMPACT_TO_NASID_NODEID(cpu_to_node(cpu));
		bridge_write(data->bc, b_int_addr[pin].addr,
			     (((data->bc->intr_addr >> 30) & 0x30000) |
			      bit | (nasid << 8)));
		bridge_read(data->bc, b_wid_tflush);
	}
	return ret;
#else
	return irq_chip_set_affinity_parent(d, mask, force);
#endif
}