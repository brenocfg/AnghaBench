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
 int /*<<< orphan*/  BWN_NPHY_BBCFG ; 
 int BWN_NPHY_BBCFG_RSTCCA ; 
 int BWN_PHY_READ (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BWN_PHY_WRITE (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BWN_RFSEQ_RESET2RX ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  bwn_nphy_force_rf_sequence (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwn_phy_force_clock (struct bwn_mac*,int) ; 

__attribute__((used)) static void bwn_nphy_reset_cca(struct bwn_mac *mac)
{
	uint16_t bbcfg;

	bwn_phy_force_clock(mac, 1);
	bbcfg = BWN_PHY_READ(mac, BWN_NPHY_BBCFG);
	BWN_PHY_WRITE(mac, BWN_NPHY_BBCFG, bbcfg | BWN_NPHY_BBCFG_RSTCCA);
	DELAY(1);
	BWN_PHY_WRITE(mac, BWN_NPHY_BBCFG, bbcfg & ~BWN_NPHY_BBCFG_RSTCCA);
	bwn_phy_force_clock(mac, 0);
	bwn_nphy_force_rf_sequence(mac, BWN_RFSEQ_RESET2RX);
}