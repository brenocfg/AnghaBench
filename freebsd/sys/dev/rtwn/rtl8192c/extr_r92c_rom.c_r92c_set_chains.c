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
struct rtwn_softc {int ntxchains; int nrxchains; struct r92c_softc* sc_priv; } ;
struct r92c_softc {int chip; } ;

/* Variables and functions */
 int R92C_CHIP_92C ; 
 int R92C_CHIP_92C_1T2R ; 

__attribute__((used)) static void
r92c_set_chains(struct rtwn_softc *sc)
{
	struct r92c_softc *rs = sc->sc_priv;

	if (rs->chip & R92C_CHIP_92C) {
		sc->ntxchains = (rs->chip & R92C_CHIP_92C_1T2R) ? 1 : 2;
		sc->nrxchains = 2;
	} else {
		sc->ntxchains = 1;
		sc->nrxchains = 1;
	}
}