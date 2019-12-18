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
struct TYPE_2__ {int rev; } ;
struct bwn_mac {TYPE_1__ mac_phy; } ;
typedef  int int8_t ;
typedef  int int32_t ;
typedef  enum n_rssi_type { ____Placeholder_n_rssi_type } n_rssi_type ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_NPHY_AFECTL_C1 ; 
 int /*<<< orphan*/  BWN_NPHY_AFECTL_C2 ; 
 int /*<<< orphan*/  BWN_NPHY_AFECTL_OVER ; 
 int /*<<< orphan*/  BWN_NPHY_AFECTL_OVER1 ; 
 int /*<<< orphan*/  BWN_NPHY_GPIO_HIOUT ; 
 int /*<<< orphan*/  BWN_NPHY_GPIO_LOOUT ; 
 int /*<<< orphan*/  BWN_NPHY_GPIO_SEL ; 
 int /*<<< orphan*/  BWN_NPHY_RFCTL_CMD ; 
 int /*<<< orphan*/  BWN_NPHY_RFCTL_LUT_TRSW_UP1 ; 
 int /*<<< orphan*/  BWN_NPHY_RFCTL_LUT_TRSW_UP2 ; 
 int /*<<< orphan*/  BWN_NPHY_RFCTL_OVER ; 
 int /*<<< orphan*/  BWN_NPHY_RFCTL_RSSIO1 ; 
 int /*<<< orphan*/  BWN_NPHY_RFCTL_RSSIO2 ; 
 int /*<<< orphan*/  BWN_NPHY_RSSI1 ; 
 int /*<<< orphan*/  BWN_NPHY_RSSI2 ; 
 int /*<<< orphan*/  BWN_NPHY_TXF_40CO_B1S0 ; 
 int /*<<< orphan*/  BWN_NPHY_TXF_40CO_B32S1 ; 
 int BWN_PHY_READ (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BWN_PHY_WRITE (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bwn_nphy_rssi_select (struct bwn_mac*,int,int) ; 

__attribute__((used)) static int bwn_nphy_poll_rssi(struct bwn_mac *mac, enum n_rssi_type rssi_type,
			      int32_t *buf, uint8_t nsamp)
{
	int i;
	int out;
	uint16_t save_regs_phy[9];
	uint16_t s[2];

	/* TODO: rev7+ is treated like rev3+, what about rev19+? */

	if (mac->mac_phy.rev >= 3) {
		save_regs_phy[0] = BWN_PHY_READ(mac, BWN_NPHY_AFECTL_C1);
		save_regs_phy[1] = BWN_PHY_READ(mac, BWN_NPHY_AFECTL_C2);
		save_regs_phy[2] = BWN_PHY_READ(mac,
						BWN_NPHY_RFCTL_LUT_TRSW_UP1);
		save_regs_phy[3] = BWN_PHY_READ(mac,
						BWN_NPHY_RFCTL_LUT_TRSW_UP2);
		save_regs_phy[4] = BWN_PHY_READ(mac, BWN_NPHY_AFECTL_OVER1);
		save_regs_phy[5] = BWN_PHY_READ(mac, BWN_NPHY_AFECTL_OVER);
		save_regs_phy[6] = BWN_PHY_READ(mac, BWN_NPHY_TXF_40CO_B1S0);
		save_regs_phy[7] = BWN_PHY_READ(mac, BWN_NPHY_TXF_40CO_B32S1);
		save_regs_phy[8] = 0;
	} else {
		save_regs_phy[0] = BWN_PHY_READ(mac, BWN_NPHY_AFECTL_C1);
		save_regs_phy[1] = BWN_PHY_READ(mac, BWN_NPHY_AFECTL_C2);
		save_regs_phy[2] = BWN_PHY_READ(mac, BWN_NPHY_AFECTL_OVER);
		save_regs_phy[3] = BWN_PHY_READ(mac, BWN_NPHY_RFCTL_CMD);
		save_regs_phy[4] = BWN_PHY_READ(mac, BWN_NPHY_RFCTL_OVER);
		save_regs_phy[5] = BWN_PHY_READ(mac, BWN_NPHY_RFCTL_RSSIO1);
		save_regs_phy[6] = BWN_PHY_READ(mac, BWN_NPHY_RFCTL_RSSIO2);
		save_regs_phy[7] = 0;
		save_regs_phy[8] = 0;
	}

	bwn_nphy_rssi_select(mac, 5, rssi_type);

	if (mac->mac_phy.rev < 2) {
		save_regs_phy[8] = BWN_PHY_READ(mac, BWN_NPHY_GPIO_SEL);
		BWN_PHY_WRITE(mac, BWN_NPHY_GPIO_SEL, 5);
	}

	for (i = 0; i < 4; i++)
		buf[i] = 0;

	for (i = 0; i < nsamp; i++) {
		if (mac->mac_phy.rev < 2) {
			s[0] = BWN_PHY_READ(mac, BWN_NPHY_GPIO_LOOUT);
			s[1] = BWN_PHY_READ(mac, BWN_NPHY_GPIO_HIOUT);
		} else {
			s[0] = BWN_PHY_READ(mac, BWN_NPHY_RSSI1);
			s[1] = BWN_PHY_READ(mac, BWN_NPHY_RSSI2);
		}

		buf[0] += ((int8_t)((s[0] & 0x3F) << 2)) >> 2;
		buf[1] += ((int8_t)(((s[0] >> 8) & 0x3F) << 2)) >> 2;
		buf[2] += ((int8_t)((s[1] & 0x3F) << 2)) >> 2;
		buf[3] += ((int8_t)(((s[1] >> 8) & 0x3F) << 2)) >> 2;
	}
	out = (buf[0] & 0xFF) << 24 | (buf[1] & 0xFF) << 16 |
		(buf[2] & 0xFF) << 8 | (buf[3] & 0xFF);

	if (mac->mac_phy.rev < 2)
		BWN_PHY_WRITE(mac, BWN_NPHY_GPIO_SEL, save_regs_phy[8]);

	if (mac->mac_phy.rev >= 3) {
		BWN_PHY_WRITE(mac, BWN_NPHY_AFECTL_C1, save_regs_phy[0]);
		BWN_PHY_WRITE(mac, BWN_NPHY_AFECTL_C2, save_regs_phy[1]);
		BWN_PHY_WRITE(mac, BWN_NPHY_RFCTL_LUT_TRSW_UP1,
				save_regs_phy[2]);
		BWN_PHY_WRITE(mac, BWN_NPHY_RFCTL_LUT_TRSW_UP2,
				save_regs_phy[3]);
		BWN_PHY_WRITE(mac, BWN_NPHY_AFECTL_OVER1, save_regs_phy[4]);
		BWN_PHY_WRITE(mac, BWN_NPHY_AFECTL_OVER, save_regs_phy[5]);
		BWN_PHY_WRITE(mac, BWN_NPHY_TXF_40CO_B1S0, save_regs_phy[6]);
		BWN_PHY_WRITE(mac, BWN_NPHY_TXF_40CO_B32S1, save_regs_phy[7]);
	} else {
		BWN_PHY_WRITE(mac, BWN_NPHY_AFECTL_C1, save_regs_phy[0]);
		BWN_PHY_WRITE(mac, BWN_NPHY_AFECTL_C2, save_regs_phy[1]);
		BWN_PHY_WRITE(mac, BWN_NPHY_AFECTL_OVER, save_regs_phy[2]);
		BWN_PHY_WRITE(mac, BWN_NPHY_RFCTL_CMD, save_regs_phy[3]);
		BWN_PHY_WRITE(mac, BWN_NPHY_RFCTL_OVER, save_regs_phy[4]);
		BWN_PHY_WRITE(mac, BWN_NPHY_RFCTL_RSSIO1, save_regs_phy[5]);
		BWN_PHY_WRITE(mac, BWN_NPHY_RFCTL_RSSIO2, save_regs_phy[6]);
	}

	return out;
}