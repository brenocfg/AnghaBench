#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ag71xx_platform_data {scalar_t__ phy_mask; scalar_t__ switch_data; TYPE_4__* mii_bus_dev; } ;
struct ag71xx {TYPE_2__* mii_bus; TYPE_1__* pdev; } ;
struct TYPE_8__ {int /*<<< orphan*/ * bus; } ;
struct TYPE_7__ {int /*<<< orphan*/  mdio_lock; int /*<<< orphan*/  (* reset ) (TYPE_2__*) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ag71xx_ar7240_init (struct ag71xx*) ; 
 struct ag71xx_platform_data* ag71xx_get_pdata (struct ag71xx*) ; 
 int ag71xx_phy_connect_fixed (struct ag71xx*) ; 
 int ag71xx_phy_connect_multi (struct ag71xx*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (TYPE_4__*) ; 
 TYPE_2__* dev_to_mii_bus (TYPE_4__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

int ag71xx_phy_connect(struct ag71xx *ag)
{
	struct ag71xx_platform_data *pdata = ag71xx_get_pdata(ag);

	if (pdata->mii_bus_dev == NULL ||
	    pdata->mii_bus_dev->bus == NULL )
		return ag71xx_phy_connect_fixed(ag);

	ag->mii_bus = dev_to_mii_bus(pdata->mii_bus_dev);
	if (ag->mii_bus == NULL) {
		dev_err(&ag->pdev->dev, "unable to find MII bus on device '%s'\n",
			   dev_name(pdata->mii_bus_dev));
		return -ENODEV;
	}

	/* Reset the mdio bus explicitly */
	if (ag->mii_bus->reset) {
		mutex_lock(&ag->mii_bus->mdio_lock);
		ag->mii_bus->reset(ag->mii_bus);
		mutex_unlock(&ag->mii_bus->mdio_lock);
	}

	if (pdata->switch_data)
		return ag71xx_ar7240_init(ag);

	if (pdata->phy_mask)
		return ag71xx_phy_connect_multi(ag);

	return ag71xx_phy_connect_fixed(ag);
}