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
#define  BWN_B2062_N_COM4 176 
#define  BWN_B2062_N_LGENACTL3 175 
#define  BWN_B2062_N_LGENACTL7 174 
#define  BWN_B2062_N_LGENATUNE0 173 
#define  BWN_B2062_N_LGENATUNE2 172 
#define  BWN_B2062_N_LGENATUNE3 171 
#define  BWN_B2062_N_LGENC 170 
#define  BWN_B2062_N_PDNCTL1 169 
#define  BWN_B2062_N_PDNCTL3 168 
#define  BWN_B2062_N_PDNCTL4 167 
#define  BWN_B2062_N_RXA_CTL1 166 
#define  BWN_B2062_N_RXBB_CTL0 165 
#define  BWN_B2062_N_RXBB_GAIN1 164 
#define  BWN_B2062_N_RXBB_GAIN2 163 
#define  BWN_B2062_N_TXCTL4 162 
#define  BWN_B2062_N_TXCTL5 161 
#define  BWN_B2062_N_TX_TUNE 160 
#define  BWN_B2062_S_COM4 159 
#define  BWN_B2062_S_LGENG_CTL0 158 
#define  BWN_B2062_S_LGENG_CTL1 157 
#define  BWN_B2062_S_LGENG_CTL10 156 
#define  BWN_B2062_S_LGENG_CTL8 155 
#define  BWN_B2062_S_PDS_CTL0 154 
#define  BWN_B2062_S_RFPLLCTL0 153 
#define  BWN_B2062_S_RFPLLCTL1 152 
#define  BWN_B2062_S_RFPLLCTL10 151 
#define  BWN_B2062_S_RFPLLCTL11 150 
#define  BWN_B2062_S_RFPLLCTL12 149 
#define  BWN_B2062_S_RFPLLCTL13 148 
#define  BWN_B2062_S_RFPLLCTL14 147 
#define  BWN_B2062_S_RFPLLCTL18 146 
#define  BWN_B2062_S_RFPLLCTL19 145 
#define  BWN_B2062_S_RFPLLCTL21 144 
#define  BWN_B2062_S_RFPLLCTL22 143 
#define  BWN_B2062_S_RFPLLCTL23 142 
#define  BWN_B2062_S_RFPLLCTL24 141 
#define  BWN_B2062_S_RFPLLCTL25 140 
#define  BWN_B2062_S_RFPLLCTL30 139 
#define  BWN_B2062_S_RFPLLCTL31 138 
#define  BWN_B2062_S_RFPLLCTL33 137 
#define  BWN_B2062_S_RFPLLCTL34 136 
#define  BWN_B2062_S_RFPLLCTL5 135 
#define  BWN_B2062_S_RFPLLCTL6 134 
#define  BWN_B2062_S_RFPLLCTL7 133 
#define  BWN_B2062_S_RFPLLCTL8 132 
#define  BWN_B2062_S_RFPLLCTL9 131 
#define  BWN_B2062_S_RXG_CNT8 130 
 int /*<<< orphan*/  BWN_RF_WRITE (struct bwn_mac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  FLAG_A 129 
#define  FLAG_G 128 
 scalar_t__ IEEE80211_IS_CHAN_2GHZ (int /*<<< orphan*/ ) ; 
 unsigned int N (struct bwn_b206x_rfinit_entry const*) ; 

__attribute__((used)) static void
bwn_phy_lp_b2062_tblinit(struct bwn_mac *mac)
{
#define	FLAG_A	0x01
#define	FLAG_G	0x02
	struct bwn_softc *sc = mac->mac_sc;
	struct ieee80211com *ic = &sc->sc_ic;
	static const struct bwn_b206x_rfinit_entry bwn_b2062_init_tab[] = {
		{ BWN_B2062_N_COM4, 0x1, 0x0, FLAG_A | FLAG_G, },
		{ BWN_B2062_N_PDNCTL1, 0x0, 0xca, FLAG_G, },
		{ BWN_B2062_N_PDNCTL3, 0x0, 0x0, FLAG_A | FLAG_G, },
		{ BWN_B2062_N_PDNCTL4, 0x15, 0x2a, FLAG_A | FLAG_G, },
		{ BWN_B2062_N_LGENC, 0xDB, 0xff, FLAG_A, },
		{ BWN_B2062_N_LGENATUNE0, 0xdd, 0x0, FLAG_A | FLAG_G, },
		{ BWN_B2062_N_LGENATUNE2, 0xdd, 0x0, FLAG_A | FLAG_G, },
		{ BWN_B2062_N_LGENATUNE3, 0x77, 0xB5, FLAG_A | FLAG_G, },
		{ BWN_B2062_N_LGENACTL3, 0x0, 0xff, FLAG_A | FLAG_G, },
		{ BWN_B2062_N_LGENACTL7, 0x33, 0x33, FLAG_A | FLAG_G, },
		{ BWN_B2062_N_RXA_CTL1, 0x0, 0x0, FLAG_G, },
		{ BWN_B2062_N_RXBB_CTL0, 0x82, 0x80, FLAG_A | FLAG_G, },
		{ BWN_B2062_N_RXBB_GAIN1, 0x4, 0x4, FLAG_A | FLAG_G, },
		{ BWN_B2062_N_RXBB_GAIN2, 0x0, 0x0, FLAG_A | FLAG_G, },
		{ BWN_B2062_N_TXCTL4, 0x3, 0x3, FLAG_A | FLAG_G, },
		{ BWN_B2062_N_TXCTL5, 0x2, 0x2, FLAG_A | FLAG_G, },
		{ BWN_B2062_N_TX_TUNE, 0x88, 0x1b, FLAG_A | FLAG_G, },
		{ BWN_B2062_S_COM4, 0x1, 0x0, FLAG_A | FLAG_G, },
		{ BWN_B2062_S_PDS_CTL0, 0xff, 0xff, FLAG_A | FLAG_G, },
		{ BWN_B2062_S_LGENG_CTL0, 0xf8, 0xd8, FLAG_A | FLAG_G, },
		{ BWN_B2062_S_LGENG_CTL1, 0x3c, 0x24, FLAG_A | FLAG_G, },
		{ BWN_B2062_S_LGENG_CTL8, 0x88, 0x80, FLAG_A | FLAG_G, },
		{ BWN_B2062_S_LGENG_CTL10, 0x88, 0x80, FLAG_A | FLAG_G, },
		{ BWN_B2062_S_RFPLLCTL0, 0x98, 0x98, FLAG_A | FLAG_G, },
		{ BWN_B2062_S_RFPLLCTL1, 0x10, 0x10, FLAG_A | FLAG_G, },
		{ BWN_B2062_S_RFPLLCTL5, 0x43, 0x43, FLAG_A | FLAG_G, },
		{ BWN_B2062_S_RFPLLCTL6, 0x47, 0x47, FLAG_A | FLAG_G, },
		{ BWN_B2062_S_RFPLLCTL7, 0xc, 0xc, FLAG_A | FLAG_G, },
		{ BWN_B2062_S_RFPLLCTL8, 0x11, 0x11, FLAG_A | FLAG_G, },
		{ BWN_B2062_S_RFPLLCTL9, 0x11, 0x11, FLAG_A | FLAG_G, },
		{ BWN_B2062_S_RFPLLCTL10, 0xe, 0xe, FLAG_A | FLAG_G, },
		{ BWN_B2062_S_RFPLLCTL11, 0x8, 0x8, FLAG_A | FLAG_G, },
		{ BWN_B2062_S_RFPLLCTL12, 0x33, 0x33, FLAG_A | FLAG_G, },
		{ BWN_B2062_S_RFPLLCTL13, 0xa, 0xa, FLAG_A | FLAG_G, },
		{ BWN_B2062_S_RFPLLCTL14, 0x6, 0x6, FLAG_A | FLAG_G, },
		{ BWN_B2062_S_RFPLLCTL18, 0x3e, 0x3e, FLAG_A | FLAG_G, },
		{ BWN_B2062_S_RFPLLCTL19, 0x13, 0x13, FLAG_A | FLAG_G, },
		{ BWN_B2062_S_RFPLLCTL21, 0x62, 0x62, FLAG_A | FLAG_G, },
		{ BWN_B2062_S_RFPLLCTL22, 0x7, 0x7, FLAG_A | FLAG_G, },
		{ BWN_B2062_S_RFPLLCTL23, 0x16, 0x16, FLAG_A | FLAG_G, },
		{ BWN_B2062_S_RFPLLCTL24, 0x5c, 0x5c, FLAG_A | FLAG_G, },
		{ BWN_B2062_S_RFPLLCTL25, 0x95, 0x95, FLAG_A | FLAG_G, },
		{ BWN_B2062_S_RFPLLCTL30, 0xa0, 0xa0, FLAG_A | FLAG_G, },
		{ BWN_B2062_S_RFPLLCTL31, 0x4, 0x4, FLAG_A | FLAG_G, },
		{ BWN_B2062_S_RFPLLCTL33, 0xcc, 0xcc, FLAG_A | FLAG_G, },
		{ BWN_B2062_S_RFPLLCTL34, 0x7, 0x7, FLAG_A | FLAG_G, },
		{ BWN_B2062_S_RXG_CNT8, 0xf, 0xf, FLAG_A, },
	};
	const struct bwn_b206x_rfinit_entry *br;
	unsigned int i;

	for (i = 0; i < N(bwn_b2062_init_tab); i++) {
		br = &bwn_b2062_init_tab[i];
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