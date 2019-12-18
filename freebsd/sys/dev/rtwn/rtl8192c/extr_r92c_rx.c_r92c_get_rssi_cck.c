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
typedef  size_t uint8_t ;
struct rtwn_softc {int sc_flags; } ;
struct r92c_rx_cck {int agc_rpt; } ;
typedef  int int8_t ;

/* Variables and functions */
 int RTWN_FLAG_CCK_HIPWR ; 

int8_t
r92c_get_rssi_cck(struct rtwn_softc *sc, void *physt)
{
	static const int8_t cckoff[] = { 16, -12, -26, -46 };
	struct r92c_rx_cck *cck = (struct r92c_rx_cck *)physt;
	uint8_t rpt;
	int8_t rssi;

	if (sc->sc_flags & RTWN_FLAG_CCK_HIPWR) {
		rpt = (cck->agc_rpt >> 5) & 0x03;
		rssi = (cck->agc_rpt & 0x1f) << 1;
	} else {
		rpt = (cck->agc_rpt >> 6) & 0x03;
		rssi = cck->agc_rpt & 0x3e;
	}
	rssi = cckoff[rpt] - rssi;

	return (rssi);
}