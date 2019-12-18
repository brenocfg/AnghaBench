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
struct TYPE_2__ {scalar_t__ phy_mode; } ;
struct bwi_mac {TYPE_1__ mac_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWI_COMM_MOBJ ; 
 scalar_t__ BWI_COMM_MOBJ_TSSI_DS ; 
 scalar_t__ BWI_COMM_MOBJ_TSSI_OFDM ; 
 int /*<<< orphan*/  BWI_HI_TSSI_MASK ; 
 int /*<<< orphan*/  BWI_INVALID_TSSI ; 
 int /*<<< orphan*/  BWI_LO_TSSI_MASK ; 
 scalar_t__ IEEE80211_MODE_11A ; 
 int /*<<< orphan*/  MOBJ_WRITE_2 (struct bwi_mac*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int __SHIFTIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
bwi_rf_clear_tssi(struct bwi_mac *mac)
{
	/* XXX use function pointer */
	if (mac->mac_phy.phy_mode == IEEE80211_MODE_11A) {
		/* TODO:11A */
	} else {
		uint16_t val;
		int i;

		val = __SHIFTIN(BWI_INVALID_TSSI, BWI_LO_TSSI_MASK) |
		      __SHIFTIN(BWI_INVALID_TSSI, BWI_HI_TSSI_MASK);

		for (i = 0; i < 2; ++i) {
			MOBJ_WRITE_2(mac, BWI_COMM_MOBJ,
				BWI_COMM_MOBJ_TSSI_DS + (i * 2), val);
		}

		for (i = 0; i < 2; ++i) {
			MOBJ_WRITE_2(mac, BWI_COMM_MOBJ,
				BWI_COMM_MOBJ_TSSI_OFDM + (i * 2), val);
		}
	}
}