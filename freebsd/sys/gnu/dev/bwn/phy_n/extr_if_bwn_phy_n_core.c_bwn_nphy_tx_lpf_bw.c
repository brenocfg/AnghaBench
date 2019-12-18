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
typedef  int uint16_t ;
struct TYPE_2__ {int rev; } ;
struct bwn_mac {TYPE_1__ mac_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_NPHY_TXF_40CO_B1S2 ; 
 int /*<<< orphan*/  BWN_NPHY_TXF_40CO_B32S2 ; 
 int /*<<< orphan*/  BWN_PHY_WRITE (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ bwn_is_40mhz (struct bwn_mac*) ; 
 scalar_t__ bwn_nphy_ipa (struct bwn_mac*) ; 

__attribute__((used)) static void bwn_nphy_tx_lpf_bw(struct bwn_mac *mac)
{
	uint16_t tmp;

	if (mac->mac_phy.rev < 3 || mac->mac_phy.rev >= 7)
		return;

	if (bwn_nphy_ipa(mac))
		tmp = bwn_is_40mhz(mac) ? 5 : 4;
	else
		tmp = bwn_is_40mhz(mac) ? 3 : 1;
	BWN_PHY_WRITE(mac, BWN_NPHY_TXF_40CO_B32S2,
		      (tmp << 9) | (tmp << 6) | (tmp << 3) | tmp);

	if (bwn_nphy_ipa(mac)) {
		tmp = bwn_is_40mhz(mac) ? 4 : 1;
		BWN_PHY_WRITE(mac, BWN_NPHY_TXF_40CO_B1S2,
			      (tmp << 9) | (tmp << 6) | (tmp << 3) | tmp);
	}
}