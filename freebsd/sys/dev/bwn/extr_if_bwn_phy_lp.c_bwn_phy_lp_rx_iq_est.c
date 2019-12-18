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
typedef  int /*<<< orphan*/  uint16_t ;
struct bwn_phy_lp_iq_est {int ie_iqprod; int ie_ipwr; int ie_qpwr; } ;
struct bwn_mac {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_PHY_CRSGAIN_CTL ; 
 int /*<<< orphan*/  BWN_PHY_IQ_ACC_HI_ADDR ; 
 int /*<<< orphan*/  BWN_PHY_IQ_ACC_LO_ADDR ; 
 int /*<<< orphan*/  BWN_PHY_IQ_ENABLE_WAIT_TIME_ADDR ; 
 int /*<<< orphan*/  BWN_PHY_IQ_I_PWR_ACC_HI_ADDR ; 
 int /*<<< orphan*/  BWN_PHY_IQ_I_PWR_ACC_LO_ADDR ; 
 int /*<<< orphan*/  BWN_PHY_IQ_NUM_SMPLS_ADDR ; 
 int /*<<< orphan*/  BWN_PHY_IQ_Q_PWR_ACC_HI_ADDR ; 
 int /*<<< orphan*/  BWN_PHY_IQ_Q_PWR_ACC_LO_ADDR ; 
 int /*<<< orphan*/  BWN_PHY_MASK (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int BWN_PHY_READ (struct bwn_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BWN_PHY_SET (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BWN_PHY_SETMASK (struct bwn_mac*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  BWN_PHY_WRITE (struct bwn_mac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DELAY (int) ; 

__attribute__((used)) static uint8_t
bwn_phy_lp_rx_iq_est(struct bwn_mac *mac, uint16_t sample, uint8_t time,
    struct bwn_phy_lp_iq_est *ie)
{
	int i;

	BWN_PHY_MASK(mac, BWN_PHY_CRSGAIN_CTL, 0xfff7);
	BWN_PHY_WRITE(mac, BWN_PHY_IQ_NUM_SMPLS_ADDR, sample);
	BWN_PHY_SETMASK(mac, BWN_PHY_IQ_ENABLE_WAIT_TIME_ADDR, 0xff00, time);
	BWN_PHY_MASK(mac, BWN_PHY_IQ_ENABLE_WAIT_TIME_ADDR, 0xfeff);
	BWN_PHY_SET(mac, BWN_PHY_IQ_ENABLE_WAIT_TIME_ADDR, 0x200);

	for (i = 0; i < 500; i++) {
		if (!(BWN_PHY_READ(mac,
		    BWN_PHY_IQ_ENABLE_WAIT_TIME_ADDR) & 0x200))
			break;
		DELAY(1000);
	}
	if ((BWN_PHY_READ(mac, BWN_PHY_IQ_ENABLE_WAIT_TIME_ADDR) & 0x200)) {
		BWN_PHY_SET(mac, BWN_PHY_CRSGAIN_CTL, 0x8);
		return 0;
	}

	ie->ie_iqprod = BWN_PHY_READ(mac, BWN_PHY_IQ_ACC_HI_ADDR);
	ie->ie_iqprod <<= 16;
	ie->ie_iqprod |= BWN_PHY_READ(mac, BWN_PHY_IQ_ACC_LO_ADDR);
	ie->ie_ipwr = BWN_PHY_READ(mac, BWN_PHY_IQ_I_PWR_ACC_HI_ADDR);
	ie->ie_ipwr <<= 16;
	ie->ie_ipwr |= BWN_PHY_READ(mac, BWN_PHY_IQ_I_PWR_ACC_LO_ADDR);
	ie->ie_qpwr = BWN_PHY_READ(mac, BWN_PHY_IQ_Q_PWR_ACC_HI_ADDR);
	ie->ie_qpwr <<= 16;
	ie->ie_qpwr |= BWN_PHY_READ(mac, BWN_PHY_IQ_Q_PWR_ACC_LO_ADDR);

	BWN_PHY_SET(mac, BWN_PHY_CRSGAIN_CTL, 0x8);
	return 1;
}