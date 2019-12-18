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
struct bwn_phy {int rev; } ;
struct bwn_mac {struct bwn_phy mac_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_OFDMTAB_AGC1 ; 
 int /*<<< orphan*/  BWN_OFDMTAB_AGC1_R1 ; 
 int /*<<< orphan*/  BWN_OFDMTAB_AGC2 ; 
 int /*<<< orphan*/  BWN_OFDMTAB_AGC3 ; 
 int /*<<< orphan*/  BWN_OFDMTAB_AGC3_R1 ; 
 int /*<<< orphan*/  BWN_PHY_ANTWRSETT ; 
 int /*<<< orphan*/  BWN_PHY_CCKSHIFTBITS_WA ; 
 int /*<<< orphan*/  BWN_PHY_DIVP1P2GAIN ; 
 int /*<<< orphan*/  BWN_PHY_DIVSRCHIDX ; 
 int /*<<< orphan*/  BWN_PHY_LMS ; 
 int /*<<< orphan*/  BWN_PHY_LPFGAINCTL ; 
 int /*<<< orphan*/  BWN_PHY_MASK (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BWN_PHY_N1N2GAIN ; 
 int /*<<< orphan*/  BWN_PHY_N1P1GAIN ; 
 int /*<<< orphan*/  BWN_PHY_OFDM (int) ; 
 int /*<<< orphan*/  BWN_PHY_P1P2GAIN ; 
 int /*<<< orphan*/  BWN_PHY_PEAK_COUNT ; 
 int /*<<< orphan*/  BWN_PHY_READ (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BWN_PHY_SETMASK (struct bwn_mac*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  BWN_PHY_VERSION_OFDM ; 
 int /*<<< orphan*/  BWN_PHY_WRITE (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BWN_RF_SET (struct bwn_mac*,int,int) ; 
 int /*<<< orphan*/  bwn_ofdmtab_write_2 (struct bwn_mac*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
bwn_wa_agc(struct bwn_mac *mac)
{
	struct bwn_phy *phy = &mac->mac_phy;

	if (phy->rev == 1) {
		bwn_ofdmtab_write_2(mac, BWN_OFDMTAB_AGC1_R1, 0, 254);
		bwn_ofdmtab_write_2(mac, BWN_OFDMTAB_AGC1_R1, 1, 13);
		bwn_ofdmtab_write_2(mac, BWN_OFDMTAB_AGC1_R1, 2, 19);
		bwn_ofdmtab_write_2(mac, BWN_OFDMTAB_AGC1_R1, 3, 25);
		bwn_ofdmtab_write_2(mac, BWN_OFDMTAB_AGC2, 0, 0x2710);
		bwn_ofdmtab_write_2(mac, BWN_OFDMTAB_AGC2, 1, 0x9b83);
		bwn_ofdmtab_write_2(mac, BWN_OFDMTAB_AGC2, 2, 0x9b83);
		bwn_ofdmtab_write_2(mac, BWN_OFDMTAB_AGC2, 3, 0x0f8d);
		BWN_PHY_WRITE(mac, BWN_PHY_LMS, 4);
	} else {
		bwn_ofdmtab_write_2(mac, BWN_OFDMTAB_AGC1, 0, 254);
		bwn_ofdmtab_write_2(mac, BWN_OFDMTAB_AGC1, 1, 13);
		bwn_ofdmtab_write_2(mac, BWN_OFDMTAB_AGC1, 2, 19);
		bwn_ofdmtab_write_2(mac, BWN_OFDMTAB_AGC1, 3, 25);
	}

	BWN_PHY_SETMASK(mac, BWN_PHY_CCKSHIFTBITS_WA, (uint16_t)~0xff00,
	    0x5700);
	BWN_PHY_SETMASK(mac, BWN_PHY_OFDM(0x1a), ~0x007f, 0x000f);
	BWN_PHY_SETMASK(mac, BWN_PHY_OFDM(0x1a), ~0x3f80, 0x2b80);
	BWN_PHY_SETMASK(mac, BWN_PHY_ANTWRSETT, 0xf0ff, 0x0300);
	BWN_RF_SET(mac, 0x7a, 0x0008);
	BWN_PHY_SETMASK(mac, BWN_PHY_N1P1GAIN, ~0x000f, 0x0008);
	BWN_PHY_SETMASK(mac, BWN_PHY_P1P2GAIN, ~0x0f00, 0x0600);
	BWN_PHY_SETMASK(mac, BWN_PHY_N1N2GAIN, ~0x0f00, 0x0700);
	BWN_PHY_SETMASK(mac, BWN_PHY_N1P1GAIN, ~0x0f00, 0x0100);
	if (phy->rev == 1)
		BWN_PHY_SETMASK(mac, BWN_PHY_N1N2GAIN, ~0x000f, 0x0007);
	BWN_PHY_SETMASK(mac, BWN_PHY_OFDM(0x88), ~0x00ff, 0x001c);
	BWN_PHY_SETMASK(mac, BWN_PHY_OFDM(0x88), ~0x3f00, 0x0200);
	BWN_PHY_SETMASK(mac, BWN_PHY_OFDM(0x96), ~0x00ff, 0x001c);
	BWN_PHY_SETMASK(mac, BWN_PHY_OFDM(0x89), ~0x00ff, 0x0020);
	BWN_PHY_SETMASK(mac, BWN_PHY_OFDM(0x89), ~0x3f00, 0x0200);
	BWN_PHY_SETMASK(mac, BWN_PHY_OFDM(0x82), ~0x00ff, 0x002e);
	BWN_PHY_SETMASK(mac, BWN_PHY_OFDM(0x96), (uint16_t)~0xff00, 0x1a00);
	BWN_PHY_SETMASK(mac, BWN_PHY_OFDM(0x81), ~0x00ff, 0x0028);
	BWN_PHY_SETMASK(mac, BWN_PHY_OFDM(0x81), (uint16_t)~0xff00, 0x2c00);
	if (phy->rev == 1) {
		BWN_PHY_WRITE(mac, BWN_PHY_PEAK_COUNT, 0x092b);
		BWN_PHY_SETMASK(mac, BWN_PHY_OFDM(0x1b), ~0x001e, 0x0002);
	} else {
		BWN_PHY_MASK(mac, BWN_PHY_OFDM(0x1b), ~0x001e);
		BWN_PHY_WRITE(mac, BWN_PHY_OFDM(0x1f), 0x287a);
		BWN_PHY_SETMASK(mac, BWN_PHY_LPFGAINCTL, ~0x000f, 0x0004);
		if (phy->rev >= 6) {
			BWN_PHY_WRITE(mac, BWN_PHY_OFDM(0x22), 0x287a);
			BWN_PHY_SETMASK(mac, BWN_PHY_LPFGAINCTL,
			    (uint16_t)~0xf000, 0x3000);
		}
	}
	BWN_PHY_SETMASK(mac, BWN_PHY_DIVSRCHIDX, 0x8080, 0x7874);
	BWN_PHY_WRITE(mac, BWN_PHY_OFDM(0x8e), 0x1c00);
	if (phy->rev == 1) {
		BWN_PHY_SETMASK(mac, BWN_PHY_DIVP1P2GAIN, ~0x0f00, 0x0600);
		BWN_PHY_WRITE(mac, BWN_PHY_OFDM(0x8b), 0x005e);
		BWN_PHY_SETMASK(mac, BWN_PHY_ANTWRSETT, ~0x00ff, 0x001e);
		BWN_PHY_WRITE(mac, BWN_PHY_OFDM(0x8d), 0x0002);
		bwn_ofdmtab_write_2(mac, BWN_OFDMTAB_AGC3_R1, 0, 0);
		bwn_ofdmtab_write_2(mac, BWN_OFDMTAB_AGC3_R1, 1, 7);
		bwn_ofdmtab_write_2(mac, BWN_OFDMTAB_AGC3_R1, 2, 16);
		bwn_ofdmtab_write_2(mac, BWN_OFDMTAB_AGC3_R1, 3, 28);
	} else {
		bwn_ofdmtab_write_2(mac, BWN_OFDMTAB_AGC3, 0, 0);
		bwn_ofdmtab_write_2(mac, BWN_OFDMTAB_AGC3, 1, 7);
		bwn_ofdmtab_write_2(mac, BWN_OFDMTAB_AGC3, 2, 16);
		bwn_ofdmtab_write_2(mac, BWN_OFDMTAB_AGC3, 3, 28);
	}
	if (phy->rev >= 6) {
		BWN_PHY_MASK(mac, BWN_PHY_OFDM(0x26), ~0x0003);
		BWN_PHY_MASK(mac, BWN_PHY_OFDM(0x26), ~0x1000);
	}
	BWN_PHY_READ(mac, BWN_PHY_VERSION_OFDM);
}