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
 int /*<<< orphan*/  BWN_PHY_OFDM (int) ; 
 int /*<<< orphan*/  BWN_PHY_SETMASK (struct bwn_mac*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
bwn_phy_lp_set_txgain_pa(struct bwn_mac *mac, uint16_t gain)
{

	BWN_PHY_SETMASK(mac, BWN_PHY_OFDM(0xfb), 0xe03f, gain << 6);
	BWN_PHY_SETMASK(mac, BWN_PHY_OFDM(0xfd), 0x80ff, gain << 8);
}