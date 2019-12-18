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
struct mips_cdmm_driver {int /*<<< orphan*/  id_table; } ;
struct mips_cdmm_device {int dummy; } ;
struct device_driver {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * mips_cdmm_lookup (int /*<<< orphan*/ ,struct mips_cdmm_device*) ; 
 struct mips_cdmm_device* to_mips_cdmm_device (struct device*) ; 
 struct mips_cdmm_driver* to_mips_cdmm_driver (struct device_driver*) ; 

__attribute__((used)) static int mips_cdmm_match(struct device *dev, struct device_driver *drv)
{
	struct mips_cdmm_device *cdev = to_mips_cdmm_device(dev);
	struct mips_cdmm_driver *cdrv = to_mips_cdmm_driver(drv);

	return mips_cdmm_lookup(cdrv->id_table, cdev) != NULL;
}