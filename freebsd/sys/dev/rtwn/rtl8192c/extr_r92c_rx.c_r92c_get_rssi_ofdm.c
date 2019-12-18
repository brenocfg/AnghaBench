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
struct r92c_rx_phystat {int pwdb_all; } ;
typedef  int int8_t ;

/* Variables and functions */

int8_t
r92c_get_rssi_ofdm(struct rtwn_softc *sc, void *physt)
{
	struct r92c_rx_phystat *phy = (struct r92c_rx_phystat *)physt;
	int rssi;

	/* Get average RSSI. */
	rssi = ((phy->pwdb_all >> 1) & 0x7f) - 110;

	return (rssi);
}