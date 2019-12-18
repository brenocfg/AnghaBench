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
struct TYPE_2__ {int rf_ver; int rf_rev; } ;
struct bwn_mac {TYPE_1__ mac_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_CHANNEL ; 
 int /*<<< orphan*/  BWN_WRITE_2 (struct bwn_mac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  bwn_phy_g_chan2freq (int) ; 

__attribute__((used)) static void
bwn_spu_workaround(struct bwn_mac *mac, uint8_t channel)
{

	if (mac->mac_phy.rf_ver != 0x2050 || mac->mac_phy.rf_rev >= 6)
		return;
	BWN_WRITE_2(mac, BWN_CHANNEL, (channel <= 10) ?
	    bwn_phy_g_chan2freq(channel + 4) : bwn_phy_g_chan2freq(1));
	DELAY(1000);
	BWN_WRITE_2(mac, BWN_CHANNEL, bwn_phy_g_chan2freq(channel));
}