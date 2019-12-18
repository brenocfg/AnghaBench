#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
struct TYPE_3__ {int phy_flags; } ;
struct bwi_mac {int /*<<< orphan*/  mac_rf; TYPE_2__* mac_sc; TYPE_1__ mac_phy; } ;
typedef  int int32_t ;
typedef  int int16_t ;
struct TYPE_4__ {int sc_card_flags; } ;

/* Variables and functions */
 int BWI_CARD_F_SW_NRSSI ; 
 int /*<<< orphan*/  BWI_PHYR_NRSSI_THR_11G ; 
 int BWI_PHY_F_LINKED ; 
 int /*<<< orphan*/  NRSSI_THR1_MASK ; 
 int /*<<< orphan*/  NRSSI_THR2_MASK ; 
 int /*<<< orphan*/  PHY_FILT_SETBITS (struct bwi_mac*,int /*<<< orphan*/ ,int,int) ; 
 int __SHIFTIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int _nrssi_threshold (int /*<<< orphan*/ *,int) ; 
 int bwi_nrssi_read (struct bwi_mac*,int) ; 

__attribute__((used)) static void
bwi_rf_set_nrssi_thr_11g(struct bwi_mac *mac)
{
	int32_t thr1, thr2;
	uint16_t thr;

	/*
	 * Find the two nrssi thresholds
	 */
	if ((mac->mac_phy.phy_flags & BWI_PHY_F_LINKED) == 0 ||
	    (mac->mac_sc->sc_card_flags & BWI_CARD_F_SW_NRSSI) == 0) {
	    	int16_t nrssi;

		nrssi = bwi_nrssi_read(mac, 0x20);
		if (nrssi >= 32)
			nrssi -= 64;

		if (nrssi < 3) {
			thr1 = 0x2b;
			thr2 = 0x27;
		} else {
			thr1 = 0x2d;
			thr2 = 0x2b;
		}
	} else {
		/* TODO Interfere mode */
		thr1 = _nrssi_threshold(&mac->mac_rf, 0x11);
		thr2 = _nrssi_threshold(&mac->mac_rf, 0xe);
	}

#define NRSSI_THR1_MASK	__BITS(5, 0)
#define NRSSI_THR2_MASK	__BITS(11, 6)

	thr = __SHIFTIN((uint32_t)thr1, NRSSI_THR1_MASK) |
	      __SHIFTIN((uint32_t)thr2, NRSSI_THR2_MASK);
	PHY_FILT_SETBITS(mac, BWI_PHYR_NRSSI_THR_11G, 0xf000, thr);

#undef NRSSI_THR1_MASK
#undef NRSSI_THR2_MASK
}