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
struct rtwn_softc {int nrxchains; struct r92c_softc* sc_priv; } ;
struct r92c_softc {int pa_setting; } ;

/* Variables and functions */
 int /*<<< orphan*/  R92C_RF_IPA ; 
 int /*<<< orphan*/  r92c_rf_write (struct rtwn_softc*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtwn_setbits_1 (struct rtwn_softc*,int,int,int) ; 

void
r92c_pa_bias_init(struct rtwn_softc *sc)
{
	struct r92c_softc *rs = sc->sc_priv;
	int i;

	for (i = 0; i < sc->nrxchains; i++) {
		if (rs->pa_setting & (1 << i))
			continue;
		r92c_rf_write(sc, i, R92C_RF_IPA, 0x0f406);
		r92c_rf_write(sc, i, R92C_RF_IPA, 0x4f406);
		r92c_rf_write(sc, i, R92C_RF_IPA, 0x8f406);
		r92c_rf_write(sc, i, R92C_RF_IPA, 0xcf406);
	}
	if (!(rs->pa_setting & 0x10))
		rtwn_setbits_1(sc, 0x16, 0xf0, 0x90);
}