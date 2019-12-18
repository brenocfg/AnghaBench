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
struct msi_domain_info {int flags; struct irq_chip* chip; } ;
struct irq_chip {int flags; scalar_t__ irq_write_msi_msg; scalar_t__ irq_set_affinity; scalar_t__ irq_eoi; scalar_t__ irq_unmask; scalar_t__ irq_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int IRQCHIP_SUPPORTS_LEVEL_MSI ; 
 int MSI_FLAG_LEVEL_CAPABLE ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ irq_chip_eoi_parent ; 
 scalar_t__ irq_chip_mask_parent ; 
 scalar_t__ irq_chip_unmask_parent ; 
 scalar_t__ msi_domain_set_affinity ; 
 scalar_t__ platform_msi_write_msg ; 

__attribute__((used)) static void platform_msi_update_chip_ops(struct msi_domain_info *info)
{
	struct irq_chip *chip = info->chip;

	BUG_ON(!chip);
	if (!chip->irq_mask)
		chip->irq_mask = irq_chip_mask_parent;
	if (!chip->irq_unmask)
		chip->irq_unmask = irq_chip_unmask_parent;
	if (!chip->irq_eoi)
		chip->irq_eoi = irq_chip_eoi_parent;
	if (!chip->irq_set_affinity)
		chip->irq_set_affinity = msi_domain_set_affinity;
	if (!chip->irq_write_msi_msg)
		chip->irq_write_msi_msg = platform_msi_write_msg;
	if (WARN_ON((info->flags & MSI_FLAG_LEVEL_CAPABLE) &&
		    !(chip->flags & IRQCHIP_SUPPORTS_LEVEL_MSI)))
		info->flags &= ~MSI_FLAG_LEVEL_CAPABLE;
}