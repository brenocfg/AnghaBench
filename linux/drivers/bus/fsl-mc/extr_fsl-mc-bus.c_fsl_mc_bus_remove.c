#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct fsl_mc {TYPE_1__* root_mc_bus_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * mc_io; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  fsl_destroy_mc_io (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsl_mc_device_remove (TYPE_1__*) ; 
 int /*<<< orphan*/  fsl_mc_is_root_dprc (int /*<<< orphan*/ *) ; 
 struct fsl_mc* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int fsl_mc_bus_remove(struct platform_device *pdev)
{
	struct fsl_mc *mc = platform_get_drvdata(pdev);

	if (!fsl_mc_is_root_dprc(&mc->root_mc_bus_dev->dev))
		return -EINVAL;

	fsl_mc_device_remove(mc->root_mc_bus_dev);

	fsl_destroy_mc_io(mc->root_mc_bus_dev->mc_io);
	mc->root_mc_bus_dev->mc_io = NULL;

	return 0;
}