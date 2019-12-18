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
struct TYPE_2__ {int rev; } ;
struct bwn_mac {TYPE_1__ mac_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  N_RSSI_NB ; 
 int /*<<< orphan*/  N_RSSI_W1 ; 
 int /*<<< orphan*/  N_RSSI_W2 ; 
 int /*<<< orphan*/  bwn_nphy_rev2_rssi_cal (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwn_nphy_rev3_rssi_cal (struct bwn_mac*) ; 

__attribute__((used)) static void bwn_nphy_rssi_cal(struct bwn_mac *mac)
{
	if (mac->mac_phy.rev >= 19) {
		/* TODO */
	} else if (mac->mac_phy.rev >= 3) {
		bwn_nphy_rev3_rssi_cal(mac);
	} else {
		bwn_nphy_rev2_rssi_cal(mac, N_RSSI_NB);
		bwn_nphy_rev2_rssi_cal(mac, N_RSSI_W1);
		bwn_nphy_rev2_rssi_cal(mac, N_RSSI_W2);
	}
}