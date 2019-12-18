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
typedef  int u_int ;
struct bwi_softc {int sc_card_flags; } ;
struct bwi_rf {int rf_rev; int rf_curchan; } ;
struct bwi_phy {scalar_t__ phy_mode; int phy_version; } ;
struct bwi_mac {struct bwi_phy mac_phy; struct bwi_rf mac_rf; struct bwi_softc* mac_sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWI_BBP_ATTEN ; 
 int /*<<< orphan*/  BWI_BBP_ATTEN_MAGIC2 ; 
 int BWI_CARD_F_ALT_IQ ; 
 int BWI_CARD_F_SW_NRSSI ; 
 int /*<<< orphan*/  BWI_HFLAG_MAGIC1 ; 
 int /*<<< orphan*/  BWI_PHY_MAGIC_REG1 ; 
 int /*<<< orphan*/  BWI_PHY_MAGIC_REG1_VAL2 ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct bwi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  HFLAGS_SETBITS (struct bwi_mac*,int /*<<< orphan*/ ) ; 
 scalar_t__ IEEE80211_MODE_11B ; 
 scalar_t__ IEEE80211_MODE_11G ; 
 int /*<<< orphan*/  PHY_CLRBITS (struct bwi_mac*,int,int) ; 
 int /*<<< orphan*/  PHY_FILT_SETBITS (struct bwi_mac*,int,int,int) ; 
 int /*<<< orphan*/  PHY_SETBITS (struct bwi_mac*,int,int) ; 
 int /*<<< orphan*/  PHY_WRITE (struct bwi_mac*,int,int) ; 
 int /*<<< orphan*/  RF_FILT_SETBITS (struct bwi_mac*,int,int,int) ; 
 int /*<<< orphan*/  RF_SETBITS (struct bwi_mac*,int,int) ; 
 int /*<<< orphan*/  RF_WRITE (struct bwi_mac*,int,int) ; 
 int /*<<< orphan*/  bwi_mac_init_tpctl_11bg (struct bwi_mac*) ; 
 int /*<<< orphan*/  bwi_mac_set_tpctl_11bg (struct bwi_mac*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bwi_rf_calc_nrssi_slope (struct bwi_mac*) ; 
 int /*<<< orphan*/  bwi_rf_init_bcm2050 (struct bwi_mac*) ; 
 int /*<<< orphan*/  bwi_rf_lo_update (struct bwi_mac*) ; 
 int /*<<< orphan*/  bwi_rf_set_chan (struct bwi_mac*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwi_rf_set_nrssi_thr (struct bwi_mac*) ; 

__attribute__((used)) static void
bwi_phy_init_11b_rev6(struct bwi_mac *mac)
{
	struct bwi_softc *sc = mac->mac_sc;
	struct bwi_rf *rf = &mac->mac_rf;
	struct bwi_phy *phy = &mac->mac_phy;
	uint16_t val, ofs;
	u_int orig_chan;

	PHY_WRITE(mac, 0x3e, 0x817a);
	RF_SETBITS(mac, 0x7a, 0x58);

	if (rf->rf_rev == 4 || rf->rf_rev == 5) {
		RF_WRITE(mac, 0x51, 0x37);
		RF_WRITE(mac, 0x52, 0x70);
		RF_WRITE(mac, 0x53, 0xb3);
		RF_WRITE(mac, 0x54, 0x9b);
		RF_WRITE(mac, 0x5a, 0x88);
		RF_WRITE(mac, 0x5b, 0x88);
		RF_WRITE(mac, 0x5d, 0x88);
		RF_WRITE(mac, 0x5e, 0x88);
		RF_WRITE(mac, 0x7d, 0x88);
		HFLAGS_SETBITS(mac, BWI_HFLAG_MAGIC1);
	} else if (rf->rf_rev == 8) {
		RF_WRITE(mac, 0x51, 0);
		RF_WRITE(mac, 0x52, 0x40);
		RF_WRITE(mac, 0x53, 0xb7);
		RF_WRITE(mac, 0x54, 0x98);
		RF_WRITE(mac, 0x5a, 0x88);
		RF_WRITE(mac, 0x5b, 0x6b);
		RF_WRITE(mac, 0x5c, 0xf);
		if (sc->sc_card_flags & BWI_CARD_F_ALT_IQ) {
			RF_WRITE(mac, 0x5d, 0xfa);
			RF_WRITE(mac, 0x5e, 0xd8);
		} else {
			RF_WRITE(mac, 0x5d, 0xf5);
			RF_WRITE(mac, 0x5e, 0xb8);
		}
		RF_WRITE(mac, 0x73, 0x3);
		RF_WRITE(mac, 0x7d, 0xa8);
		RF_WRITE(mac, 0x7c, 0x1);
		RF_WRITE(mac, 0x7e, 0x8);
	}

	val = 0x1e1f;
	for (ofs = 0x88; ofs < 0x98; ++ofs) {
		PHY_WRITE(mac, ofs, val);
		val -= 0x202;
	}

	val = 0x3e3f;
	for (ofs = 0x98; ofs < 0xa8; ++ofs) {
		PHY_WRITE(mac, ofs, val);
		val -= 0x202;
	}

	val = 0x2120;
	for (ofs = 0xa8; ofs < 0xc8; ++ofs) {
		PHY_WRITE(mac, ofs, (val & 0x3f3f));
		val += 0x202;

		/* XXX: delay 10 us to avoid PCI parity errors with BCM4318 */
		DELAY(10);
	}

	if (phy->phy_mode == IEEE80211_MODE_11G) {
		RF_SETBITS(mac, 0x7a, 0x20);
		RF_SETBITS(mac, 0x51, 0x4);
		PHY_SETBITS(mac, 0x802, 0x100);
		PHY_SETBITS(mac, 0x42b, 0x2000);
		PHY_WRITE(mac, 0x5b, 0);
		PHY_WRITE(mac, 0x5c, 0);
	}

	/* Force to channel 7 */
	orig_chan = rf->rf_curchan;
	if (orig_chan >= 8)
		bwi_rf_set_chan(mac, 1, 0);
	else
		bwi_rf_set_chan(mac, 13, 0);

	RF_WRITE(mac, 0x50, 0x20);
	RF_WRITE(mac, 0x50, 0x23);

	DELAY(40);

	if (rf->rf_rev < 6 || rf->rf_rev == 8) {
		RF_SETBITS(mac, 0x7c, 0x2);
		RF_WRITE(mac, 0x50, 0x20);
	}
	if (rf->rf_rev <= 2) {
		RF_WRITE(mac, 0x7c, 0x20);
		RF_WRITE(mac, 0x5a, 0x70);
		RF_WRITE(mac, 0x5b, 0x7b);
		RF_WRITE(mac, 0x5c, 0xb0);
	}

	RF_FILT_SETBITS(mac, 0x7a, 0xf8, 0x7);

	bwi_rf_set_chan(mac, orig_chan, 0);

	PHY_WRITE(mac, 0x14, 0x200);
	if (rf->rf_rev >= 6)
		PHY_WRITE(mac, 0x2a, 0x88c2);
	else
		PHY_WRITE(mac, 0x2a, 0x8ac0);
	PHY_WRITE(mac, 0x38, 0x668);

	bwi_mac_set_tpctl_11bg(mac, NULL);

	if (rf->rf_rev <= 5) {
		PHY_FILT_SETBITS(mac, 0x5d, 0xff80, 0x3);
		if (rf->rf_rev <= 2)
			RF_WRITE(mac, 0x5d, 0xd);
	}

	if (phy->phy_version == 4) {
		CSR_WRITE_2(sc, BWI_PHY_MAGIC_REG1, BWI_PHY_MAGIC_REG1_VAL2);
		PHY_CLRBITS(mac, 0x61, 0xf000);
	} else {
		PHY_FILT_SETBITS(mac, 0x2, 0xffc0, 0x4);
	}

	if (phy->phy_mode == IEEE80211_MODE_11B) {
		CSR_WRITE_2(sc, BWI_BBP_ATTEN, BWI_BBP_ATTEN_MAGIC2);
		PHY_WRITE(mac, 0x16, 0x410);
		PHY_WRITE(mac, 0x17, 0x820);
		PHY_WRITE(mac, 0x62, 0x7);

		bwi_rf_init_bcm2050(mac);
		bwi_rf_lo_update(mac);
		if (sc->sc_card_flags & BWI_CARD_F_SW_NRSSI) {
			bwi_rf_calc_nrssi_slope(mac);
			bwi_rf_set_nrssi_thr(mac);
		}
		bwi_mac_init_tpctl_11bg(mac);
	} else {
		CSR_WRITE_2(sc, BWI_BBP_ATTEN, 0);
	}
}