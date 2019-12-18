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
struct octeon_ciu_chip_data {int current_cpu; int /*<<< orphan*/  ciu_node; int /*<<< orphan*/  ciu3_addr; int /*<<< orphan*/  intsn; } ;
struct octeon_ciu3_info {int /*<<< orphan*/  node; int /*<<< orphan*/  ciu3_addr; } ;
struct irq_domain {struct octeon_ciu3_info* host_data; } ;
struct irq_chip {int dummy; } ;
typedef  int /*<<< orphan*/  irq_hw_number_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (unsigned int,struct irq_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chip_data (unsigned int,struct octeon_ciu_chip_data*) ; 
 struct octeon_ciu_chip_data* kzalloc_node (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int octeon_irq_ciu3_mapx(struct irq_domain *d, unsigned int virq,
			 irq_hw_number_t hw, struct irq_chip *chip)
{
	struct octeon_ciu3_info *ciu3_info = d->host_data;
	struct octeon_ciu_chip_data *cd = kzalloc_node(sizeof(*cd), GFP_KERNEL,
						       ciu3_info->node);
	if (!cd)
		return -ENOMEM;
	cd->intsn = hw;
	cd->current_cpu = -1;
	cd->ciu3_addr = ciu3_info->ciu3_addr;
	cd->ciu_node = ciu3_info->node;
	irq_set_chip_and_handler(virq, chip, handle_edge_irq);
	irq_set_chip_data(virq, cd);

	return 0;
}