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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
struct bwi_phy {int phy_flags; } ;
struct bwi_mac {struct bwi_phy mac_phy; } ;

/* Variables and functions */
 int BWI_PHY_F_LINKED ; 
 int /*<<< orphan*/  DELAY (int) ; 
 scalar_t__ PHY_READ (struct bwi_mac*,int) ; 
 int /*<<< orphan*/  PHY_WRITE (struct bwi_mac*,int,int) ; 

__attribute__((used)) static uint32_t
bwi_rf_lo_devi_measure(struct bwi_mac *mac, uint16_t ctrl)
{
	struct bwi_phy *phy = &mac->mac_phy;
	uint32_t devi = 0;
	int i;

	if (phy->phy_flags & BWI_PHY_F_LINKED)
		ctrl <<= 8;

	for (i = 0; i < 8; ++i) {
		if (phy->phy_flags & BWI_PHY_F_LINKED) {
			PHY_WRITE(mac, 0x15, 0xe300);
			PHY_WRITE(mac, 0x812, ctrl | 0xb0);
			DELAY(5);
			PHY_WRITE(mac, 0x812, ctrl | 0xb2);
			DELAY(2);
			PHY_WRITE(mac, 0x812, ctrl | 0xb3);
			DELAY(4);
			PHY_WRITE(mac, 0x15, 0xf300);
		} else {
			PHY_WRITE(mac, 0x15, ctrl | 0xefa0);
			DELAY(2);
			PHY_WRITE(mac, 0x15, ctrl | 0xefe0);
			DELAY(4);
			PHY_WRITE(mac, 0x15, ctrl | 0xffe0);
		}
		DELAY(8);
		devi += PHY_READ(mac, 0x2d);
	}
	return devi;
}