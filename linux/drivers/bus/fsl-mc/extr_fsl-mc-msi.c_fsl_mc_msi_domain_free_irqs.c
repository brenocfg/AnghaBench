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
struct irq_domain {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct irq_domain* dev_get_msi_domain (struct device*) ; 
 int /*<<< orphan*/  dev_to_msi_list (struct device*) ; 
 int /*<<< orphan*/  fsl_mc_msi_free_descs (struct device*) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_domain_free_irqs (struct irq_domain*,struct device*) ; 

void fsl_mc_msi_domain_free_irqs(struct device *dev)
{
	struct irq_domain *msi_domain;

	msi_domain = dev_get_msi_domain(dev);
	if (!msi_domain)
		return;

	msi_domain_free_irqs(msi_domain, dev);

	if (list_empty(dev_to_msi_list(dev)))
		return;

	fsl_mc_msi_free_descs(dev);
}