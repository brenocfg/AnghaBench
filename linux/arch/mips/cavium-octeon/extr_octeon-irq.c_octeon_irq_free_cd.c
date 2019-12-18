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
struct octeon_ciu_chip_data {int dummy; } ;
struct irq_domain {int dummy; } ;
struct irq_data {int dummy; } ;

/* Variables and functions */
 struct octeon_ciu_chip_data* irq_data_get_irq_chip_data (struct irq_data*) ; 
 struct irq_data* irq_get_irq_data (unsigned int) ; 
 int /*<<< orphan*/  irq_set_chip_data (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct octeon_ciu_chip_data*) ; 

__attribute__((used)) static void octeon_irq_free_cd(struct irq_domain *d, unsigned int irq)
{
	struct irq_data *data = irq_get_irq_data(irq);
	struct octeon_ciu_chip_data *cd = irq_data_get_irq_chip_data(data);

	irq_set_chip_data(irq, NULL);
	kfree(cd);
}