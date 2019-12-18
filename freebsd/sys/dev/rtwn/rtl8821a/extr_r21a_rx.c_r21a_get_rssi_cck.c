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
struct rtwn_softc {int dummy; } ;
struct r12a_rx_phystat {int* cfosho; } ;
typedef  int int8_t ;

/* Variables and functions */

int8_t
r21a_get_rssi_cck(struct rtwn_softc *sc, void *physt)
{
	struct r12a_rx_phystat *stat = (struct r12a_rx_phystat *)physt;
	int8_t lna_idx, rssi;

	lna_idx = (stat->cfosho[0] & 0xe0) >> 5;
	rssi = -6 - 2*(stat->cfosho[0] & 0x1f);	/* Pout - (2 * VGA_idx) */

	switch (lna_idx) {
	case 5:
		rssi -= 32;
		break;
	case 4:
		rssi -= 24;
		break;
	case 2:
		rssi -= 11;
		break;
	case 1:
		rssi += 5;
		break;
	case 0:
		rssi += 21;
		break;
	}

	return (rssi);
}