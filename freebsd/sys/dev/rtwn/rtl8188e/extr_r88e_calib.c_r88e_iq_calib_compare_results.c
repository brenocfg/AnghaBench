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
struct rtwn_softc {int dummy; } ;

/* Variables and functions */
 scalar_t__ RTWN_IQ_CAL_MAX_TOLERANCE ; 
 scalar_t__ abs (int) ; 

__attribute__((used)) static int
r88e_iq_calib_compare_results(struct rtwn_softc *sc, uint16_t tx1[2],
    uint16_t rx1[2], uint16_t tx2[2], uint16_t rx2[2])
{
	int i, tx_ok, rx_ok;

	tx_ok = rx_ok = 0;
	for (i = 0; i < 2; i++)	{
		if (tx1[i] == 0xff || tx2[i] == 0xff ||
		    rx1[i] == 0xff || rx2[i] == 0xff)
			continue;

		tx_ok = (abs(tx1[i] - tx2[i]) <= RTWN_IQ_CAL_MAX_TOLERANCE);
		rx_ok = (abs(rx1[i] - rx2[i]) <= RTWN_IQ_CAL_MAX_TOLERANCE);
	}

	return (tx_ok && rx_ok);
}