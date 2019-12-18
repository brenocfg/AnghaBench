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
struct device {int dummy; } ;
struct dev_dax {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_DAX_CLASS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct dev_dax*) ; 
 int PTR_ERR (struct dev_dax*) ; 
 struct dev_dax* __dax_pmem_probe (struct device*,int /*<<< orphan*/ ) ; 
 int dev_dax_probe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devres_close_group (int /*<<< orphan*/ *,struct dev_dax*) ; 
 int /*<<< orphan*/  devres_open_group (int /*<<< orphan*/ *,struct dev_dax*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_release_group (int /*<<< orphan*/ *,struct dev_dax*) ; 

__attribute__((used)) static int dax_pmem_compat_probe(struct device *dev)
{
	struct dev_dax *dev_dax = __dax_pmem_probe(dev, DEV_DAX_CLASS);
	int rc;

	if (IS_ERR(dev_dax))
		return PTR_ERR(dev_dax);

        if (!devres_open_group(&dev_dax->dev, dev_dax, GFP_KERNEL))
		return -ENOMEM;

	device_lock(&dev_dax->dev);
	rc = dev_dax_probe(&dev_dax->dev);
	device_unlock(&dev_dax->dev);

	devres_close_group(&dev_dax->dev, dev_dax);
	if (rc)
		devres_release_group(&dev_dax->dev, dev_dax);

	return rc;
}