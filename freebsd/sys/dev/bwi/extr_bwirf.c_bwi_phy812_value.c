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
struct bwi_softc {int sc_card_flags; } ;
struct bwi_rf {int rf_lo_gain; int rf_rev; } ;
struct bwi_phy {int phy_flags; int phy_rev; } ;
struct bwi_mac {struct bwi_rf mac_rf; struct bwi_phy mac_phy; struct bwi_softc* mac_sc; } ;

/* Variables and functions */
 int BWI_CARD_F_EXT_LNA ; 
 int BWI_PHY_F_LINKED ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static __inline uint16_t
bwi_phy812_value(struct bwi_mac *mac, uint16_t lpd)
{
	struct bwi_softc *sc = mac->mac_sc;
	struct bwi_phy *phy = &mac->mac_phy;
	struct bwi_rf *rf = &mac->mac_rf;
	uint16_t lo_gain, ext_lna, loop;

	if ((phy->phy_flags & BWI_PHY_F_LINKED) == 0)
		return 0;

	lo_gain = rf->rf_lo_gain;
	if (rf->rf_rev == 8)
		lo_gain += 0x3e;
	else
		lo_gain += 0x26;

	if (lo_gain >= 0x46) {
		lo_gain -= 0x46;
		ext_lna = 0x3000;
	} else if (lo_gain >= 0x3a) {
		lo_gain -= 0x3a;
		ext_lna = 0x1000;
	} else if (lo_gain >= 0x2e) {
		lo_gain -= 0x2e;
		ext_lna = 0x2000;
	} else {
		lo_gain -= 0x10;
		ext_lna = 0;
	}

	for (loop = 0; loop < 16; ++loop) {
		lo_gain -= (6 * loop);
		if (lo_gain < 6)
			break;
	}

	if (phy->phy_rev >= 7 && (sc->sc_card_flags & BWI_CARD_F_EXT_LNA)) {
		if (ext_lna)
			ext_lna |= 0x8000;
		ext_lna |= (loop << 8);
		switch (lpd) {
		case 0x011:
			return 0x8f92;
		case 0x001:
			return (0x8092 | ext_lna);
		case 0x101:
			return (0x2092 | ext_lna);
		case 0x100:
			return (0x2093 | ext_lna);
		default:
			panic("unsupported lpd\n");
		}
	} else {
		ext_lna |= (loop << 8);
		switch (lpd) {
		case 0x011:
			return 0xf92;
		case 0x001:
		case 0x101:
			return (0x92 | ext_lna);
		case 0x100:
			return (0x93 | ext_lna);
		default:
			panic("unsupported lpd\n");
		}
	}

	panic("never reached\n");
	return 0;
}