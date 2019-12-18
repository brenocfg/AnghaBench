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
typedef  int u_int32_t ;
struct hifn_softc {int sc_flags; int sc_maxses; int sc_ramsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  HIFN_0_PUCNFG ; 
 int HIFN_IS_7956 ; 
 int HIFN_PUCNFG_COMPSING ; 
 int HIFN_PUCNFG_ENCCNFG ; 
 int READ_REG_0 (struct hifn_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
hifn_sessions(struct hifn_softc *sc)
{
	u_int32_t pucnfg;
	int ctxsize;

	pucnfg = READ_REG_0(sc, HIFN_0_PUCNFG);

	if (pucnfg & HIFN_PUCNFG_COMPSING) {
		if (pucnfg & HIFN_PUCNFG_ENCCNFG)
			ctxsize = 128;
		else
			ctxsize = 512;
		/*
		 * 7955/7956 has internal context memory of 32K
		 */
		if (sc->sc_flags & HIFN_IS_7956)
			sc->sc_maxses = 32768 / ctxsize;
		else
			sc->sc_maxses = 1 +
			    ((sc->sc_ramsize - 32768) / ctxsize);
	} else
		sc->sc_maxses = sc->sc_ramsize / 16384;

	if (sc->sc_maxses > 2048)
		sc->sc_maxses = 2048;
}