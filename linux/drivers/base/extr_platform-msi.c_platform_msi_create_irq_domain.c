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
struct msi_domain_info {int flags; } ;
struct irq_domain {int dummy; } ;
struct fwnode_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOMAIN_BUS_PLATFORM_MSI ; 
 int MSI_FLAG_USE_DEF_CHIP_OPS ; 
 int MSI_FLAG_USE_DEF_DOM_OPS ; 
 int /*<<< orphan*/  irq_domain_update_bus_token (struct irq_domain*,int /*<<< orphan*/ ) ; 
 struct irq_domain* msi_create_irq_domain (struct fwnode_handle*,struct msi_domain_info*,struct irq_domain*) ; 
 int /*<<< orphan*/  platform_msi_update_chip_ops (struct msi_domain_info*) ; 
 int /*<<< orphan*/  platform_msi_update_dom_ops (struct msi_domain_info*) ; 

struct irq_domain *platform_msi_create_irq_domain(struct fwnode_handle *fwnode,
						  struct msi_domain_info *info,
						  struct irq_domain *parent)
{
	struct irq_domain *domain;

	if (info->flags & MSI_FLAG_USE_DEF_DOM_OPS)
		platform_msi_update_dom_ops(info);
	if (info->flags & MSI_FLAG_USE_DEF_CHIP_OPS)
		platform_msi_update_chip_ops(info);

	domain = msi_create_irq_domain(fwnode, info, parent);
	if (domain)
		irq_domain_update_bus_token(domain, DOMAIN_BUS_PLATFORM_MSI);

	return domain;
}