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
typedef  int uint16_t ;
struct bwn_mac {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_PHY_AFE_DAC_CTL ; 
 int BWN_PHY_READ (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BWN_PHY_SETMASK (struct bwn_mac*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
bwn_phy_lp_set_txgain_dac(struct bwn_mac *mac, uint16_t dac)
{
	uint16_t ctl;

	ctl = BWN_PHY_READ(mac, BWN_PHY_AFE_DAC_CTL) & 0xc7f;
	ctl |= dac << 7;
	BWN_PHY_SETMASK(mac, BWN_PHY_AFE_DAC_CTL, 0xf000, ctl);
}