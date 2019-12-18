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
struct irq_domain {struct fsl_msi* host_data; } ;
struct irq_chip {int dummy; } ;
struct fsl_msi {int dummy; } ;
typedef  int /*<<< orphan*/  irq_hw_number_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_TYPE_EDGE_FALLING ; 
 struct irq_chip fsl_msi_chip ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (unsigned int,struct irq_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chip_data (unsigned int,struct fsl_msi*) ; 
 int /*<<< orphan*/  irq_set_status_flags (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fsl_msi_host_map(struct irq_domain *h, unsigned int virq,
				irq_hw_number_t hw)
{
	struct fsl_msi *msi_data = h->host_data;
	struct irq_chip *chip = &fsl_msi_chip;

	irq_set_status_flags(virq, IRQ_TYPE_EDGE_FALLING);

	irq_set_chip_data(virq, msi_data);
	irq_set_chip_and_handler(virq, chip, handle_edge_irq);

	return 0;
}