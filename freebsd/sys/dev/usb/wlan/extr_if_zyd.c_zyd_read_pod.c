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
typedef  int uint32_t ;
struct zyd_softc {int sc_rfrev; int sc_ledtype; int sc_al2230s; int sc_cckgain; int sc_fix_cr157; int sc_parev; int sc_bandedge6; int sc_newphy; int sc_txled; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZYD_EEPROM_POD ; 
 int /*<<< orphan*/  zyd_read32_m (struct zyd_softc*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
zyd_read_pod(struct zyd_softc *sc)
{
	int error;
	uint32_t tmp;

	zyd_read32_m(sc, ZYD_EEPROM_POD, &tmp);
	sc->sc_rfrev     = tmp & 0x0f;
	sc->sc_ledtype   = (tmp >>  4) & 0x01;
	sc->sc_al2230s   = (tmp >>  7) & 0x01;
	sc->sc_cckgain   = (tmp >>  8) & 0x01;
	sc->sc_fix_cr157 = (tmp >> 13) & 0x01;
	sc->sc_parev     = (tmp >> 16) & 0x0f;
	sc->sc_bandedge6 = (tmp >> 21) & 0x01;
	sc->sc_newphy    = (tmp >> 31) & 0x01;
	sc->sc_txled     = ((tmp & (1 << 24)) && (tmp & (1 << 29))) ? 0 : 1;
fail:
	return (error);
}