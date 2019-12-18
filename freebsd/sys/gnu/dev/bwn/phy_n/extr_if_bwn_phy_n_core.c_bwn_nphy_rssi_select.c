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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int rev; } ;
struct bwn_mac {TYPE_1__ mac_phy; } ;
typedef  enum n_rssi_type { ____Placeholder_n_rssi_type } n_rssi_type ;

/* Variables and functions */
 int /*<<< orphan*/  bwn_nphy_rev2_rssi_select (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bwn_nphy_rev3_rssi_select (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bwn_nphy_rssi_select_rev19 (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bwn_nphy_rssi_select(struct bwn_mac *mac, uint8_t code,
				 enum n_rssi_type type)
{
	if (mac->mac_phy.rev >= 19)
		bwn_nphy_rssi_select_rev19(mac, code, type);
	else if (mac->mac_phy.rev >= 3)
		bwn_nphy_rev3_rssi_select(mac, code, type);
	else
		bwn_nphy_rev2_rssi_select(mac, code, type);
}