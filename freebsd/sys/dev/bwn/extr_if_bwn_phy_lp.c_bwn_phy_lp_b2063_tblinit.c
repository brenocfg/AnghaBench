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
struct ieee80211com {int /*<<< orphan*/  ic_curchan; } ;
struct bwn_softc {struct ieee80211com sc_ic; } ;
struct bwn_mac {struct bwn_softc* mac_sc; } ;
struct bwn_b206x_rfinit_entry {int member_1; int member_2; int member_3; int const br_flags; int /*<<< orphan*/  br_valuea; int /*<<< orphan*/  br_offset; int /*<<< orphan*/  br_valueg; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
#define  BWN_B2063_A_RX_1ST2 171 
#define  BWN_B2063_A_RX_MIX4 170 
#define  BWN_B2063_A_RX_MIX5 169 
#define  BWN_B2063_A_RX_MIX6 168 
#define  BWN_B2063_A_RX_PS6 167 
#define  BWN_B2063_A_RX_SP1 166 
#define  BWN_B2063_A_RX_SP2 165 
#define  BWN_B2063_A_RX_SP7 164 
#define  BWN_B2063_BANDGAP_CTL1 163 
#define  BWN_B2063_COM1 162 
#define  BWN_B2063_COM10 161 
#define  BWN_B2063_COM16 160 
#define  BWN_B2063_COM17 159 
#define  BWN_B2063_COM18 158 
#define  BWN_B2063_COM19 157 
#define  BWN_B2063_COM20 156 
#define  BWN_B2063_COM21 155 
#define  BWN_B2063_COM22 154 
#define  BWN_B2063_COM23 153 
#define  BWN_B2063_COM24 152 
#define  BWN_B2063_G_RX_MIX3 151 
#define  BWN_B2063_G_RX_MIX4 150 
#define  BWN_B2063_G_RX_SP1 149 
#define  BWN_B2063_G_RX_SP10 148 
#define  BWN_B2063_G_RX_SP2 147 
#define  BWN_B2063_G_RX_SP3 146 
#define  BWN_B2063_G_RX_SP7 145 
#define  BWN_B2063_JTAG_VCO2 144 
#define  BWN_B2063_LOGEN_SP1 143 
#define  BWN_B2063_LOGEN_SP2 142 
#define  BWN_B2063_LOGEN_SP4 141 
#define  BWN_B2063_PA_CTL1 140 
#define  BWN_B2063_PA_SP1 139 
#define  BWN_B2063_RX_BB_CTL2 138 
#define  BWN_B2063_RX_BB_SP4 137 
#define  BWN_B2063_RX_BB_SP8 136 
#define  BWN_B2063_RX_TIA_CTL1 135 
#define  BWN_B2063_RX_TIA_CTL3 134 
#define  BWN_B2063_TX_BB_SP1 133 
#define  BWN_B2063_TX_RF_SP3 132 
#define  BWN_B2063_TX_RF_SP4 131 
#define  BWN_B2063_VREG_CTL1 130 
 int /*<<< orphan*/  BWN_RF_WRITE (struct bwn_mac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  FLAG_A 129 
#define  FLAG_G 128 
 scalar_t__ IEEE80211_IS_CHAN_2GHZ (int /*<<< orphan*/ ) ; 
 unsigned int N (struct bwn_b206x_rfinit_entry const*) ; 

__attribute__((used)) static void
bwn_phy_lp_b2063_tblinit(struct bwn_mac *mac)
{
#define	FLAG_A	0x01
#define	FLAG_G	0x02
	struct bwn_softc *sc = mac->mac_sc;
	struct ieee80211com *ic = &sc->sc_ic;
	static const struct bwn_b206x_rfinit_entry bwn_b2063_init_tab[] = {
		{ BWN_B2063_COM1, 0x0, 0x0, FLAG_G, },
		{ BWN_B2063_COM10, 0x1, 0x0, FLAG_A, },
		{ BWN_B2063_COM16, 0x0, 0x0, FLAG_G, },
		{ BWN_B2063_COM17, 0x0, 0x0, FLAG_G, },
		{ BWN_B2063_COM18, 0x0, 0x0, FLAG_G, },
		{ BWN_B2063_COM19, 0x0, 0x0, FLAG_G, },
		{ BWN_B2063_COM20, 0x0, 0x0, FLAG_G, },
		{ BWN_B2063_COM21, 0x0, 0x0, FLAG_G, },
		{ BWN_B2063_COM22, 0x0, 0x0, FLAG_G, },
		{ BWN_B2063_COM23, 0x0, 0x0, FLAG_G, },
		{ BWN_B2063_COM24, 0x0, 0x0, FLAG_G, },
		{ BWN_B2063_LOGEN_SP1, 0xe8, 0xd4, FLAG_A | FLAG_G, },
		{ BWN_B2063_LOGEN_SP2, 0xa7, 0x53, FLAG_A | FLAG_G, },
		{ BWN_B2063_LOGEN_SP4, 0xf0, 0xf, FLAG_A | FLAG_G, },
		{ BWN_B2063_G_RX_SP1, 0x1f, 0x5e, FLAG_G, },
		{ BWN_B2063_G_RX_SP2, 0x7f, 0x7e, FLAG_G, },
		{ BWN_B2063_G_RX_SP3, 0x30, 0xf0, FLAG_G, },
		{ BWN_B2063_G_RX_SP7, 0x7f, 0x7f, FLAG_A | FLAG_G, },
		{ BWN_B2063_G_RX_SP10, 0xc, 0xc, FLAG_A | FLAG_G, },
		{ BWN_B2063_A_RX_SP1, 0x3c, 0x3f, FLAG_A, },
		{ BWN_B2063_A_RX_SP2, 0xfc, 0xfe, FLAG_A, },
		{ BWN_B2063_A_RX_SP7, 0x8, 0x8, FLAG_A | FLAG_G, },
		{ BWN_B2063_RX_BB_SP4, 0x60, 0x60, FLAG_A | FLAG_G, },
		{ BWN_B2063_RX_BB_SP8, 0x30, 0x30, FLAG_A | FLAG_G, },
		{ BWN_B2063_TX_RF_SP3, 0xc, 0xb, FLAG_A | FLAG_G, },
		{ BWN_B2063_TX_RF_SP4, 0x10, 0xf, FLAG_A | FLAG_G, },
		{ BWN_B2063_PA_SP1, 0x3d, 0xfd, FLAG_A | FLAG_G, },
		{ BWN_B2063_TX_BB_SP1, 0x2, 0x2, FLAG_A | FLAG_G, },
		{ BWN_B2063_BANDGAP_CTL1, 0x56, 0x56, FLAG_A | FLAG_G, },
		{ BWN_B2063_JTAG_VCO2, 0xF7, 0xF7, FLAG_A | FLAG_G, },
		{ BWN_B2063_G_RX_MIX3, 0x71, 0x71, FLAG_A | FLAG_G, },
		{ BWN_B2063_G_RX_MIX4, 0x71, 0x71, FLAG_A | FLAG_G, },
		{ BWN_B2063_A_RX_1ST2, 0xf0, 0x30, FLAG_A, },
		{ BWN_B2063_A_RX_PS6, 0x77, 0x77, FLAG_A | FLAG_G, },
		{ BWN_B2063_A_RX_MIX4, 0x3, 0x3, FLAG_A | FLAG_G, },
		{ BWN_B2063_A_RX_MIX5, 0xf, 0xf, FLAG_A | FLAG_G, },
		{ BWN_B2063_A_RX_MIX6, 0xf, 0xf, FLAG_A | FLAG_G, },
		{ BWN_B2063_RX_TIA_CTL1, 0x77, 0x77, FLAG_A | FLAG_G, },
		{ BWN_B2063_RX_TIA_CTL3, 0x77, 0x77, FLAG_A | FLAG_G, },
		{ BWN_B2063_RX_BB_CTL2, 0x4, 0x4, FLAG_A | FLAG_G, },
		{ BWN_B2063_PA_CTL1, 0x0, 0x4, FLAG_A, },
		{ BWN_B2063_VREG_CTL1, 0x3, 0x3, FLAG_A | FLAG_G, },
	};
	const struct bwn_b206x_rfinit_entry *br;
	unsigned int i;

	for (i = 0; i < N(bwn_b2063_init_tab); i++) {
		br = &bwn_b2063_init_tab[i];
		if (IEEE80211_IS_CHAN_2GHZ(ic->ic_curchan)) {
			if (br->br_flags & FLAG_G)
				BWN_RF_WRITE(mac, br->br_offset, br->br_valueg);
		} else {
			if (br->br_flags & FLAG_A)
				BWN_RF_WRITE(mac, br->br_offset, br->br_valuea);
		}
	}
#undef FLAG_A
#undef FLAG_B
}