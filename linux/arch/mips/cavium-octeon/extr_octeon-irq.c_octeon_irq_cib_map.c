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
struct octeon_irq_cib_host_data {scalar_t__ max_bits; } ;
struct octeon_irq_cib_chip_data {scalar_t__ bit; struct octeon_irq_cib_host_data* host_data; } ;
struct irq_domain {struct octeon_irq_cib_host_data* host_data; } ;
typedef  scalar_t__ irq_hw_number_t ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  handle_simple_irq ; 
 TYPE_1__* irq_domain_get_of_node (struct irq_domain*) ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chip_data (unsigned int,struct octeon_irq_cib_chip_data*) ; 
 struct octeon_irq_cib_chip_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  octeon_irq_chip_cib ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int octeon_irq_cib_map(struct irq_domain *d,
			      unsigned int virq, irq_hw_number_t hw)
{
	struct octeon_irq_cib_host_data *host_data = d->host_data;
	struct octeon_irq_cib_chip_data *cd;

	if (hw >= host_data->max_bits) {
		pr_err("ERROR: %s mapping %u is to big!\n",
		       irq_domain_get_of_node(d)->name, (unsigned)hw);
		return -EINVAL;
	}

	cd = kzalloc(sizeof(*cd), GFP_KERNEL);
	cd->host_data = host_data;
	cd->bit = hw;

	irq_set_chip_and_handler(virq, &octeon_irq_chip_cib,
				 handle_simple_irq);
	irq_set_chip_data(virq, cd);
	return 0;
}