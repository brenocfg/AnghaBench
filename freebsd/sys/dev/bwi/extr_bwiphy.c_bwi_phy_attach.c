#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct bwi_softc {int /*<<< orphan*/  sc_dev; } ;
struct bwi_phy {int phy_rev; int phy_version; int /*<<< orphan*/  phy_tbl_data_hi; int /*<<< orphan*/  phy_tbl_data_lo; int /*<<< orphan*/  phy_tbl_ctrl; int /*<<< orphan*/  phy_mode; int /*<<< orphan*/  phy_init; } ;
struct bwi_mac {struct bwi_phy mac_phy; struct bwi_softc* mac_sc; } ;
struct TYPE_3__ {int rev; int /*<<< orphan*/  init; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWI_PHYINFO ; 
 int /*<<< orphan*/  BWI_PHYINFO_REV_MASK ; 
#define  BWI_PHYINFO_TYPE_11A 130 
#define  BWI_PHYINFO_TYPE_11B 129 
#define  BWI_PHYINFO_TYPE_11G 128 
 int /*<<< orphan*/  BWI_PHYINFO_TYPE_MASK ; 
 int /*<<< orphan*/  BWI_PHYINFO_VER_MASK ; 
 int /*<<< orphan*/  BWI_PHYR_TBL_CTRL_11A ; 
 int /*<<< orphan*/  BWI_PHYR_TBL_CTRL_11G ; 
 int /*<<< orphan*/  BWI_PHYR_TBL_DATA_HI_11A ; 
 int /*<<< orphan*/  BWI_PHYR_TBL_DATA_HI_11G ; 
 int /*<<< orphan*/  BWI_PHYR_TBL_DATA_LO_11A ; 
 int /*<<< orphan*/  BWI_PHYR_TBL_DATA_LO_11G ; 
 int /*<<< orphan*/  CSR_READ_2 (struct bwi_softc*,int /*<<< orphan*/ ) ; 
 int ENXIO ; 
 int /*<<< orphan*/  IEEE80211_MODE_11A ; 
 int /*<<< orphan*/  IEEE80211_MODE_11B ; 
 int /*<<< orphan*/  IEEE80211_MODE_11G ; 
 int __SHIFTOUT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwi_phy_init_11a ; 
 int /*<<< orphan*/  bwi_phy_init_11g ; 
 TYPE_1__* bwi_sup_bphy ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,...) ; 
 int nitems (TYPE_1__*) ; 

int
bwi_phy_attach(struct bwi_mac *mac)
{
	struct bwi_softc *sc = mac->mac_sc;
	struct bwi_phy *phy = &mac->mac_phy;
	uint8_t phyrev, phytype, phyver;
	uint16_t val;
	int i;

	/* Get PHY type/revision/version */
	val = CSR_READ_2(sc, BWI_PHYINFO);
	phyrev = __SHIFTOUT(val, BWI_PHYINFO_REV_MASK);
	phytype = __SHIFTOUT(val, BWI_PHYINFO_TYPE_MASK);
	phyver = __SHIFTOUT(val, BWI_PHYINFO_VER_MASK);
	device_printf(sc->sc_dev, "PHY: type %d, rev %d, ver %d\n",
		      phytype, phyrev, phyver);

	/*
	 * Verify whether the revision of the PHY type is supported
	 * Convert PHY type to ieee80211_phymode
	 */
	switch (phytype) {
	case BWI_PHYINFO_TYPE_11A:
		if (phyrev >= 4) {
			device_printf(sc->sc_dev, "unsupported 11A PHY, "
				      "rev %u\n", phyrev);
			return ENXIO;
		}
		phy->phy_init = bwi_phy_init_11a;
		phy->phy_mode = IEEE80211_MODE_11A;
		phy->phy_tbl_ctrl = BWI_PHYR_TBL_CTRL_11A;
		phy->phy_tbl_data_lo = BWI_PHYR_TBL_DATA_LO_11A;
		phy->phy_tbl_data_hi = BWI_PHYR_TBL_DATA_HI_11A;
		break;
	case BWI_PHYINFO_TYPE_11B:
		for (i = 0; i < nitems(bwi_sup_bphy); ++i) {
			if (phyrev == bwi_sup_bphy[i].rev) {
				phy->phy_init = bwi_sup_bphy[i].init;
				break;
			}
		}
		if (i == nitems(bwi_sup_bphy)) {
			device_printf(sc->sc_dev, "unsupported 11B PHY, "
				      "rev %u\n", phyrev);
			return ENXIO;
		}
		phy->phy_mode = IEEE80211_MODE_11B;
		break;
	case BWI_PHYINFO_TYPE_11G:
		if (phyrev > 8) {
			device_printf(sc->sc_dev, "unsupported 11G PHY, "
				      "rev %u\n", phyrev);
			return ENXIO;
		}
		phy->phy_init = bwi_phy_init_11g;
		phy->phy_mode = IEEE80211_MODE_11G;
		phy->phy_tbl_ctrl = BWI_PHYR_TBL_CTRL_11G;
		phy->phy_tbl_data_lo = BWI_PHYR_TBL_DATA_LO_11G;
		phy->phy_tbl_data_hi = BWI_PHYR_TBL_DATA_HI_11G;
		break;
	default:
		device_printf(sc->sc_dev, "unsupported PHY type %d\n",
			      phytype);
		return ENXIO;
	}
	phy->phy_rev = phyrev;
	phy->phy_version = phyver;
	return 0;
}