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
struct fsl_mc_device {int /*<<< orphan*/  dev; int /*<<< orphan*/ * mc_io; int /*<<< orphan*/  mc_handle; } ;
struct fsl_mc_bus {int /*<<< orphan*/  irq_resources; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  __fsl_mc_device_remove ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ dev_get_msi_domain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_set_msi_domain (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_for_each_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dprc_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprc_teardown_irq (struct fsl_mc_device*) ; 
 int /*<<< orphan*/  fsl_destroy_mc_io (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsl_mc_cleanup_all_resource_pools (struct fsl_mc_device*) ; 
 int /*<<< orphan*/  fsl_mc_cleanup_irq_pool (struct fsl_mc_bus*) ; 
 int /*<<< orphan*/  fsl_mc_is_root_dprc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_fsl_mc_bus_dprc (struct fsl_mc_device*) ; 
 struct fsl_mc_bus* to_fsl_mc_bus (struct fsl_mc_device*) ; 

__attribute__((used)) static int dprc_remove(struct fsl_mc_device *mc_dev)
{
	int error;
	struct fsl_mc_bus *mc_bus = to_fsl_mc_bus(mc_dev);

	if (!is_fsl_mc_bus_dprc(mc_dev))
		return -EINVAL;
	if (!mc_dev->mc_io)
		return -EINVAL;

	if (!mc_bus->irq_resources)
		return -EINVAL;

	if (dev_get_msi_domain(&mc_dev->dev))
		dprc_teardown_irq(mc_dev);

	device_for_each_child(&mc_dev->dev, NULL, __fsl_mc_device_remove);

	if (dev_get_msi_domain(&mc_dev->dev)) {
		fsl_mc_cleanup_irq_pool(mc_bus);
		dev_set_msi_domain(&mc_dev->dev, NULL);
	}

	fsl_mc_cleanup_all_resource_pools(mc_dev);

	error = dprc_close(mc_dev->mc_io, 0, mc_dev->mc_handle);
	if (error < 0)
		dev_err(&mc_dev->dev, "dprc_close() failed: %d\n", error);

	if (!fsl_mc_is_root_dprc(&mc_dev->dev)) {
		fsl_destroy_mc_io(mc_dev->mc_io);
		mc_dev->mc_io = NULL;
	}

	dev_info(&mc_dev->dev, "DPRC device unbound from driver");
	return 0;
}