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
typedef  int u_int ;
struct bwn_wpair {int member_1; int value; int /*<<< orphan*/  const reg; int /*<<< orphan*/  const member_0; } ;
struct bwn_softc {int /*<<< orphan*/  sc_dev; } ;
struct bwn_mac {struct bwn_softc* mac_sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_CLOCK_ALP ; 
 int /*<<< orphan*/  const BWN_B2063_PA_SP7 ; 
 int /*<<< orphan*/  BWN_B2063_PLL_SP1 ; 
#define  BWN_B2063_RC_CALIB_CTL1 134 
#define  BWN_B2063_RC_CALIB_CTL2 133 
#define  BWN_B2063_RC_CALIB_CTL3 132 
#define  BWN_B2063_RC_CALIB_CTL4 131 
#define  BWN_B2063_RC_CALIB_CTL5 130 
 int /*<<< orphan*/  const BWN_B2063_RC_CALIB_CTL6 ; 
#define  BWN_B2063_RX_BB_SP8 129 
#define  BWN_B2063_TX_BB_SP3 128 
 int /*<<< orphan*/  BWN_RF_MASK (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int BWN_RF_READ (struct bwn_mac*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  BWN_RF_WRITE (struct bwn_mac*,int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int N (struct bwn_wpair const*) ; 
 int bhnd_get_clock_freq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
bwn_phy_lp_rxcal_r2(struct bwn_mac *mac)
{
	struct bwn_softc *sc = mac->mac_sc;
	static const struct bwn_wpair v1[] = {
		{ BWN_B2063_RX_BB_SP8, 0x0 },
		{ BWN_B2063_RC_CALIB_CTL1, 0x7e },
		{ BWN_B2063_RC_CALIB_CTL1, 0x7c },
		{ BWN_B2063_RC_CALIB_CTL2, 0x15 },
		{ BWN_B2063_RC_CALIB_CTL3, 0x70 },
		{ BWN_B2063_RC_CALIB_CTL4, 0x52 },
		{ BWN_B2063_RC_CALIB_CTL5, 0x1 },
		{ BWN_B2063_RC_CALIB_CTL1, 0x7d }
	};
	static const struct bwn_wpair v2[] = {
		{ BWN_B2063_TX_BB_SP3, 0x0 },
		{ BWN_B2063_RC_CALIB_CTL1, 0x7e },
		{ BWN_B2063_RC_CALIB_CTL1, 0x7c },
		{ BWN_B2063_RC_CALIB_CTL2, 0x55 },
		{ BWN_B2063_RC_CALIB_CTL3, 0x76 }
	};
	u_int freqxtal;
	int error, i;
	uint8_t tmp;

	error = bhnd_get_clock_freq(sc->sc_dev, BHND_CLOCK_ALP, &freqxtal);
	if (error) {
		device_printf(sc->sc_dev, "failed to fetch clock frequency: %d",
		    error);
		return (error);
	}

	tmp = BWN_RF_READ(mac, BWN_B2063_RX_BB_SP8) & 0xff;

	for (i = 0; i < 2; i++)
		BWN_RF_WRITE(mac, v1[i].reg, v1[i].value);
	BWN_RF_MASK(mac, BWN_B2063_PLL_SP1, 0xf7);
	for (i = 2; i < N(v1); i++)
		BWN_RF_WRITE(mac, v1[i].reg, v1[i].value);
	for (i = 0; i < 10000; i++) {
		if (BWN_RF_READ(mac, BWN_B2063_RC_CALIB_CTL6) & 0x2)
			break;
		DELAY(1000);
	}

	if (!(BWN_RF_READ(mac, BWN_B2063_RC_CALIB_CTL6) & 0x2))
		BWN_RF_WRITE(mac, BWN_B2063_RX_BB_SP8, tmp);

	tmp = BWN_RF_READ(mac, BWN_B2063_TX_BB_SP3) & 0xff;

	for (i = 0; i < N(v2); i++)
		BWN_RF_WRITE(mac, v2[i].reg, v2[i].value);
	if (freqxtal == 24000000) {
		BWN_RF_WRITE(mac, BWN_B2063_RC_CALIB_CTL4, 0xfc);
		BWN_RF_WRITE(mac, BWN_B2063_RC_CALIB_CTL5, 0x0);
	} else {
		BWN_RF_WRITE(mac, BWN_B2063_RC_CALIB_CTL4, 0x13);
		BWN_RF_WRITE(mac, BWN_B2063_RC_CALIB_CTL5, 0x1);
	}
	BWN_RF_WRITE(mac, BWN_B2063_PA_SP7, 0x7d);
	for (i = 0; i < 10000; i++) {
		if (BWN_RF_READ(mac, BWN_B2063_RC_CALIB_CTL6) & 0x2)
			break;
		DELAY(1000);
	}
	if (!(BWN_RF_READ(mac, BWN_B2063_RC_CALIB_CTL6) & 0x2))
		BWN_RF_WRITE(mac, BWN_B2063_TX_BB_SP3, tmp);
	BWN_RF_WRITE(mac, BWN_B2063_RC_CALIB_CTL1, 0x7e);

	return (0);
}