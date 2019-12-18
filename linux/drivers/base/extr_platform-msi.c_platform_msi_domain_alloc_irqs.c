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
struct platform_msi_priv_data {int dummy; } ;
struct device {int /*<<< orphan*/  msi_domain; } ;
typedef  int /*<<< orphan*/  irq_write_msi_msg_t ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct platform_msi_priv_data*) ; 
 int PTR_ERR (struct platform_msi_priv_data*) ; 
 int msi_domain_alloc_irqs (int /*<<< orphan*/ ,struct device*,unsigned int) ; 
 int platform_msi_alloc_descs (struct device*,unsigned int,struct platform_msi_priv_data*) ; 
 struct platform_msi_priv_data* platform_msi_alloc_priv_data (struct device*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_msi_free_descs (struct device*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  platform_msi_free_priv_data (struct platform_msi_priv_data*) ; 

int platform_msi_domain_alloc_irqs(struct device *dev, unsigned int nvec,
				   irq_write_msi_msg_t write_msi_msg)
{
	struct platform_msi_priv_data *priv_data;
	int err;

	priv_data = platform_msi_alloc_priv_data(dev, nvec, write_msi_msg);
	if (IS_ERR(priv_data))
		return PTR_ERR(priv_data);

	err = platform_msi_alloc_descs(dev, nvec, priv_data);
	if (err)
		goto out_free_priv_data;

	err = msi_domain_alloc_irqs(dev->msi_domain, dev, nvec);
	if (err)
		goto out_free_desc;

	return 0;

out_free_desc:
	platform_msi_free_descs(dev, 0, nvec);
out_free_priv_data:
	platform_msi_free_priv_data(priv_data);

	return err;
}