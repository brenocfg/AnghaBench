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
typedef  int uint16_t ;
struct rtwn_softc {int ntxchains; } ;

/* Variables and functions */
 scalar_t__ RTWN_IQ_CAL_MAX_TOLERANCE ; 
 scalar_t__ abs (int) ; 

__attribute__((used)) static int
r92c_iq_calib_compare_results(struct rtwn_softc *sc, uint16_t tx1[2][2],
    uint16_t rx1[2][2], uint16_t tx2[2][2], uint16_t rx2[2][2])
{
	int chain, i, tx_ok[2], rx_ok[2];

	tx_ok[0] = tx_ok[1] = rx_ok[0] = rx_ok[1] = 0;
	for (chain = 0; chain < sc->ntxchains; chain++) {
		for (i = 0; i < 2; i++)	{
			if (tx1[chain][i] == 0xff || tx2[chain][i] == 0xff ||
			    rx1[chain][i] == 0xff || rx2[chain][i] == 0xff)
				continue;

			tx_ok[chain] = (abs(tx1[chain][i] - tx2[chain][i]) <=
			    RTWN_IQ_CAL_MAX_TOLERANCE);

			rx_ok[chain] = (abs(rx1[chain][i] - rx2[chain][i]) <=
			    RTWN_IQ_CAL_MAX_TOLERANCE);
		}
	}

	if (sc->ntxchains > 1)
		return (tx_ok[0] && tx_ok[1] && rx_ok[0] && rx_ok[1]);
	else
		return (tx_ok[0] && rx_ok[0]);
}