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
typedef  int uint8_t ;
typedef  int uint16_t ;
struct bwn_phy_lp {scalar_t__ plp_rccap; } ;
struct TYPE_2__ {int rev; struct bwn_phy_lp phy_lp; } ;
struct bwn_mac {TYPE_1__ mac_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_B2063_TX_BB_SP3 ; 
 int /*<<< orphan*/  BWN_PHY_LP_PHY_CTL ; 
 int /*<<< orphan*/  BWN_PHY_SETMASK (struct bwn_mac*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  BWN_RF_WRITE (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bwn_phy_lp_set_rccap (struct bwn_mac*) ; 

__attribute__((used)) static void
bwn_phy_lp_set_anafilter(struct bwn_mac *mac, uint8_t channel)
{
	struct bwn_phy_lp *plp = &mac->mac_phy.phy_lp;
	uint16_t tmp = (channel == 14);

	if (mac->mac_phy.rev < 2) {
		BWN_PHY_SETMASK(mac, BWN_PHY_LP_PHY_CTL, 0xfcff, tmp << 9);
		if ((mac->mac_phy.rev == 1) && (plp->plp_rccap))
			bwn_phy_lp_set_rccap(mac);
		return;
	}

	BWN_RF_WRITE(mac, BWN_B2063_TX_BB_SP3, 0x3f);
}