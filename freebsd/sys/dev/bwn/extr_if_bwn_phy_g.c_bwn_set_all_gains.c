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
struct bwn_phy {int rev; } ;
struct bwn_mac {struct bwn_phy mac_phy; } ;
typedef  int int16_t ;

/* Variables and functions */
 int BWN_OFDMTAB_GAINX ; 
 int BWN_OFDMTAB_GAINX_R1 ; 
 int /*<<< orphan*/  BWN_PHY_SETMASK (struct bwn_mac*,int,int,int) ; 
 int /*<<< orphan*/  bwn_dummy_transmission (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bwn_ofdmtab_write_2 (struct bwn_mac*,int,int,int) ; 

__attribute__((used)) static void
bwn_set_all_gains(struct bwn_mac *mac, int16_t first, int16_t second,
    int16_t third)
{
	struct bwn_phy *phy = &mac->mac_phy;
	uint16_t i;
	uint16_t start = 0x08, end = 0x18;
	uint16_t tmp;
	uint16_t table;

	if (phy->rev <= 1) {
		start = 0x10;
		end = 0x20;
	}

	table = BWN_OFDMTAB_GAINX;
	if (phy->rev <= 1)
		table = BWN_OFDMTAB_GAINX_R1;
	for (i = 0; i < 4; i++)
		bwn_ofdmtab_write_2(mac, table, i, first);

	for (i = start; i < end; i++)
		bwn_ofdmtab_write_2(mac, table, i, second);

	if (third != -1) {
		tmp = ((uint16_t) third << 14) | ((uint16_t) third << 6);
		BWN_PHY_SETMASK(mac, 0x04a0, 0xbfbf, tmp);
		BWN_PHY_SETMASK(mac, 0x04a1, 0xbfbf, tmp);
		BWN_PHY_SETMASK(mac, 0x04a2, 0xbfbf, tmp);
	}
	bwn_dummy_transmission(mac, 0, 1);
}