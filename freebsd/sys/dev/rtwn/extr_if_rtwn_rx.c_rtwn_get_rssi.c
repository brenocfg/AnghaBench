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
typedef  int /*<<< orphan*/  int8_t ;

/* Variables and functions */
 int /*<<< orphan*/  rtwn_get_rssi_cck (struct rtwn_softc*,void*) ; 
 int /*<<< orphan*/  rtwn_get_rssi_ofdm (struct rtwn_softc*,void*) ; 

__attribute__((used)) static int8_t
rtwn_get_rssi(struct rtwn_softc *sc, void *physt, int is_cck)
{
	int8_t rssi;

	if (is_cck)
		rssi = rtwn_get_rssi_cck(sc, physt);
	else	/* OFDM/HT. */
		rssi = rtwn_get_rssi_ofdm(sc, physt);

	return (rssi);
}