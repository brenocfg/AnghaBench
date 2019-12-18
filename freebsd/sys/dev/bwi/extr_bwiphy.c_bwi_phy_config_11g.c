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
struct bwi_softc {int sc_pci_revid; int sc_card_flags; } ;
struct bwi_phy {int phy_rev; } ;
struct bwi_mac {struct bwi_phy mac_phy; struct bwi_softc* mac_sc; } ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int BWI_CARD_F_PA_GPIO9 ; 
 scalar_t__ BWI_IS_BRCM_BU4306 (struct bwi_softc*) ; 
 scalar_t__ BWI_PHYTBL_DELAY ; 
 int BWI_PHYTBL_FREQ ; 
 int BWI_PHYTBL_NOISE ; 
 int BWI_PHYTBL_NOISE_SCALE ; 
 scalar_t__ BWI_PHYTBL_ROTOR ; 
 int BWI_PHYTBL_RSSI ; 
 int BWI_PHYTBL_SIGMA_SQ ; 
 int BWI_PHYTBL_WRSSI ; 
 int BWI_PHYTBL_WRSSI_REV1 ; 
 int /*<<< orphan*/  PHY_FILT_SETBITS (struct bwi_mac*,int,int,int) ; 
 int PHY_READ (struct bwi_mac*,int) ; 
 int /*<<< orphan*/  PHY_SETBITS (struct bwi_mac*,int,int) ; 
 int /*<<< orphan*/  PHY_WRITE (struct bwi_mac*,int,int) ; 
 int /*<<< orphan*/  bwi_nrssi_write (struct bwi_mac*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwi_phy_config_agc (struct bwi_mac*) ; 
 int* bwi_phy_delay_11g_rev1 ; 
 int* bwi_phy_freq_11g_rev1 ; 
 int* bwi_phy_noise_11g ; 
 int* bwi_phy_noise_11g_rev1 ; 
 int* bwi_phy_noise_scale_11g ; 
 int* bwi_phy_noise_scale_11g_rev2 ; 
 int* bwi_phy_noise_scale_11g_rev7 ; 
 int* bwi_phy_rotor_11g_rev1 ; 
 int* bwi_phy_sigma_sq_11g_rev2 ; 
 int* bwi_phy_sigma_sq_11g_rev7 ; 
 int /*<<< orphan*/  bwi_tbl_write_2 (struct bwi_mac*,int,int const) ; 
 int /*<<< orphan*/  bwi_tbl_write_4 (struct bwi_mac*,scalar_t__,int) ; 
 int nitems (int*) ; 

__attribute__((used)) static void
bwi_phy_config_11g(struct bwi_mac *mac)
{
	struct bwi_softc *sc = mac->mac_sc;
	struct bwi_phy *phy = &mac->mac_phy;
	const uint16_t *tbl;
	uint16_t wrd_ofs1, wrd_ofs2;
	int i, n;

	if (phy->phy_rev == 1) {
		PHY_WRITE(mac, 0x406, 0x4f19);
		PHY_FILT_SETBITS(mac, 0x429, 0xfc3f, 0x340);
		PHY_WRITE(mac, 0x42c, 0x5a);
		PHY_WRITE(mac, 0x427, 0x1a);

		/* Fill frequency table */
		for (i = 0; i < nitems(bwi_phy_freq_11g_rev1); ++i) {
			bwi_tbl_write_2(mac, BWI_PHYTBL_FREQ + i,
					bwi_phy_freq_11g_rev1[i]);
		}

		/* Fill noise table */
		for (i = 0; i < nitems(bwi_phy_noise_11g_rev1); ++i) {
			bwi_tbl_write_2(mac, BWI_PHYTBL_NOISE + i,
					bwi_phy_noise_11g_rev1[i]);
		}

		/* Fill rotor table */
		for (i = 0; i < nitems(bwi_phy_rotor_11g_rev1); ++i) {
			/* NB: data length is 4 bytes */
			bwi_tbl_write_4(mac, BWI_PHYTBL_ROTOR + i,
					bwi_phy_rotor_11g_rev1[i]);
		}
	} else {
		bwi_nrssi_write(mac, 0xba98, (int16_t)0x7654); /* XXX */

		if (phy->phy_rev == 2) {
			PHY_WRITE(mac, 0x4c0, 0x1861);
			PHY_WRITE(mac, 0x4c1, 0x271);
		} else if (phy->phy_rev > 2) {
			PHY_WRITE(mac, 0x4c0, 0x98);
			PHY_WRITE(mac, 0x4c1, 0x70);
			PHY_WRITE(mac, 0x4c9, 0x80);
		}
		PHY_SETBITS(mac, 0x42b, 0x800);

		/* Fill RSSI table */
		for (i = 0; i < 64; ++i)
			bwi_tbl_write_2(mac, BWI_PHYTBL_RSSI + i, i);

		/* Fill noise table */
		for (i = 0; i < nitems(bwi_phy_noise_11g); ++i) {
			bwi_tbl_write_2(mac, BWI_PHYTBL_NOISE + i,
					bwi_phy_noise_11g[i]);
		}
	}

	/*
	 * Fill noise scale table
	 */
	if (phy->phy_rev <= 2) {
		tbl = bwi_phy_noise_scale_11g_rev2;
		n = nitems(bwi_phy_noise_scale_11g_rev2);
	} else if (phy->phy_rev >= 7 && (PHY_READ(mac, 0x449) & 0x200)) {
		tbl = bwi_phy_noise_scale_11g_rev7;
		n = nitems(bwi_phy_noise_scale_11g_rev7);
	} else {
		tbl = bwi_phy_noise_scale_11g;
		n = nitems(bwi_phy_noise_scale_11g);
	}
	for (i = 0; i < n; ++i)
		bwi_tbl_write_2(mac, BWI_PHYTBL_NOISE_SCALE + i, tbl[i]);

	/*
	 * Fill sigma square table
	 */
	if (phy->phy_rev == 2) {
		tbl = bwi_phy_sigma_sq_11g_rev2;
		n = nitems(bwi_phy_sigma_sq_11g_rev2);
	} else if (phy->phy_rev > 2 && phy->phy_rev <= 8) {
		tbl = bwi_phy_sigma_sq_11g_rev7;
		n = nitems(bwi_phy_sigma_sq_11g_rev7);
	} else {
		tbl = NULL;
		n = 0;
	}
	for (i = 0; i < n; ++i)
		bwi_tbl_write_2(mac, BWI_PHYTBL_SIGMA_SQ + i, tbl[i]);

	if (phy->phy_rev == 1) {
		/* Fill delay table */
		for (i = 0; i < nitems(bwi_phy_delay_11g_rev1); ++i) {
			bwi_tbl_write_4(mac, BWI_PHYTBL_DELAY + i,
					bwi_phy_delay_11g_rev1[i]);
		}

		/* Fill WRSSI (Wide-Band RSSI) table */
		for (i = 4; i < 20; ++i)
			bwi_tbl_write_2(mac, BWI_PHYTBL_WRSSI_REV1 + i, 0x20);

		bwi_phy_config_agc(mac);

		wrd_ofs1 = 0x5001;
		wrd_ofs2 = 0x5002;
	} else {
		/* Fill WRSSI (Wide-Band RSSI) table */
		for (i = 0; i < 0x20; ++i)
			bwi_tbl_write_2(mac, BWI_PHYTBL_WRSSI + i, 0x820);

		bwi_phy_config_agc(mac);

		PHY_READ(mac, 0x400);	/* Dummy read */
		PHY_WRITE(mac, 0x403, 0x1000);
		bwi_tbl_write_2(mac, 0x3c02, 0xf);
		bwi_tbl_write_2(mac, 0x3c03, 0x14);

		wrd_ofs1 = 0x401;
		wrd_ofs2 = 0x402;
	}

	if (!(BWI_IS_BRCM_BU4306(sc) && sc->sc_pci_revid == 0x17)) {
		bwi_tbl_write_2(mac, wrd_ofs1, 0x2);
		bwi_tbl_write_2(mac, wrd_ofs2, 0x1);
	}

	/* phy->phy_flags & BWI_PHY_F_LINKED ? */
	if (sc->sc_card_flags & BWI_CARD_F_PA_GPIO9)
		PHY_WRITE(mac, 0x46e, 0x3cf);
}