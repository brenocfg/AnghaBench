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
struct timespec {int tv_nsec; int tv_sec; } ;
struct bwn_txpwr_loctl {int /*<<< orphan*/  txctl_measured_time; } ;
struct TYPE_2__ {int board_flags; } ;
struct bwn_softc {TYPE_1__ sc_board_info; } ;
struct bwn_phy_g {struct bwn_txpwr_loctl pg_loctl; } ;
struct bwn_phy {scalar_t__ type; int rf_ver; int rf_rev; int rev; struct bwn_phy_g phy_g; } ;
struct bwn_mac {struct bwn_softc* mac_sc; struct bwn_phy mac_phy; } ;
struct bwn_lo_g_value {int reg0; int reg1; int rf1; int phy_syncctl; int rf2; void* phy_cck1; void* phy_cck0; void* phy_dacctl; void* phy_cck2; void* phy_pgactl; void* rf0; void* phy_crs0; void* phy_cck3; void* phy_classctl; void* phy_rfoverval; void* phy_rfover; void* phy_analogoverval; void* phy_analogover; void* phy_hpwr_tssictl; void* phy_cck4; void* phy_dacctl_hwpctl; void* phy_extg; void* phy_lomask; } ;

/* Variables and functions */
 int BHND_BFL_EXTLNA ; 
 int /*<<< orphan*/  BWN_HAS_TXMAG (struct bwn_phy*) ; 
 scalar_t__ BWN_LO_TXCTL_EXPIRE ; 
 scalar_t__ BWN_PHYTYPE_B ; 
 scalar_t__ BWN_PHYTYPE_G ; 
 int BWN_PHY_ANALOGOVER ; 
 int BWN_PHY_ANALOGOVERVAL ; 
 int BWN_PHY_CCK (int) ; 
 int BWN_PHY_CLASSCTL ; 
 int BWN_PHY_CRS0 ; 
 int BWN_PHY_DACCTL ; 
 int BWN_PHY_EXTG (int) ; 
 int BWN_PHY_HPWR_TSSICTL ; 
 int BWN_PHY_LO_MASK ; 
 int /*<<< orphan*/  BWN_PHY_MASK (struct bwn_mac*,int,int) ; 
 int BWN_PHY_PGACTL ; 
 void* BWN_PHY_READ (struct bwn_mac*,int) ; 
 int BWN_PHY_RFOVER ; 
 int BWN_PHY_RFOVERVAL ; 
 int /*<<< orphan*/  BWN_PHY_SET (struct bwn_mac*,int,int) ; 
 int BWN_PHY_SYNCCTL ; 
 int /*<<< orphan*/  BWN_PHY_WRITE (struct bwn_mac*,int,int) ; 
 int BWN_READ_2 (struct bwn_mac*,int) ; 
 void* BWN_RF_READ (struct bwn_mac*,int) ; 
 int /*<<< orphan*/  BWN_RF_WRITE (struct bwn_mac*,int,int) ; 
 int /*<<< orphan*/  BWN_WRITE_2 (struct bwn_mac*,int,int) ; 
 int /*<<< orphan*/  bwn_dummy_transmission (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ bwn_has_hwpctl (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_lo_measure_txctl_values (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_phy_g_switch_chan (struct bwn_mac*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_time_before (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  nanouptime (struct timespec*) ; 

__attribute__((used)) static void
bwn_lo_save(struct bwn_mac *mac, struct bwn_lo_g_value *sav)
{
	struct bwn_phy *phy = &mac->mac_phy;
	struct bwn_phy_g *pg = &phy->phy_g;
	struct bwn_softc *sc = mac->mac_sc;
	struct bwn_txpwr_loctl *lo = &pg->pg_loctl;
	struct timespec ts;
	uint16_t tmp;

	if (bwn_has_hwpctl(mac)) {
		sav->phy_lomask = BWN_PHY_READ(mac, BWN_PHY_LO_MASK);
		sav->phy_extg = BWN_PHY_READ(mac, BWN_PHY_EXTG(0x01));
		sav->phy_dacctl_hwpctl = BWN_PHY_READ(mac, BWN_PHY_DACCTL);
		sav->phy_cck4 = BWN_PHY_READ(mac, BWN_PHY_CCK(0x14));
		sav->phy_hpwr_tssictl = BWN_PHY_READ(mac, BWN_PHY_HPWR_TSSICTL);

		BWN_PHY_SET(mac, BWN_PHY_HPWR_TSSICTL, 0x100);
		BWN_PHY_SET(mac, BWN_PHY_EXTG(0x01), 0x40);
		BWN_PHY_SET(mac, BWN_PHY_DACCTL, 0x40);
		BWN_PHY_SET(mac, BWN_PHY_CCK(0x14), 0x200);
	}
	if (phy->type == BWN_PHYTYPE_B &&
	    phy->rf_ver == 0x2050 && phy->rf_rev < 6) {
		BWN_PHY_WRITE(mac, BWN_PHY_CCK(0x16), 0x410);
		BWN_PHY_WRITE(mac, BWN_PHY_CCK(0x17), 0x820);
	}
	if (phy->rev >= 2) {
		sav->phy_analogover = BWN_PHY_READ(mac, BWN_PHY_ANALOGOVER);
		sav->phy_analogoverval =
		    BWN_PHY_READ(mac, BWN_PHY_ANALOGOVERVAL);
		sav->phy_rfover = BWN_PHY_READ(mac, BWN_PHY_RFOVER);
		sav->phy_rfoverval = BWN_PHY_READ(mac, BWN_PHY_RFOVERVAL);
		sav->phy_classctl = BWN_PHY_READ(mac, BWN_PHY_CLASSCTL);
		sav->phy_cck3 = BWN_PHY_READ(mac, BWN_PHY_CCK(0x3e));
		sav->phy_crs0 = BWN_PHY_READ(mac, BWN_PHY_CRS0);

		BWN_PHY_MASK(mac, BWN_PHY_CLASSCTL, 0xfffc);
		BWN_PHY_MASK(mac, BWN_PHY_CRS0, 0x7fff);
		BWN_PHY_SET(mac, BWN_PHY_ANALOGOVER, 0x0003);
		BWN_PHY_MASK(mac, BWN_PHY_ANALOGOVERVAL, 0xfffc);
		if (phy->type == BWN_PHYTYPE_G) {
			if ((phy->rev >= 7) &&
			    (sc->sc_board_info.board_flags &
			     BHND_BFL_EXTLNA)) {
				BWN_PHY_WRITE(mac, BWN_PHY_RFOVER, 0x933);
			} else {
				BWN_PHY_WRITE(mac, BWN_PHY_RFOVER, 0x133);
			}
		} else {
			BWN_PHY_WRITE(mac, BWN_PHY_RFOVER, 0);
		}
		BWN_PHY_WRITE(mac, BWN_PHY_CCK(0x3e), 0);
	}
	sav->reg0 = BWN_READ_2(mac, 0x3f4);
	sav->reg1 = BWN_READ_2(mac, 0x3e2);
	sav->rf0 = BWN_RF_READ(mac, 0x43);
	sav->rf1 = BWN_RF_READ(mac, 0x7a);
	sav->phy_pgactl = BWN_PHY_READ(mac, BWN_PHY_PGACTL);
	sav->phy_cck2 = BWN_PHY_READ(mac, BWN_PHY_CCK(0x2a));
	sav->phy_syncctl = BWN_PHY_READ(mac, BWN_PHY_SYNCCTL);
	sav->phy_dacctl = BWN_PHY_READ(mac, BWN_PHY_DACCTL);

	if (!BWN_HAS_TXMAG(phy)) {
		sav->rf2 = BWN_RF_READ(mac, 0x52);
		sav->rf2 &= 0x00f0;
	}
	if (phy->type == BWN_PHYTYPE_B) {
		sav->phy_cck0 = BWN_PHY_READ(mac, BWN_PHY_CCK(0x30));
		sav->phy_cck1 = BWN_PHY_READ(mac, BWN_PHY_CCK(0x06));
		BWN_PHY_WRITE(mac, BWN_PHY_CCK(0x30), 0x00ff);
		BWN_PHY_WRITE(mac, BWN_PHY_CCK(0x06), 0x3f3f);
	} else {
		BWN_WRITE_2(mac, 0x3e2, BWN_READ_2(mac, 0x3e2)
			    | 0x8000);
	}
	BWN_WRITE_2(mac, 0x3f4, BWN_READ_2(mac, 0x3f4)
		    & 0xf000);

	tmp =
	    (phy->type == BWN_PHYTYPE_G) ? BWN_PHY_LO_MASK : BWN_PHY_CCK(0x2e);
	BWN_PHY_WRITE(mac, tmp, 0x007f);

	tmp = sav->phy_syncctl;
	BWN_PHY_WRITE(mac, BWN_PHY_SYNCCTL, tmp & 0xff7f);
	tmp = sav->rf1;
	BWN_RF_WRITE(mac, 0x007a, tmp & 0xfff0);

	BWN_PHY_WRITE(mac, BWN_PHY_CCK(0x2a), 0x8a3);
	if (phy->type == BWN_PHYTYPE_G ||
	    (phy->type == BWN_PHYTYPE_B &&
	     phy->rf_ver == 0x2050 && phy->rf_rev >= 6)) {
		BWN_PHY_WRITE(mac, BWN_PHY_CCK(0x2b), 0x1003);
	} else
		BWN_PHY_WRITE(mac, BWN_PHY_CCK(0x2b), 0x0802);
	if (phy->rev >= 2)
		bwn_dummy_transmission(mac, 0, 1);
	bwn_phy_g_switch_chan(mac, 6, 0);
	BWN_RF_READ(mac, 0x51);
	if (phy->type == BWN_PHYTYPE_G)
		BWN_PHY_WRITE(mac, BWN_PHY_CCK(0x2f), 0);

	nanouptime(&ts);
	if (ieee80211_time_before(lo->txctl_measured_time,
	    (ts.tv_nsec / 1000000 + ts.tv_sec * 1000) - BWN_LO_TXCTL_EXPIRE))
		bwn_lo_measure_txctl_values(mac);

	if (phy->type == BWN_PHYTYPE_G && phy->rev >= 3)
		BWN_PHY_WRITE(mac, BWN_PHY_LO_MASK, 0xc078);
	else {
		if (phy->type == BWN_PHYTYPE_B)
			BWN_PHY_WRITE(mac, BWN_PHY_CCK(0x2e), 0x8078);
		else
			BWN_PHY_WRITE(mac, BWN_PHY_LO_MASK, 0x8078);
	}
}