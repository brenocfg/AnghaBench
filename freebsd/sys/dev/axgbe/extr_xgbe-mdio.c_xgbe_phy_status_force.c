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
struct TYPE_2__ {int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; } ;
struct xgbe_prv_data {int speed_set; TYPE_1__ phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  SPEED_1000 ; 
 int /*<<< orphan*/  SPEED_10000 ; 
 int /*<<< orphan*/  SPEED_2500 ; 
#define  XGBE_SPEEDSET_1000_10000 129 
#define  XGBE_SPEEDSET_2500_10000 128 
 scalar_t__ xgbe_in_kr_mode (struct xgbe_prv_data*) ; 

__attribute__((used)) static void xgbe_phy_status_force(struct xgbe_prv_data *pdata)
{
	if (xgbe_in_kr_mode(pdata)) {
		pdata->phy.speed = SPEED_10000;
	} else {
		switch (pdata->speed_set) {
		case XGBE_SPEEDSET_1000_10000:
			pdata->phy.speed = SPEED_1000;
			break;

		case XGBE_SPEEDSET_2500_10000:
			pdata->phy.speed = SPEED_2500;
			break;
		}
	}
	pdata->phy.duplex = DUPLEX_FULL;
}