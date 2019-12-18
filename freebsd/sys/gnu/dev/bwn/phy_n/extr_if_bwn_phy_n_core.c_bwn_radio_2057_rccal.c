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
typedef  int /*<<< orphan*/  uint16_t ;
struct bwn_phy {int rf_rev; } ;
struct bwn_mac {int /*<<< orphan*/  mac_sc; struct bwn_phy mac_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_DBGPRINTF (struct bwn_mac*,char*) ; 
 int /*<<< orphan*/  BWN_ERRPRINTF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  BWN_RF_MASK (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BWN_RF_READ (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BWN_RF_WRITE (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  R2057_RCCAL_DONE_OSCCAP ; 
 int /*<<< orphan*/  R2057_RCCAL_MASTER ; 
 int /*<<< orphan*/  R2057_RCCAL_START_R1_Q1_P1 ; 
 int /*<<< orphan*/  R2057_RCCAL_TRC0 ; 
 int /*<<< orphan*/  R2057_RCCAL_X1 ; 
 int /*<<< orphan*/  R2057v7_RCCAL_MASTER ; 
 int /*<<< orphan*/  bwn_radio_wait_value (struct bwn_mac*,int /*<<< orphan*/ ,int,int,int,int) ; 

__attribute__((used)) static uint16_t bwn_radio_2057_rccal(struct bwn_mac *mac)
{
	struct bwn_phy *phy = &mac->mac_phy;
	bool special = (phy->rf_rev == 3 || phy->rf_rev == 4 ||
			phy->rf_rev == 6);
	uint16_t tmp;

	/* Setup cal */
	if (special) {
		BWN_RF_WRITE(mac, R2057_RCCAL_MASTER, 0x61);
		BWN_RF_WRITE(mac, R2057_RCCAL_TRC0, 0xC0);
	} else {
		BWN_RF_WRITE(mac, R2057v7_RCCAL_MASTER, 0x61);
		BWN_RF_WRITE(mac, R2057_RCCAL_TRC0, 0xE9);
	}
	BWN_RF_WRITE(mac, R2057_RCCAL_X1, 0x6E);

	/* Start, wait, stop */
	BWN_RF_WRITE(mac, R2057_RCCAL_START_R1_Q1_P1, 0x55);
	if (!bwn_radio_wait_value(mac, R2057_RCCAL_DONE_OSCCAP, 2, 2, 500,
				  5000000))
		BWN_DBGPRINTF(mac, "Radio 0x2057 rccal timeout\n");
	/* 35..70 */
	DELAY(70);
	BWN_RF_WRITE(mac, R2057_RCCAL_START_R1_Q1_P1, 0x15);
	/* 70..140 */
	DELAY(140);

	/* Setup cal */
	if (special) {
		BWN_RF_WRITE(mac, R2057_RCCAL_MASTER, 0x69);
		BWN_RF_WRITE(mac, R2057_RCCAL_TRC0, 0xB0);
	} else {
		BWN_RF_WRITE(mac, R2057v7_RCCAL_MASTER, 0x69);
		BWN_RF_WRITE(mac, R2057_RCCAL_TRC0, 0xD5);
	}
	BWN_RF_WRITE(mac, R2057_RCCAL_X1, 0x6E);

	/* Start, wait, stop */
	/* 35..70 */
	DELAY(70);
	BWN_RF_WRITE(mac, R2057_RCCAL_START_R1_Q1_P1, 0x55);
	/* 70..140 */
	DELAY(140);
	if (!bwn_radio_wait_value(mac, R2057_RCCAL_DONE_OSCCAP, 2, 2, 500,
				  5000000))
		BWN_DBGPRINTF(mac, "Radio 0x2057 rccal timeout\n");
	/* 35..70 */
	DELAY(70);
	BWN_RF_WRITE(mac, R2057_RCCAL_START_R1_Q1_P1, 0x15);
	/* 70..140 */
	DELAY(140);

	/* Setup cal */
	if (special) {
		BWN_RF_WRITE(mac, R2057_RCCAL_MASTER, 0x73);
		BWN_RF_WRITE(mac, R2057_RCCAL_X1, 0x28);
		BWN_RF_WRITE(mac, R2057_RCCAL_TRC0, 0xB0);
	} else {
		BWN_RF_WRITE(mac, R2057v7_RCCAL_MASTER, 0x73);
		BWN_RF_WRITE(mac, R2057_RCCAL_X1, 0x6E);
		BWN_RF_WRITE(mac, R2057_RCCAL_TRC0, 0x99);
	}

	/* Start, wait, stop */
	/* 35..70 */
	DELAY(70);
	BWN_RF_WRITE(mac, R2057_RCCAL_START_R1_Q1_P1, 0x55);
	/* 70..140 */
	DELAY(140);
	if (!bwn_radio_wait_value(mac, R2057_RCCAL_DONE_OSCCAP, 2, 2, 500,
				  5000000)) {
		BWN_ERRPRINTF(mac->mac_sc, "Radio 0x2057 rcal timeout\n");
		return 0;
	}
	tmp = BWN_RF_READ(mac, R2057_RCCAL_DONE_OSCCAP);
	/* 35..70 */
	DELAY(70);
	BWN_RF_WRITE(mac, R2057_RCCAL_START_R1_Q1_P1, 0x15);
	/* 70..140 */
	DELAY(140);

	if (special)
		BWN_RF_MASK(mac, R2057_RCCAL_MASTER, ~0x1);
	else
		BWN_RF_MASK(mac, R2057v7_RCCAL_MASTER, ~0x1);

	return tmp;
}