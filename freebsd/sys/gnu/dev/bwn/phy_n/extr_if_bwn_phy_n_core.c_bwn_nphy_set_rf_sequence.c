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
struct bwn_phy_n {scalar_t__ hang_avoid; } ;
struct TYPE_2__ {int rev; struct bwn_phy_n* phy_n; } ;
struct bwn_mac {TYPE_1__ mac_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_NTAB8 (int,int) ; 
 int /*<<< orphan*/  bwn_nphy_stay_in_carrier_search (struct bwn_mac*,int) ; 
 int /*<<< orphan*/  bwn_ntab_write (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bwn_ntab_write_bulk (struct bwn_mac*,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static void bwn_nphy_set_rf_sequence(struct bwn_mac *mac, uint8_t cmd,
					uint8_t *events, uint8_t *delays, uint8_t length)
{
	struct bwn_phy_n *nphy = mac->mac_phy.phy_n;
	uint8_t i;
	uint8_t end = (mac->mac_phy.rev >= 3) ? 0x1F : 0x0F;
	uint16_t offset1 = cmd << 4;
	uint16_t offset2 = offset1 + 0x80;

	if (nphy->hang_avoid)
		bwn_nphy_stay_in_carrier_search(mac, true);

	bwn_ntab_write_bulk(mac, BWN_NTAB8(7, offset1), length, events);
	bwn_ntab_write_bulk(mac, BWN_NTAB8(7, offset2), length, delays);

	for (i = length; i < 16; i++) {
		bwn_ntab_write(mac, BWN_NTAB8(7, offset1 + i), end);
		bwn_ntab_write(mac, BWN_NTAB8(7, offset2 + i), 1);
	}

	if (nphy->hang_avoid)
		bwn_nphy_stay_in_carrier_search(mac, false);
}