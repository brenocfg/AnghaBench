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
struct TYPE_2__ {scalar_t__ autoneg; int advertising; scalar_t__ speed; } ;
struct xgbe_prv_data {TYPE_1__ phy; } ;

/* Variables and functions */
 int ADVERTISED_10000baseKR_Full ; 
 scalar_t__ AUTONEG_ENABLE ; 
 scalar_t__ SPEED_10000 ; 

__attribute__((used)) static bool xgbe_use_xgmii_mode(struct xgbe_prv_data *pdata)
{
	if (pdata->phy.autoneg == AUTONEG_ENABLE) {
		if (pdata->phy.advertising & ADVERTISED_10000baseKR_Full)
			return true;
	} else {
		if (pdata->phy.speed == SPEED_10000)
			return true;
	}

	return false;
}