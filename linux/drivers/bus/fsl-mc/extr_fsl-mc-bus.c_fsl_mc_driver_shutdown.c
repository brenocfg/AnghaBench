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
struct fsl_mc_driver {int /*<<< orphan*/  (* shutdown ) (struct fsl_mc_device*) ;} ;
struct fsl_mc_device {int dummy; } ;
struct device {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct fsl_mc_device*) ; 
 struct fsl_mc_device* to_fsl_mc_device (struct device*) ; 
 struct fsl_mc_driver* to_fsl_mc_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fsl_mc_driver_shutdown(struct device *dev)
{
	struct fsl_mc_driver *mc_drv = to_fsl_mc_driver(dev->driver);
	struct fsl_mc_device *mc_dev = to_fsl_mc_device(dev);

	mc_drv->shutdown(mc_dev);
}