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
struct ag71xx_platform_data {scalar_t__ switch_data; scalar_t__ mii_bus_dev; } ;
struct ag71xx {int /*<<< orphan*/  lock; scalar_t__ link; scalar_t__ phy_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ag71xx_ar7240_stop (struct ag71xx*) ; 
 struct ag71xx_platform_data* ag71xx_get_pdata (struct ag71xx*) ; 
 int /*<<< orphan*/  ag71xx_link_adjust (struct ag71xx*) ; 
 int /*<<< orphan*/  phy_stop (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void ag71xx_phy_stop(struct ag71xx *ag)
{
	struct ag71xx_platform_data *pdata = ag71xx_get_pdata(ag);
	unsigned long flags;

	if (ag->phy_dev)
		phy_stop(ag->phy_dev);
	else if (pdata->mii_bus_dev && pdata->switch_data)
		ag71xx_ar7240_stop(ag);

	spin_lock_irqsave(&ag->lock, flags);
	if (ag->link) {
		ag->link = 0;
		ag71xx_link_adjust(ag);
	}
	spin_unlock_irqrestore(&ag->lock, flags);
}