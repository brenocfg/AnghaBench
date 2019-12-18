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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct bwn_phy {scalar_t__ type; int rev; int analog; int rf_rev; scalar_t__ gmode; int /*<<< orphan*/  chan; } ;
struct bwn_mac {struct bwn_phy mac_phy; } ;

/* Variables and functions */
 int BWN_BITREV4 (int) ; 
 int BWN_CHANNEL_EXT ; 
 scalar_t__ BWN_HAS_LOOPBACK (struct bwn_phy*) ; 
 int /*<<< orphan*/  BWN_LPD (int,int,int) ; 
 scalar_t__ BWN_PHYTYPE_B ; 
 int /*<<< orphan*/  BWN_PHY_ANALOGOVER ; 
 int /*<<< orphan*/  BWN_PHY_ANALOGOVERVAL ; 
 int /*<<< orphan*/  BWN_PHY_CCK (int) ; 
 int /*<<< orphan*/  BWN_PHY_CLASSCTL ; 
 int /*<<< orphan*/  BWN_PHY_CRS0 ; 
 int /*<<< orphan*/  BWN_PHY_LO_CTL ; 
 int /*<<< orphan*/  BWN_PHY_LO_LEAKAGE ; 
 int /*<<< orphan*/  BWN_PHY_LO_MASK ; 
 int /*<<< orphan*/  BWN_PHY_MASK (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BWN_PHY_PGACTL ; 
 int BWN_PHY_RADIO ; 
 int BWN_PHY_READ (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BWN_PHY_RFOVER ; 
 int /*<<< orphan*/  BWN_PHY_RFOVERVAL ; 
 int /*<<< orphan*/  BWN_PHY_SET (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BWN_PHY_SETMASK (struct bwn_mac*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  BWN_PHY_SYNCCTL ; 
 int /*<<< orphan*/  BWN_PHY_WRITE (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int BWN_READ_2 (struct bwn_mac*,int) ; 
 int BWN_RF_READ (struct bwn_mac*,int) ; 
 int /*<<< orphan*/  BWN_RF_SET (struct bwn_mac*,int,int) ; 
 int /*<<< orphan*/  BWN_RF_SETMASK (struct bwn_mac*,int,int,int) ; 
 int /*<<< orphan*/  BWN_RF_WRITE (struct bwn_mac*,int,int) ; 
 int /*<<< orphan*/  BWN_WRITE_2 (struct bwn_mac*,int,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int bwn_rf_2050_rfoverval (struct bwn_mac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwn_spu_workaround (struct bwn_mac*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint16_t
bwn_rf_init_bcm2050(struct bwn_mac *mac)
{
	struct bwn_phy *phy = &mac->mac_phy;
	uint32_t tmp1 = 0, tmp2 = 0;
	uint16_t rcc, i, j, pgactl, cck0, cck1, cck2, cck3, rfover, rfoverval,
	    analogover, analogoverval, crs0, classctl, lomask, loctl, syncctl,
	    radio0, radio1, radio2, reg0, reg1, reg2, radio78, reg, index;
	static const uint8_t rcc_table[] = {
		0x02, 0x03, 0x01, 0x0f,
		0x06, 0x07, 0x05, 0x0f,
		0x0a, 0x0b, 0x09, 0x0f,
		0x0e, 0x0f, 0x0d, 0x0f,
	};

	loctl = lomask = reg0 = classctl = crs0 = analogoverval = analogover =
	    rfoverval = rfover = cck3 = 0;
	radio0 = BWN_RF_READ(mac, 0x43);
	radio1 = BWN_RF_READ(mac, 0x51);
	radio2 = BWN_RF_READ(mac, 0x52);
	pgactl = BWN_PHY_READ(mac, BWN_PHY_PGACTL);
	cck0 = BWN_PHY_READ(mac, BWN_PHY_CCK(0x5a));
	cck1 = BWN_PHY_READ(mac, BWN_PHY_CCK(0x59));
	cck2 = BWN_PHY_READ(mac, BWN_PHY_CCK(0x58));

	if (phy->type == BWN_PHYTYPE_B) {
		cck3 = BWN_PHY_READ(mac, BWN_PHY_CCK(0x30));
		reg0 = BWN_READ_2(mac, 0x3ec);

		BWN_PHY_WRITE(mac, BWN_PHY_CCK(0x30), 0xff);
		BWN_WRITE_2(mac, 0x3ec, 0x3f3f);
	} else if (phy->gmode || phy->rev >= 2) {
		rfover = BWN_PHY_READ(mac, BWN_PHY_RFOVER);
		rfoverval = BWN_PHY_READ(mac, BWN_PHY_RFOVERVAL);
		analogover = BWN_PHY_READ(mac, BWN_PHY_ANALOGOVER);
		analogoverval = BWN_PHY_READ(mac, BWN_PHY_ANALOGOVERVAL);
		crs0 = BWN_PHY_READ(mac, BWN_PHY_CRS0);
		classctl = BWN_PHY_READ(mac, BWN_PHY_CLASSCTL);

		BWN_PHY_SET(mac, BWN_PHY_ANALOGOVER, 0x0003);
		BWN_PHY_MASK(mac, BWN_PHY_ANALOGOVERVAL, 0xfffc);
		BWN_PHY_MASK(mac, BWN_PHY_CRS0, 0x7fff);
		BWN_PHY_MASK(mac, BWN_PHY_CLASSCTL, 0xfffc);
		if (BWN_HAS_LOOPBACK(phy)) {
			lomask = BWN_PHY_READ(mac, BWN_PHY_LO_MASK);
			loctl = BWN_PHY_READ(mac, BWN_PHY_LO_CTL);
			if (phy->rev >= 3)
				BWN_PHY_WRITE(mac, BWN_PHY_LO_MASK, 0xc020);
			else
				BWN_PHY_WRITE(mac, BWN_PHY_LO_MASK, 0x8020);
			BWN_PHY_WRITE(mac, BWN_PHY_LO_CTL, 0);
		}

		BWN_PHY_WRITE(mac, BWN_PHY_RFOVERVAL,
		    bwn_rf_2050_rfoverval(mac, BWN_PHY_RFOVERVAL,
			BWN_LPD(0, 1, 1)));
		BWN_PHY_WRITE(mac, BWN_PHY_RFOVER,
		    bwn_rf_2050_rfoverval(mac, BWN_PHY_RFOVER, 0));
	}
	BWN_WRITE_2(mac, 0x3e2, BWN_READ_2(mac, 0x3e2) | 0x8000);

	syncctl = BWN_PHY_READ(mac, BWN_PHY_SYNCCTL);
	BWN_PHY_MASK(mac, BWN_PHY_SYNCCTL, 0xff7f);
	reg1 = BWN_READ_2(mac, 0x3e6);
	reg2 = BWN_READ_2(mac, 0x3f4);

	if (phy->analog == 0)
		BWN_WRITE_2(mac, 0x03e6, 0x0122);
	else {
		if (phy->analog >= 2)
			BWN_PHY_SETMASK(mac, BWN_PHY_CCK(0x03), 0xffbf, 0x40);
		BWN_WRITE_2(mac, BWN_CHANNEL_EXT,
		    (BWN_READ_2(mac, BWN_CHANNEL_EXT) | 0x2000));
	}

	reg = BWN_RF_READ(mac, 0x60);
	index = (reg & 0x001e) >> 1;
	rcc = (((rcc_table[index] << 1) | (reg & 0x0001)) | 0x0020);

	if (phy->type == BWN_PHYTYPE_B)
		BWN_RF_WRITE(mac, 0x78, 0x26);
	if (phy->gmode || phy->rev >= 2) {
		BWN_PHY_WRITE(mac, BWN_PHY_RFOVERVAL,
		    bwn_rf_2050_rfoverval(mac, BWN_PHY_RFOVERVAL,
			BWN_LPD(0, 1, 1)));
	}
	BWN_PHY_WRITE(mac, BWN_PHY_PGACTL, 0xbfaf);
	BWN_PHY_WRITE(mac, BWN_PHY_CCK(0x2b), 0x1403);
	if (phy->gmode || phy->rev >= 2) {
		BWN_PHY_WRITE(mac, BWN_PHY_RFOVERVAL,
		    bwn_rf_2050_rfoverval(mac, BWN_PHY_RFOVERVAL,
			BWN_LPD(0, 0, 1)));
	}
	BWN_PHY_WRITE(mac, BWN_PHY_PGACTL, 0xbfa0);
	BWN_RF_SET(mac, 0x51, 0x0004);
	if (phy->rf_rev == 8)
		BWN_RF_WRITE(mac, 0x43, 0x1f);
	else {
		BWN_RF_WRITE(mac, 0x52, 0);
		BWN_RF_SETMASK(mac, 0x43, 0xfff0, 0x0009);
	}
	BWN_PHY_WRITE(mac, BWN_PHY_CCK(0x58), 0);

	for (i = 0; i < 16; i++) {
		BWN_PHY_WRITE(mac, BWN_PHY_CCK(0x5a), 0x0480);
		BWN_PHY_WRITE(mac, BWN_PHY_CCK(0x59), 0xc810);
		BWN_PHY_WRITE(mac, BWN_PHY_CCK(0x58), 0x000d);
		if (phy->gmode || phy->rev >= 2) {
			BWN_PHY_WRITE(mac, BWN_PHY_RFOVERVAL,
			    bwn_rf_2050_rfoverval(mac,
				BWN_PHY_RFOVERVAL, BWN_LPD(1, 0, 1)));
		}
		BWN_PHY_WRITE(mac, BWN_PHY_PGACTL, 0xafb0);
		DELAY(10);
		if (phy->gmode || phy->rev >= 2) {
			BWN_PHY_WRITE(mac, BWN_PHY_RFOVERVAL,
			    bwn_rf_2050_rfoverval(mac,
				BWN_PHY_RFOVERVAL, BWN_LPD(1, 0, 1)));
		}
		BWN_PHY_WRITE(mac, BWN_PHY_PGACTL, 0xefb0);
		DELAY(10);
		if (phy->gmode || phy->rev >= 2) {
			BWN_PHY_WRITE(mac, BWN_PHY_RFOVERVAL,
			    bwn_rf_2050_rfoverval(mac,
				BWN_PHY_RFOVERVAL, BWN_LPD(1, 0, 0)));
		}
		BWN_PHY_WRITE(mac, BWN_PHY_PGACTL, 0xfff0);
		DELAY(20);
		tmp1 += BWN_PHY_READ(mac, BWN_PHY_LO_LEAKAGE);
		BWN_PHY_WRITE(mac, BWN_PHY_CCK(0x58), 0);
		if (phy->gmode || phy->rev >= 2) {
			BWN_PHY_WRITE(mac, BWN_PHY_RFOVERVAL,
			    bwn_rf_2050_rfoverval(mac,
				BWN_PHY_RFOVERVAL, BWN_LPD(1, 0, 1)));
		}
		BWN_PHY_WRITE(mac, BWN_PHY_PGACTL, 0xafb0);
	}
	DELAY(10);

	BWN_PHY_WRITE(mac, BWN_PHY_CCK(0x58), 0);
	tmp1++;
	tmp1 >>= 9;

	for (i = 0; i < 16; i++) {
		radio78 = (BWN_BITREV4(i) << 1) | 0x0020;
		BWN_RF_WRITE(mac, 0x78, radio78);
		DELAY(10);
		for (j = 0; j < 16; j++) {
			BWN_PHY_WRITE(mac, BWN_PHY_CCK(0x5a), 0x0d80);
			BWN_PHY_WRITE(mac, BWN_PHY_CCK(0x59), 0xc810);
			BWN_PHY_WRITE(mac, BWN_PHY_CCK(0x58), 0x000d);
			if (phy->gmode || phy->rev >= 2) {
				BWN_PHY_WRITE(mac, BWN_PHY_RFOVERVAL,
				    bwn_rf_2050_rfoverval(mac,
					BWN_PHY_RFOVERVAL, BWN_LPD(1, 0, 1)));
			}
			BWN_PHY_WRITE(mac, BWN_PHY_PGACTL, 0xafb0);
			DELAY(10);
			if (phy->gmode || phy->rev >= 2) {
				BWN_PHY_WRITE(mac, BWN_PHY_RFOVERVAL,
				    bwn_rf_2050_rfoverval(mac,
					BWN_PHY_RFOVERVAL, BWN_LPD(1, 0, 1)));
			}
			BWN_PHY_WRITE(mac, BWN_PHY_PGACTL, 0xefb0);
			DELAY(10);
			if (phy->gmode || phy->rev >= 2) {
				BWN_PHY_WRITE(mac, BWN_PHY_RFOVERVAL,
				    bwn_rf_2050_rfoverval(mac,
					BWN_PHY_RFOVERVAL, BWN_LPD(1, 0, 0)));
			}
			BWN_PHY_WRITE(mac, BWN_PHY_PGACTL, 0xfff0);
			DELAY(10);
			tmp2 += BWN_PHY_READ(mac, BWN_PHY_LO_LEAKAGE);
			BWN_PHY_WRITE(mac, BWN_PHY_CCK(0x58), 0);
			if (phy->gmode || phy->rev >= 2) {
				BWN_PHY_WRITE(mac, BWN_PHY_RFOVERVAL,
				    bwn_rf_2050_rfoverval(mac,
					BWN_PHY_RFOVERVAL, BWN_LPD(1, 0, 1)));
			}
			BWN_PHY_WRITE(mac, BWN_PHY_PGACTL, 0xafb0);
		}
		tmp2++;
		tmp2 >>= 8;
		if (tmp1 < tmp2)
			break;
	}

	BWN_PHY_WRITE(mac, BWN_PHY_PGACTL, pgactl);
	BWN_RF_WRITE(mac, 0x51, radio1);
	BWN_RF_WRITE(mac, 0x52, radio2);
	BWN_RF_WRITE(mac, 0x43, radio0);
	BWN_PHY_WRITE(mac, BWN_PHY_CCK(0x5a), cck0);
	BWN_PHY_WRITE(mac, BWN_PHY_CCK(0x59), cck1);
	BWN_PHY_WRITE(mac, BWN_PHY_CCK(0x58), cck2);
	BWN_WRITE_2(mac, 0x3e6, reg1);
	if (phy->analog != 0)
		BWN_WRITE_2(mac, 0x3f4, reg2);
	BWN_PHY_WRITE(mac, BWN_PHY_SYNCCTL, syncctl);
	bwn_spu_workaround(mac, phy->chan);
	if (phy->type == BWN_PHYTYPE_B) {
		BWN_PHY_WRITE(mac, BWN_PHY_CCK(0x30), cck3);
		BWN_WRITE_2(mac, 0x3ec, reg0);
	} else if (phy->gmode) {
		BWN_WRITE_2(mac, BWN_PHY_RADIO,
			    BWN_READ_2(mac, BWN_PHY_RADIO)
			    & 0x7fff);
		BWN_PHY_WRITE(mac, BWN_PHY_RFOVER, rfover);
		BWN_PHY_WRITE(mac, BWN_PHY_RFOVERVAL, rfoverval);
		BWN_PHY_WRITE(mac, BWN_PHY_ANALOGOVER, analogover);
		BWN_PHY_WRITE(mac, BWN_PHY_ANALOGOVERVAL,
			      analogoverval);
		BWN_PHY_WRITE(mac, BWN_PHY_CRS0, crs0);
		BWN_PHY_WRITE(mac, BWN_PHY_CLASSCTL, classctl);
		if (BWN_HAS_LOOPBACK(phy)) {
			BWN_PHY_WRITE(mac, BWN_PHY_LO_MASK, lomask);
			BWN_PHY_WRITE(mac, BWN_PHY_LO_CTL, loctl);
		}
	}

	return ((i > 15) ? radio78 : rcc);
}