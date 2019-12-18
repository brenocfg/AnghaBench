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
struct ag71xx_platform_data {scalar_t__ switch_data; } ;
struct ag71xx {scalar_t__ phy_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ag71xx_ar7240_cleanup (struct ag71xx*) ; 
 struct ag71xx_platform_data* ag71xx_get_pdata (struct ag71xx*) ; 
 int /*<<< orphan*/  phy_disconnect (scalar_t__) ; 

void ag71xx_phy_disconnect(struct ag71xx *ag)
{
	struct ag71xx_platform_data *pdata = ag71xx_get_pdata(ag);

	if (pdata->switch_data)
		ag71xx_ar7240_cleanup(ag);
	else if (ag->phy_dev)
		phy_disconnect(ag->phy_dev);
}