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
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct irq_domain* dev_get_msi_domain (struct device*) ; 
 int /*<<< orphan*/  dev_to_msi_list (struct device*) ; 
 int fsl_mc_msi_alloc_descs (struct device*,unsigned int) ; 
 int /*<<< orphan*/  fsl_mc_msi_free_descs (struct device*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ ) ; 
 int msi_domain_alloc_irqs (struct irq_domain*,struct device*,unsigned int) ; 

int fsl_mc_msi_domain_alloc_irqs(struct device *dev,
				 unsigned int irq_count)
{
	struct irq_domain *msi_domain;
	int error;

	if (!list_empty(dev_to_msi_list(dev)))
		return -EINVAL;

	error = fsl_mc_msi_alloc_descs(dev, irq_count);
	if (error < 0)
		return error;

	msi_domain = dev_get_msi_domain(dev);
	if (!msi_domain) {
		error = -EINVAL;
		goto cleanup_msi_descs;
	}

	/*
	 * NOTE: Calling this function will trigger the invocation of the
	 * its_fsl_mc_msi_prepare() callback
	 */
	error = msi_domain_alloc_irqs(msi_domain, dev, irq_count);

	if (error) {
		dev_err(dev, "Failed to allocate IRQs\n");
		goto cleanup_msi_descs;
	}

	return 0;

cleanup_msi_descs:
	fsl_mc_msi_free_descs(dev);
	return error;
}