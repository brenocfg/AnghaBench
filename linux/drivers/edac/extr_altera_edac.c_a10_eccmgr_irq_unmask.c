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
struct irq_data {int /*<<< orphan*/  hwirq; } ;
struct altr_arria10_edac {int /*<<< orphan*/  ecc_mgr_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  A10_SYSMGR_ECC_INTMASK_CLR_OFST ; 
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 struct altr_arria10_edac* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void a10_eccmgr_irq_unmask(struct irq_data *d)
{
	struct altr_arria10_edac *edac = irq_data_get_irq_chip_data(d);

	regmap_write(edac->ecc_mgr_map,	A10_SYSMGR_ECC_INTMASK_CLR_OFST,
		     BIT(d->hwirq));
}