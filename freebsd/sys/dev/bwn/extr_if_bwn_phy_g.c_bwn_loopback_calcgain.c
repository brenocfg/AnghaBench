#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_3__ {int board_flags; } ;
struct bwn_softc {TYPE_1__ sc_board_info; } ;
struct TYPE_4__ {int att; } ;
struct bwn_phy_g {int pg_max_lb_gain; int pg_trsw_rx_gain; TYPE_2__ pg_bbatt; } ;
struct bwn_phy {int rev; int rf_rev; struct bwn_phy_g phy_g; } ;
struct bwn_mac {struct bwn_softc* mac_sc; struct bwn_phy mac_phy; } ;

/* Variables and functions */
 int BHND_BFL_EXTLNA ; 
 int /*<<< orphan*/  BWN_PHY_ANALOGOVER ; 
 int /*<<< orphan*/  BWN_PHY_ANALOGOVERVAL ; 
 int /*<<< orphan*/  BWN_PHY_CCK (int) ; 
 int /*<<< orphan*/  BWN_PHY_CCKBBANDCFG ; 
 int /*<<< orphan*/  BWN_PHY_CRS0 ; 
 int /*<<< orphan*/  BWN_PHY_LO_CTL ; 
 int /*<<< orphan*/  BWN_PHY_LO_LEAKAGE ; 
 int /*<<< orphan*/  BWN_PHY_LO_MASK ; 
 int /*<<< orphan*/  BWN_PHY_MASK (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BWN_PHY_PGACTL ; 
 int BWN_PHY_READ (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BWN_PHY_RFOVER ; 
 int /*<<< orphan*/  BWN_PHY_RFOVERVAL ; 
 int /*<<< orphan*/  BWN_PHY_SET (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BWN_PHY_SETMASK (struct bwn_mac*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  BWN_PHY_WRITE (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BWN_RF_MASK (struct bwn_mac*,int,int) ; 
 int BWN_RF_READ (struct bwn_mac*,int) ; 
 int /*<<< orphan*/  BWN_RF_SETMASK (struct bwn_mac*,int,int,int) ; 
 int /*<<< orphan*/  BWN_RF_WRITE (struct bwn_mac*,int,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  bwn_phy_g_set_bbatt (struct bwn_mac*,int) ; 

__attribute__((used)) static void
bwn_loopback_calcgain(struct bwn_mac *mac)
{
	struct bwn_phy *phy = &mac->mac_phy;
	struct bwn_phy_g *pg = &phy->phy_g;
	struct bwn_softc *sc = mac->mac_sc;
	uint16_t backup_phy[16] = { 0 };
	uint16_t backup_radio[3];
	uint16_t backup_bband;
	uint16_t i, j, loop_i_max;
	uint16_t trsw_rx;
	uint16_t loop1_outer_done, loop1_inner_done;

	backup_phy[0] = BWN_PHY_READ(mac, BWN_PHY_CRS0);
	backup_phy[1] = BWN_PHY_READ(mac, BWN_PHY_CCKBBANDCFG);
	backup_phy[2] = BWN_PHY_READ(mac, BWN_PHY_RFOVER);
	backup_phy[3] = BWN_PHY_READ(mac, BWN_PHY_RFOVERVAL);
	if (phy->rev != 1) {
		backup_phy[4] = BWN_PHY_READ(mac, BWN_PHY_ANALOGOVER);
		backup_phy[5] = BWN_PHY_READ(mac, BWN_PHY_ANALOGOVERVAL);
	}
	backup_phy[6] = BWN_PHY_READ(mac, BWN_PHY_CCK(0x5a));
	backup_phy[7] = BWN_PHY_READ(mac, BWN_PHY_CCK(0x59));
	backup_phy[8] = BWN_PHY_READ(mac, BWN_PHY_CCK(0x58));
	backup_phy[9] = BWN_PHY_READ(mac, BWN_PHY_CCK(0x0a));
	backup_phy[10] = BWN_PHY_READ(mac, BWN_PHY_CCK(0x03));
	backup_phy[11] = BWN_PHY_READ(mac, BWN_PHY_LO_MASK);
	backup_phy[12] = BWN_PHY_READ(mac, BWN_PHY_LO_CTL);
	backup_phy[13] = BWN_PHY_READ(mac, BWN_PHY_CCK(0x2b));
	backup_phy[14] = BWN_PHY_READ(mac, BWN_PHY_PGACTL);
	backup_phy[15] = BWN_PHY_READ(mac, BWN_PHY_LO_LEAKAGE);
	backup_bband = pg->pg_bbatt.att;
	backup_radio[0] = BWN_RF_READ(mac, 0x52);
	backup_radio[1] = BWN_RF_READ(mac, 0x43);
	backup_radio[2] = BWN_RF_READ(mac, 0x7a);

	BWN_PHY_MASK(mac, BWN_PHY_CRS0, 0x3fff);
	BWN_PHY_SET(mac, BWN_PHY_CCKBBANDCFG, 0x8000);
	BWN_PHY_SET(mac, BWN_PHY_RFOVER, 0x0002);
	BWN_PHY_MASK(mac, BWN_PHY_RFOVERVAL, 0xfffd);
	BWN_PHY_SET(mac, BWN_PHY_RFOVER, 0x0001);
	BWN_PHY_MASK(mac, BWN_PHY_RFOVERVAL, 0xfffe);
	if (phy->rev != 1) {
		BWN_PHY_SET(mac, BWN_PHY_ANALOGOVER, 0x0001);
		BWN_PHY_MASK(mac, BWN_PHY_ANALOGOVERVAL, 0xfffe);
		BWN_PHY_SET(mac, BWN_PHY_ANALOGOVER, 0x0002);
		BWN_PHY_MASK(mac, BWN_PHY_ANALOGOVERVAL, 0xfffd);
	}
	BWN_PHY_SET(mac, BWN_PHY_RFOVER, 0x000c);
	BWN_PHY_SET(mac, BWN_PHY_RFOVERVAL, 0x000c);
	BWN_PHY_SET(mac, BWN_PHY_RFOVER, 0x0030);
	BWN_PHY_SETMASK(mac, BWN_PHY_RFOVERVAL, 0xffcf, 0x10);

	BWN_PHY_WRITE(mac, BWN_PHY_CCK(0x5a), 0x0780);
	BWN_PHY_WRITE(mac, BWN_PHY_CCK(0x59), 0xc810);
	BWN_PHY_WRITE(mac, BWN_PHY_CCK(0x58), 0x000d);

	BWN_PHY_SET(mac, BWN_PHY_CCK(0x0a), 0x2000);
	if (phy->rev != 1) {
		BWN_PHY_SET(mac, BWN_PHY_ANALOGOVER, 0x0004);
		BWN_PHY_MASK(mac, BWN_PHY_ANALOGOVERVAL, 0xfffb);
	}
	BWN_PHY_SETMASK(mac, BWN_PHY_CCK(0x03), 0xff9f, 0x40);

	if (phy->rf_rev == 8)
		BWN_RF_WRITE(mac, 0x43, 0x000f);
	else {
		BWN_RF_WRITE(mac, 0x52, 0);
		BWN_RF_SETMASK(mac, 0x43, 0xfff0, 0x9);
	}
	bwn_phy_g_set_bbatt(mac, 11);

	if (phy->rev >= 3)
		BWN_PHY_WRITE(mac, BWN_PHY_LO_MASK, 0xc020);
	else
		BWN_PHY_WRITE(mac, BWN_PHY_LO_MASK, 0x8020);
	BWN_PHY_WRITE(mac, BWN_PHY_LO_CTL, 0);

	BWN_PHY_SETMASK(mac, BWN_PHY_CCK(0x2b), 0xffc0, 0x01);
	BWN_PHY_SETMASK(mac, BWN_PHY_CCK(0x2b), 0xc0ff, 0x800);

	BWN_PHY_SET(mac, BWN_PHY_RFOVER, 0x0100);
	BWN_PHY_MASK(mac, BWN_PHY_RFOVERVAL, 0xcfff);

	if (sc->sc_board_info.board_flags & BHND_BFL_EXTLNA) {
		if (phy->rev >= 7) {
			BWN_PHY_SET(mac, BWN_PHY_RFOVER, 0x0800);
			BWN_PHY_SET(mac, BWN_PHY_RFOVERVAL, 0x8000);
		}
	}
	BWN_RF_MASK(mac, 0x7a, 0x00f7);

	j = 0;
	loop_i_max = (phy->rf_rev == 8) ? 15 : 9;
	for (i = 0; i < loop_i_max; i++) {
		for (j = 0; j < 16; j++) {
			BWN_RF_WRITE(mac, 0x43, i);
			BWN_PHY_SETMASK(mac, BWN_PHY_RFOVERVAL, 0xf0ff,
			    (j << 8));
			BWN_PHY_SETMASK(mac, BWN_PHY_PGACTL, 0x0fff, 0xa000);
			BWN_PHY_SET(mac, BWN_PHY_PGACTL, 0xf000);
			DELAY(20);
			if (BWN_PHY_READ(mac, BWN_PHY_LO_LEAKAGE) >= 0xdfc)
				goto done0;
		}
	}
done0:
	loop1_outer_done = i;
	loop1_inner_done = j;
	if (j >= 8) {
		BWN_PHY_SET(mac, BWN_PHY_RFOVERVAL, 0x30);
		trsw_rx = 0x1b;
		for (j = j - 8; j < 16; j++) {
			BWN_PHY_SETMASK(mac, BWN_PHY_RFOVERVAL, 0xf0ff, j << 8);
			BWN_PHY_SETMASK(mac, BWN_PHY_PGACTL, 0x0fff, 0xa000);
			BWN_PHY_SET(mac, BWN_PHY_PGACTL, 0xf000);
			DELAY(20);
			trsw_rx -= 3;
			if (BWN_PHY_READ(mac, BWN_PHY_LO_LEAKAGE) >= 0xdfc)
				goto done1;
		}
	} else
		trsw_rx = 0x18;
done1:

	if (phy->rev != 1) {
		BWN_PHY_WRITE(mac, BWN_PHY_ANALOGOVER, backup_phy[4]);
		BWN_PHY_WRITE(mac, BWN_PHY_ANALOGOVERVAL, backup_phy[5]);
	}
	BWN_PHY_WRITE(mac, BWN_PHY_CCK(0x5a), backup_phy[6]);
	BWN_PHY_WRITE(mac, BWN_PHY_CCK(0x59), backup_phy[7]);
	BWN_PHY_WRITE(mac, BWN_PHY_CCK(0x58), backup_phy[8]);
	BWN_PHY_WRITE(mac, BWN_PHY_CCK(0x0a), backup_phy[9]);
	BWN_PHY_WRITE(mac, BWN_PHY_CCK(0x03), backup_phy[10]);
	BWN_PHY_WRITE(mac, BWN_PHY_LO_MASK, backup_phy[11]);
	BWN_PHY_WRITE(mac, BWN_PHY_LO_CTL, backup_phy[12]);
	BWN_PHY_WRITE(mac, BWN_PHY_CCK(0x2b), backup_phy[13]);
	BWN_PHY_WRITE(mac, BWN_PHY_PGACTL, backup_phy[14]);

	bwn_phy_g_set_bbatt(mac, backup_bband);

	BWN_RF_WRITE(mac, 0x52, backup_radio[0]);
	BWN_RF_WRITE(mac, 0x43, backup_radio[1]);
	BWN_RF_WRITE(mac, 0x7a, backup_radio[2]);

	BWN_PHY_WRITE(mac, BWN_PHY_RFOVER, backup_phy[2] | 0x0003);
	DELAY(10);
	BWN_PHY_WRITE(mac, BWN_PHY_RFOVER, backup_phy[2]);
	BWN_PHY_WRITE(mac, BWN_PHY_RFOVERVAL, backup_phy[3]);
	BWN_PHY_WRITE(mac, BWN_PHY_CRS0, backup_phy[0]);
	BWN_PHY_WRITE(mac, BWN_PHY_CCKBBANDCFG, backup_phy[1]);

	pg->pg_max_lb_gain =
	    ((loop1_inner_done * 6) - (loop1_outer_done * 4)) - 11;
	pg->pg_trsw_rx_gain = trsw_rx * 2;
}