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
struct xlp_msi_data {int /*<<< orphan*/  lnkbase; } ;
struct irq_data {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCIE_9XX_MSI_STATUS ; 
 int /*<<< orphan*/  PCIE_MSI_STATUS ; 
 scalar_t__ cpu_is_xlp9xx () ; 
 struct xlp_msi_data* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int nlm_irq_msilink (int /*<<< orphan*/ ) ; 
 int nlm_irq_msivec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  xlp_msi_disable (struct irq_data*) ; 

__attribute__((used)) static void xlp_msi_mask_ack(struct irq_data *d)
{
	struct xlp_msi_data *md = irq_data_get_irq_chip_data(d);
	int link, vec;

	link = nlm_irq_msilink(d->irq);
	vec = nlm_irq_msivec(d->irq);
	xlp_msi_disable(d);

	/* Ack MSI on bridge */
	if (cpu_is_xlp9xx())
		nlm_write_reg(md->lnkbase, PCIE_9XX_MSI_STATUS, 1u << vec);
	else
		nlm_write_reg(md->lnkbase, PCIE_MSI_STATUS, 1u << vec);

}