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
struct bwn_txgain {int tg_dac; int tg_gm; int tg_pga; int tg_pad; } ;
struct TYPE_2__ {int rev; } ;
struct bwn_mac {TYPE_1__ mac_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_PHY_AFE_DAC_CTL ; 
 int /*<<< orphan*/  BWN_PHY_OFDM (int) ; 
 int BWN_PHY_READ (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BWN_PHY_TX_GAIN_CTL_OVERRIDE_VAL ; 

__attribute__((used)) static struct bwn_txgain
bwn_phy_lp_get_txgain(struct bwn_mac *mac)
{
	struct bwn_txgain tg;
	uint16_t tmp;

	tg.tg_dac = (BWN_PHY_READ(mac, BWN_PHY_AFE_DAC_CTL) & 0x380) >> 7;
	if (mac->mac_phy.rev < 2) {
		tmp = BWN_PHY_READ(mac,
		    BWN_PHY_TX_GAIN_CTL_OVERRIDE_VAL) & 0x7ff;
		tg.tg_gm = tmp & 0x0007;
		tg.tg_pga = (tmp & 0x0078) >> 3;
		tg.tg_pad = (tmp & 0x780) >> 7;
		return (tg);
	}

	tmp = BWN_PHY_READ(mac, BWN_PHY_TX_GAIN_CTL_OVERRIDE_VAL);
	tg.tg_pad = BWN_PHY_READ(mac, BWN_PHY_OFDM(0xfb)) & 0xff;
	tg.tg_gm = tmp & 0xff;
	tg.tg_pga = (tmp >> 8) & 0xff;
	return (tg);
}