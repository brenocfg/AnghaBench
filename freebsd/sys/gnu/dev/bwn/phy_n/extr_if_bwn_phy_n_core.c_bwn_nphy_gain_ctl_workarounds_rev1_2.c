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
typedef  int uint8_t ;
typedef  int uint16_t ;
struct bwn_phy_n {scalar_t__ elna_gain_config; scalar_t__ gain_boost; } ;
struct TYPE_2__ {int rev; struct bwn_phy_n* phy_n; } ;
struct bwn_mac {TYPE_1__ mac_phy; } ;

/* Variables and functions */
 scalar_t__ BWN_BAND_2G ; 
 int /*<<< orphan*/  BWN_NPHY_C1_CCK_CGAINI ; 
 int BWN_NPHY_C1_CCK_CGAINI_GAINBKOFF ; 
 int /*<<< orphan*/  BWN_NPHY_C1_CGAINI ; 
 int /*<<< orphan*/  BWN_NPHY_C1_CGAINI_CL2DETECT ; 
 int BWN_NPHY_C1_CGAINI_GAINBKOFF ; 
 int /*<<< orphan*/  BWN_NPHY_C1_CLIPWBTHRES ; 
 int BWN_NPHY_C1_CLIPWBTHRES_CLIP2 ; 
 int /*<<< orphan*/  BWN_NPHY_C1_INITGAIN ; 
 int BWN_NPHY_C1_INITGAIN_HPVGA2 ; 
 int BWN_NPHY_C1_INITGAIN_HPVGA2_SHIFT ; 
 int /*<<< orphan*/  BWN_NPHY_C1_NBCLIPTHRES ; 
 int /*<<< orphan*/  BWN_NPHY_C2_CCK_CGAINI ; 
 int BWN_NPHY_C2_CCK_CGAINI_GAINBKOFF ; 
 int /*<<< orphan*/  BWN_NPHY_C2_CGAINI ; 
 int /*<<< orphan*/  BWN_NPHY_C2_CGAINI_CL2DETECT ; 
 int BWN_NPHY_C2_CGAINI_GAINBKOFF ; 
 int /*<<< orphan*/  BWN_NPHY_C2_CLIPWBTHRES ; 
 int BWN_NPHY_C2_CLIPWBTHRES_CLIP2 ; 
 int /*<<< orphan*/  BWN_NPHY_C2_INITGAIN ; 
 int BWN_NPHY_C2_INITGAIN_HPVGA2 ; 
 int BWN_NPHY_C2_INITGAIN_HPVGA2_SHIFT ; 
 int /*<<< orphan*/  BWN_NPHY_C2_NBCLIPTHRES ; 
 int /*<<< orphan*/  BWN_NPHY_CCK_SHIFTB_REF ; 
 int /*<<< orphan*/  BWN_NPHY_CLIP1_NBDWELL_LEN ; 
 int /*<<< orphan*/  BWN_NPHY_CLIP2_NBDWELL_LEN ; 
 int /*<<< orphan*/  BWN_NPHY_OVER_DGAIN1 ; 
 int BWN_NPHY_OVER_DGAIN_CCKDGECV ; 
 int BWN_NPHY_OVER_DGAIN_CCKDGECV_SHIFT ; 
 int /*<<< orphan*/  BWN_NPHY_TABLE_ADDR ; 
 int /*<<< orphan*/  BWN_NPHY_TABLE_DATALO ; 
 int /*<<< orphan*/  BWN_NPHY_W1CLIP1_DWELL_LEN ; 
 int /*<<< orphan*/  BWN_NPHY_W1CLIP2_DWELL_LEN ; 
 int /*<<< orphan*/  BWN_PHY_N (int) ; 
 int /*<<< orphan*/  BWN_PHY_SET (struct bwn_mac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BWN_PHY_SETMASK (struct bwn_mac*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  BWN_PHY_WRITE (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ bwn_current_band (struct bwn_mac*) ; 
 scalar_t__ bwn_is_40mhz (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_nphy_adjust_lna_gain_table (struct bwn_mac*) ; 
 int /*<<< orphan*/  bwn_nphy_set_rf_sequence (struct bwn_mac*,int,int*,int*,int) ; 

__attribute__((used)) static void bwn_nphy_gain_ctl_workarounds_rev1_2(struct bwn_mac *mac)
{
	struct bwn_phy_n *nphy = mac->mac_phy.phy_n;

	uint8_t i, j;
	uint8_t code;
	uint16_t tmp;
	uint8_t rfseq_events[3] = { 6, 8, 7 };
	uint8_t rfseq_delays[3] = { 10, 30, 1 };

	/* Set Clip 2 detect */
	BWN_PHY_SET(mac, BWN_NPHY_C1_CGAINI, BWN_NPHY_C1_CGAINI_CL2DETECT);
	BWN_PHY_SET(mac, BWN_NPHY_C2_CGAINI, BWN_NPHY_C2_CGAINI_CL2DETECT);

	/* Set narrowband clip threshold */
	BWN_PHY_WRITE(mac, BWN_NPHY_C1_NBCLIPTHRES, 0x84);
	BWN_PHY_WRITE(mac, BWN_NPHY_C2_NBCLIPTHRES, 0x84);

	if (!bwn_is_40mhz(mac)) {
		/* Set dwell lengths */
		BWN_PHY_WRITE(mac, BWN_NPHY_CLIP1_NBDWELL_LEN, 0x002B);
		BWN_PHY_WRITE(mac, BWN_NPHY_CLIP2_NBDWELL_LEN, 0x002B);
		BWN_PHY_WRITE(mac, BWN_NPHY_W1CLIP1_DWELL_LEN, 0x0009);
		BWN_PHY_WRITE(mac, BWN_NPHY_W1CLIP2_DWELL_LEN, 0x0009);
	}

	/* Set wideband clip 2 threshold */
	BWN_PHY_SETMASK(mac, BWN_NPHY_C1_CLIPWBTHRES,
			~BWN_NPHY_C1_CLIPWBTHRES_CLIP2, 21);
	BWN_PHY_SETMASK(mac, BWN_NPHY_C2_CLIPWBTHRES,
			~BWN_NPHY_C2_CLIPWBTHRES_CLIP2, 21);

	if (!bwn_is_40mhz(mac)) {
		BWN_PHY_SETMASK(mac, BWN_NPHY_C1_CGAINI,
			~BWN_NPHY_C1_CGAINI_GAINBKOFF, 0x1);
		BWN_PHY_SETMASK(mac, BWN_NPHY_C2_CGAINI,
			~BWN_NPHY_C2_CGAINI_GAINBKOFF, 0x1);
		BWN_PHY_SETMASK(mac, BWN_NPHY_C1_CCK_CGAINI,
			~BWN_NPHY_C1_CCK_CGAINI_GAINBKOFF, 0x1);
		BWN_PHY_SETMASK(mac, BWN_NPHY_C2_CCK_CGAINI,
			~BWN_NPHY_C2_CCK_CGAINI_GAINBKOFF, 0x1);
	}

	BWN_PHY_WRITE(mac, BWN_NPHY_CCK_SHIFTB_REF, 0x809C);

	if (nphy->gain_boost) {
		if (bwn_current_band(mac) == BWN_BAND_2G &&
		    bwn_is_40mhz(mac))
			code = 4;
		else
			code = 5;
	} else {
		code = bwn_is_40mhz(mac) ? 6 : 7;
	}

	/* Set HPVGA2 index */
	BWN_PHY_SETMASK(mac, BWN_NPHY_C1_INITGAIN, ~BWN_NPHY_C1_INITGAIN_HPVGA2,
			code << BWN_NPHY_C1_INITGAIN_HPVGA2_SHIFT);
	BWN_PHY_SETMASK(mac, BWN_NPHY_C2_INITGAIN, ~BWN_NPHY_C2_INITGAIN_HPVGA2,
			code << BWN_NPHY_C2_INITGAIN_HPVGA2_SHIFT);

	BWN_PHY_WRITE(mac, BWN_NPHY_TABLE_ADDR, 0x1D06);
	/* specs say about 2 loops, but wl does 4 */
	for (i = 0; i < 4; i++)
		BWN_PHY_WRITE(mac, BWN_NPHY_TABLE_DATALO, (code << 8 | 0x7C));

	bwn_nphy_adjust_lna_gain_table(mac);

	if (nphy->elna_gain_config) {
		BWN_PHY_WRITE(mac, BWN_NPHY_TABLE_ADDR, 0x0808);
		BWN_PHY_WRITE(mac, BWN_NPHY_TABLE_DATALO, 0x0);
		BWN_PHY_WRITE(mac, BWN_NPHY_TABLE_DATALO, 0x1);
		BWN_PHY_WRITE(mac, BWN_NPHY_TABLE_DATALO, 0x1);
		BWN_PHY_WRITE(mac, BWN_NPHY_TABLE_DATALO, 0x1);

		BWN_PHY_WRITE(mac, BWN_NPHY_TABLE_ADDR, 0x0C08);
		BWN_PHY_WRITE(mac, BWN_NPHY_TABLE_DATALO, 0x0);
		BWN_PHY_WRITE(mac, BWN_NPHY_TABLE_DATALO, 0x1);
		BWN_PHY_WRITE(mac, BWN_NPHY_TABLE_DATALO, 0x1);
		BWN_PHY_WRITE(mac, BWN_NPHY_TABLE_DATALO, 0x1);

		BWN_PHY_WRITE(mac, BWN_NPHY_TABLE_ADDR, 0x1D06);
		/* specs say about 2 loops, but wl does 4 */
		for (i = 0; i < 4; i++)
			BWN_PHY_WRITE(mac, BWN_NPHY_TABLE_DATALO,
						(code << 8 | 0x74));
	}

	if (mac->mac_phy.rev == 2) {
		for (i = 0; i < 4; i++) {
			BWN_PHY_WRITE(mac, BWN_NPHY_TABLE_ADDR,
					(0x0400 * i) + 0x0020);
			for (j = 0; j < 21; j++) {
				tmp = j * (i < 2 ? 3 : 1);
				BWN_PHY_WRITE(mac,
					BWN_NPHY_TABLE_DATALO, tmp);
			}
		}
	}

	bwn_nphy_set_rf_sequence(mac, 5, rfseq_events, rfseq_delays, 3);
	BWN_PHY_SETMASK(mac, BWN_NPHY_OVER_DGAIN1,
		~BWN_NPHY_OVER_DGAIN_CCKDGECV & 0xFFFF,
		0x5A << BWN_NPHY_OVER_DGAIN_CCKDGECV_SHIFT);

	if (bwn_current_band(mac) == BWN_BAND_2G)
		BWN_PHY_SETMASK(mac, BWN_PHY_N(0xC5D), 0xFF80, 4);
}