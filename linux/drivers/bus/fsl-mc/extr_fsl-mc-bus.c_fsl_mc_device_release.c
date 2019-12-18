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
struct fsl_mc_device {struct fsl_mc_device* regions; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ is_fsl_mc_bus_dprc (struct fsl_mc_device*) ; 
 int /*<<< orphan*/  kfree (struct fsl_mc_device*) ; 
 struct fsl_mc_device* to_fsl_mc_bus (struct fsl_mc_device*) ; 
 struct fsl_mc_device* to_fsl_mc_device (struct device*) ; 

__attribute__((used)) static void fsl_mc_device_release(struct device *dev)
{
	struct fsl_mc_device *mc_dev = to_fsl_mc_device(dev);

	kfree(mc_dev->regions);

	if (is_fsl_mc_bus_dprc(mc_dev))
		kfree(to_fsl_mc_bus(mc_dev));
	else
		kfree(mc_dev);
}