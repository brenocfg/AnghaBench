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
struct bwi_tpctl {int tp_ctrl2; int tp_ctrl1; } ;
struct bwi_softc {int sc_card_flags; scalar_t__ sc_bbp_id; int sc_bbp_pkg; } ;
struct bwi_rf {int rf_rev; scalar_t__ rf_type; scalar_t__* rf_nrssi; } ;
struct bwi_phy {int phy_rev; int phy_flags; } ;
struct bwi_mac {struct bwi_tpctl mac_tpctl; struct bwi_rf mac_rf; struct bwi_phy mac_phy; struct bwi_softc* mac_sc; } ;

/* Variables and functions */
 scalar_t__ BWI_BBPID_BCM4306 ; 
 int BWI_CARD_F_PA_GPIO9 ; 
 int BWI_CARD_F_SW_NRSSI ; 
 scalar_t__ BWI_INVALID_NRSSI ; 
 int BWI_PHY_F_LINKED ; 
 scalar_t__ BWI_RF_T_BCM2050 ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  PHY_CLRBITS (struct bwi_mac*,int,int) ; 
 int /*<<< orphan*/  PHY_FILT_SETBITS (struct bwi_mac*,int,int,int) ; 
 int PHY_READ (struct bwi_mac*,int) ; 
 int /*<<< orphan*/  PHY_SETBITS (struct bwi_mac*,int,int) ; 
 int /*<<< orphan*/  PHY_WRITE (struct bwi_mac*,int,int) ; 
 int /*<<< orphan*/  RF_FILT_SETBITS (struct bwi_mac*,int,int,int) ; 
 int /*<<< orphan*/  RF_WRITE (struct bwi_mac*,int,int) ; 
 int /*<<< orphan*/  bwi_mac_init_tpctl_11bg (struct bwi_mac*) ; 
 int /*<<< orphan*/  bwi_phy_config_11g (struct bwi_mac*) ; 
 int /*<<< orphan*/  bwi_phy_init_11b_rev5 (struct bwi_mac*) ; 
 int /*<<< orphan*/  bwi_phy_init_11b_rev6 (struct bwi_mac*) ; 
 int /*<<< orphan*/  bwi_rf_calc_nrssi_slope (struct bwi_mac*) ; 
 int /*<<< orphan*/  bwi_rf_get_gains (struct bwi_mac*) ; 
 int /*<<< orphan*/  bwi_rf_init (struct bwi_mac*) ; 
 int /*<<< orphan*/  bwi_rf_init_hw_nrssi_table (struct bwi_mac*,int) ; 
 int /*<<< orphan*/  bwi_rf_lo_adjust (struct bwi_mac*,struct bwi_tpctl const*) ; 
 int /*<<< orphan*/  bwi_rf_lo_update (struct bwi_mac*) ; 
 int /*<<< orphan*/  bwi_rf_set_nrssi_thr (struct bwi_mac*) ; 

__attribute__((used)) static void
bwi_phy_init_11g(struct bwi_mac *mac)
{
	struct bwi_softc *sc = mac->mac_sc;
	struct bwi_phy *phy = &mac->mac_phy;
	struct bwi_rf *rf = &mac->mac_rf;
	const struct bwi_tpctl *tpctl = &mac->mac_tpctl;

	if (phy->phy_rev == 1)
		bwi_phy_init_11b_rev5(mac);
	else
		bwi_phy_init_11b_rev6(mac);

	if (phy->phy_rev >= 2 || (phy->phy_flags & BWI_PHY_F_LINKED))
		bwi_phy_config_11g(mac);

	if (phy->phy_rev >= 2) {
		PHY_WRITE(mac, 0x814, 0);
		PHY_WRITE(mac, 0x815, 0);

		if (phy->phy_rev == 2) {
			PHY_WRITE(mac, 0x811, 0);
			PHY_WRITE(mac, 0x15, 0xc0);
		} else if (phy->phy_rev > 5) {
			PHY_WRITE(mac, 0x811, 0x400);
			PHY_WRITE(mac, 0x15, 0xc0);
		}
	}

	if (phy->phy_rev >= 2 || (phy->phy_flags & BWI_PHY_F_LINKED)) {
		uint16_t val;

		val = PHY_READ(mac, 0x400) & 0xff;
		if (val == 3 || val == 5) {
			PHY_WRITE(mac, 0x4c2, 0x1816);
			PHY_WRITE(mac, 0x4c3, 0x8006);
			if (val == 5) {
				PHY_FILT_SETBITS(mac, 0x4cc,
						 0xff, 0x1f00);
			}
		}
	}

	if ((phy->phy_rev <= 2 && (phy->phy_flags & BWI_PHY_F_LINKED)) ||
	    phy->phy_rev >= 2)
		PHY_WRITE(mac, 0x47e, 0x78);

	if (rf->rf_rev == 8) {
		PHY_SETBITS(mac, 0x801, 0x80);
		PHY_SETBITS(mac, 0x43e, 0x4);
	}

	if (phy->phy_rev >= 2 && (phy->phy_flags & BWI_PHY_F_LINKED))
		bwi_rf_get_gains(mac);

	if (rf->rf_rev != 8)
		bwi_rf_init(mac);

	if (tpctl->tp_ctrl2 == 0xffff) {
		bwi_rf_lo_update(mac);
	} else {
		if (rf->rf_type == BWI_RF_T_BCM2050 && rf->rf_rev == 8) {
			RF_WRITE(mac, 0x52,
				 (tpctl->tp_ctrl1 << 4) | tpctl->tp_ctrl2);
		} else {
			RF_FILT_SETBITS(mac, 0x52, 0xfff0, tpctl->tp_ctrl2);
		}

		if (phy->phy_rev >= 6) {
			PHY_FILT_SETBITS(mac, 0x36, 0xfff,
					 tpctl->tp_ctrl2 << 12);
		}

		if (sc->sc_card_flags & BWI_CARD_F_PA_GPIO9)
			PHY_WRITE(mac, 0x2e, 0x8075);
		else
			PHY_WRITE(mac, 0x2e, 0x807f);

		if (phy->phy_rev < 2)
			PHY_WRITE(mac, 0x2f, 0x101);
		else
			PHY_WRITE(mac, 0x2f, 0x202);
	}

	if ((phy->phy_flags & BWI_PHY_F_LINKED) || phy->phy_rev >= 2) {
		bwi_rf_lo_adjust(mac, tpctl);
		PHY_WRITE(mac, 0x80f, 0x8078);
	}

	if ((sc->sc_card_flags & BWI_CARD_F_SW_NRSSI) == 0) {
		bwi_rf_init_hw_nrssi_table(mac, 0xffff /* XXX */);
		bwi_rf_set_nrssi_thr(mac);
	} else if ((phy->phy_flags & BWI_PHY_F_LINKED) || phy->phy_rev >= 2) {
		if (rf->rf_nrssi[0] == BWI_INVALID_NRSSI) {
			KASSERT(rf->rf_nrssi[1] == BWI_INVALID_NRSSI,
			    ("rf_nrssi[1] %d", rf->rf_nrssi[1]));
			bwi_rf_calc_nrssi_slope(mac);
		} else {
			KASSERT(rf->rf_nrssi[1] != BWI_INVALID_NRSSI,
			    ("rf_nrssi[1] %d", rf->rf_nrssi[1]));
			bwi_rf_set_nrssi_thr(mac);
		}
	}

	if (rf->rf_rev == 8)
		PHY_WRITE(mac, 0x805, 0x3230);

	bwi_mac_init_tpctl_11bg(mac);

	if (sc->sc_bbp_id == BWI_BBPID_BCM4306 && sc->sc_bbp_pkg == 2) {
		PHY_CLRBITS(mac, 0x429, 0x4000);
		PHY_CLRBITS(mac, 0x4c3, 0x8000);
	}
}