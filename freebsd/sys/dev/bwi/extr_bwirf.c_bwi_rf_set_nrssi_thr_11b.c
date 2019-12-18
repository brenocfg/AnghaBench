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
typedef  int uint16_t ;
struct bwi_rf {scalar_t__ rf_type; int rf_rev; int* rf_nrssi; } ;
struct bwi_mac {TYPE_1__* mac_sc; struct bwi_rf mac_rf; } ;
typedef  int int32_t ;
struct TYPE_2__ {int sc_card_flags; } ;

/* Variables and functions */
 int BWI_CARD_F_SW_NRSSI ; 
 int BWI_PHYR_NRSSI_THR_11B ; 
 scalar_t__ BWI_RF_T_BCM2050 ; 
 int /*<<< orphan*/  PHY_READ (struct bwi_mac*,int) ; 
 int /*<<< orphan*/  PHY_WRITE (struct bwi_mac*,int,int) ; 

__attribute__((used)) static void
bwi_rf_set_nrssi_thr_11b(struct bwi_mac *mac)
{
	struct bwi_rf *rf = &mac->mac_rf;
	int32_t thr;

	if (rf->rf_type != BWI_RF_T_BCM2050 ||
	    (mac->mac_sc->sc_card_flags & BWI_CARD_F_SW_NRSSI) == 0)
		return;

	/*
	 * Calculate nrssi threshold
	 */
	if (rf->rf_rev >= 6) {
		thr = (rf->rf_nrssi[1] - rf->rf_nrssi[0]) * 32;
		thr += 20 * (rf->rf_nrssi[0] + 1);
		thr /= 40;
	} else {
		thr = rf->rf_nrssi[1] - 5;
	}
	if (thr < 0)
		thr = 0;
	else if (thr > 0x3e)
		thr = 0x3e;

	PHY_READ(mac, BWI_PHYR_NRSSI_THR_11B);	/* dummy read */
	PHY_WRITE(mac, BWI_PHYR_NRSSI_THR_11B, (((uint16_t)thr) << 8) | 0x1c);

	if (rf->rf_rev >= 6) {
		PHY_WRITE(mac, 0x87, 0xe0d);
		PHY_WRITE(mac, 0x86, 0xc0b);
		PHY_WRITE(mac, 0x85, 0xa09);
		PHY_WRITE(mac, 0x84, 0x808);
		PHY_WRITE(mac, 0x83, 0x808);
		PHY_WRITE(mac, 0x82, 0x604);
		PHY_WRITE(mac, 0x81, 0x302);
		PHY_WRITE(mac, 0x80, 0x100);
	}
}