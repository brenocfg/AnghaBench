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
struct rtwn_softc {int sc_flags; } ;
struct r88e_rx_phystat {int agc_rpt; } ;
typedef  int int8_t ;

/* Variables and functions */
 int RTWN_FLAG_CCK_HIPWR ; 

int8_t
r88e_get_rssi_cck(struct rtwn_softc *sc, void *physt)
{
	struct r88e_rx_phystat *phy = (struct r88e_rx_phystat *)physt;
	int8_t lna_idx, vga_idx, rssi;

	lna_idx = (phy->agc_rpt & 0xe0) >> 5;
	vga_idx = (phy->agc_rpt & 0x1f);
	rssi = 6 - 2 * vga_idx;

	switch (lna_idx) {
	case 7:
		if (vga_idx > 27)
			rssi = -100 + 6;
		else
			rssi += -100 + 2 * 27;
		break;
	case 6:
		rssi += -48 + 2 * 2;
		break;
	case 5:
		rssi += -42 + 2 * 7;
		break;
	case 4:
		rssi += -36 + 2 * 7;
		break;
	case 3:
		rssi += -24 + 2 * 7;
		break;
	case 2:
		rssi += -6 + 2 * 5;
		if (sc->sc_flags & RTWN_FLAG_CCK_HIPWR)
			rssi -= 6;
		break;
	case 1:
		rssi += 8;
		break;
	case 0:
		rssi += 14;
		break;
	}

	return (rssi);
}