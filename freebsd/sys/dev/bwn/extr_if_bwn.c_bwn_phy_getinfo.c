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
typedef  int uint32_t ;
struct bwn_softc {int /*<<< orphan*/  sc_dev; } ;
struct bwn_phy {int gmode; int rf_on; int analog; int type; int rev; int rf_rev; int rf_ver; int rf_manuf; int phy_do_full_init; } ;
struct bwn_mac {struct bwn_softc* mac_sc; struct bwn_phy mac_phy; } ;

/* Variables and functions */
 int BWN_PHYTYPE_A ; 
 int BWN_PHYTYPE_B ; 
 int BWN_PHYTYPE_G ; 
 int BWN_PHYTYPE_LP ; 
 int BWN_PHYTYPE_N ; 
 int /*<<< orphan*/  BWN_PHYVER ; 
 int BWN_PHYVER_ANALOG ; 
 int BWN_PHYVER_TYPE ; 
 int BWN_PHYVER_VERSION ; 
 int BWN_READ_2 (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BWN_RFCTL ; 
 int /*<<< orphan*/  BWN_RFCTL_ID ; 
 int /*<<< orphan*/  BWN_RFDATAHI ; 
 int /*<<< orphan*/  BWN_RFDATALO ; 
 int /*<<< orphan*/  BWN_WRITE_2 (struct bwn_mac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ENXIO ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int,int) ; 

__attribute__((used)) static int
bwn_phy_getinfo(struct bwn_mac *mac, int gmode)
{
	struct bwn_phy *phy = &mac->mac_phy;
	struct bwn_softc *sc = mac->mac_sc;
	uint32_t tmp;

	/* PHY */
	tmp = BWN_READ_2(mac, BWN_PHYVER);
	phy->gmode = gmode;
	phy->rf_on = 1;
	phy->analog = (tmp & BWN_PHYVER_ANALOG) >> 12;
	phy->type = (tmp & BWN_PHYVER_TYPE) >> 8;
	phy->rev = (tmp & BWN_PHYVER_VERSION);
	if ((phy->type == BWN_PHYTYPE_A && phy->rev >= 4) ||
	    (phy->type == BWN_PHYTYPE_B && phy->rev != 2 &&
		phy->rev != 4 && phy->rev != 6 && phy->rev != 7) ||
	    (phy->type == BWN_PHYTYPE_G && phy->rev > 9) ||
	    (phy->type == BWN_PHYTYPE_N && phy->rev > 6) ||
	    (phy->type == BWN_PHYTYPE_LP && phy->rev > 2))
		goto unsupphy;

	/* RADIO */
	BWN_WRITE_2(mac, BWN_RFCTL, BWN_RFCTL_ID);
	tmp = BWN_READ_2(mac, BWN_RFDATALO);
	BWN_WRITE_2(mac, BWN_RFCTL, BWN_RFCTL_ID);
	tmp |= (uint32_t)BWN_READ_2(mac, BWN_RFDATAHI) << 16;

	phy->rf_rev = (tmp & 0xf0000000) >> 28;
	phy->rf_ver = (tmp & 0x0ffff000) >> 12;
	phy->rf_manuf = (tmp & 0x00000fff);

	/*
	 * For now, just always do full init (ie, what bwn has traditionally
	 * done)
	 */
	phy->phy_do_full_init = 1;

	if (phy->rf_manuf != 0x17f)	/* 0x17f is broadcom */
		goto unsupradio;
	if ((phy->type == BWN_PHYTYPE_A && (phy->rf_ver != 0x2060 ||
	     phy->rf_rev != 1 || phy->rf_manuf != 0x17f)) ||
	    (phy->type == BWN_PHYTYPE_B && (phy->rf_ver & 0xfff0) != 0x2050) ||
	    (phy->type == BWN_PHYTYPE_G && phy->rf_ver != 0x2050) ||
	    (phy->type == BWN_PHYTYPE_N &&
	     phy->rf_ver != 0x2055 && phy->rf_ver != 0x2056) ||
	    (phy->type == BWN_PHYTYPE_LP &&
	     phy->rf_ver != 0x2062 && phy->rf_ver != 0x2063))
		goto unsupradio;

	return (0);
unsupphy:
	device_printf(sc->sc_dev, "unsupported PHY (type %#x, rev %#x, "
	    "analog %#x)\n",
	    phy->type, phy->rev, phy->analog);
	return (ENXIO);
unsupradio:
	device_printf(sc->sc_dev, "unsupported radio (manuf %#x, ver %#x, "
	    "rev %#x)\n",
	    phy->rf_manuf, phy->rf_ver, phy->rf_rev);
	return (ENXIO);
}