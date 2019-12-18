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
struct bwi_tpctl {scalar_t__ bbp_atten; scalar_t__ rf_atten; scalar_t__ tp_ctrl1; } ;
struct bwi_rf {int rf_rev; scalar_t__ rf_type; } ;
struct TYPE_2__ {scalar_t__ phy_mode; } ;
struct bwi_mac {TYPE_1__ mac_phy; struct bwi_tpctl mac_tpctl; struct bwi_rf mac_rf; } ;

/* Variables and functions */
 scalar_t__ BWI_BBP_ATTEN_MAX ; 
 int /*<<< orphan*/  BWI_COMM_MOBJ ; 
 int /*<<< orphan*/  BWI_COMM_MOBJ_RF_ATTEN ; 
 int /*<<< orphan*/  BWI_RFR_ATTEN ; 
 int /*<<< orphan*/  BWI_RFR_TXPWR ; 
 int /*<<< orphan*/  BWI_RFR_TXPWR1_MASK ; 
 scalar_t__ BWI_RF_ATTEN_MAX0 ; 
 scalar_t__ BWI_RF_ATTEN_MAX1 ; 
 scalar_t__ BWI_RF_T_BCM2050 ; 
 scalar_t__ BWI_TPCTL1_MAX ; 
 scalar_t__ IEEE80211_MODE_11G ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MOBJ_WRITE_2 (struct bwi_mac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  RF_FILT_SETBITS (struct bwi_mac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RF_WRITE (struct bwi_mac*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  __SHIFTIN (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwi_phy_set_bbp_atten (struct bwi_mac*,scalar_t__) ; 
 int /*<<< orphan*/  bwi_rf_lo_adjust (struct bwi_mac*,struct bwi_tpctl*) ; 

void
bwi_mac_set_tpctl_11bg(struct bwi_mac *mac, const struct bwi_tpctl *new_tpctl)
{
	struct bwi_rf *rf = &mac->mac_rf;
	struct bwi_tpctl *tpctl = &mac->mac_tpctl;

	if (new_tpctl != NULL) {
		KASSERT(new_tpctl->bbp_atten <= BWI_BBP_ATTEN_MAX,
		    ("bbp_atten %d", new_tpctl->bbp_atten));
		KASSERT(new_tpctl->rf_atten <=
			 (rf->rf_rev < 6 ? BWI_RF_ATTEN_MAX0
			 		 : BWI_RF_ATTEN_MAX1),
		    ("rf_atten %d", new_tpctl->rf_atten));
		KASSERT(new_tpctl->tp_ctrl1 <= BWI_TPCTL1_MAX,
		    ("tp_ctrl1 %d", new_tpctl->tp_ctrl1));

		tpctl->bbp_atten = new_tpctl->bbp_atten;
		tpctl->rf_atten = new_tpctl->rf_atten;
		tpctl->tp_ctrl1 = new_tpctl->tp_ctrl1;
	}

	/* Set BBP attenuation */
	bwi_phy_set_bbp_atten(mac, tpctl->bbp_atten);

	/* Set RF attenuation */
	RF_WRITE(mac, BWI_RFR_ATTEN, tpctl->rf_atten);
	MOBJ_WRITE_2(mac, BWI_COMM_MOBJ, BWI_COMM_MOBJ_RF_ATTEN,
		     tpctl->rf_atten);

	/* Set TX power */
	if (rf->rf_type == BWI_RF_T_BCM2050) {
		RF_FILT_SETBITS(mac, BWI_RFR_TXPWR, ~BWI_RFR_TXPWR1_MASK,
			__SHIFTIN(tpctl->tp_ctrl1, BWI_RFR_TXPWR1_MASK));
	}

	/* Adjust RF Local Oscillator */
	if (mac->mac_phy.phy_mode == IEEE80211_MODE_11G)
		bwi_rf_lo_adjust(mac, tpctl);
}