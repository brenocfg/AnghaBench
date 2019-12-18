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
struct hifn_softc {int sc_flags; int sc_ramsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  HIFN_0_PUCNFG ; 
 int HIFN_IS_7956 ; 
 int HIFN_PUCNFG_DRAMMASK ; 
 int READ_REG_0 (struct hifn_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hifn_dramsize(struct hifn_softc *sc)
{
	u_int32_t cnfg;

	if (sc->sc_flags & HIFN_IS_7956) {
		/*
		 * 7955/7956 have a fixed internal ram of only 32K.
		 */
		sc->sc_ramsize = 32768;
	} else {
		cnfg = READ_REG_0(sc, HIFN_0_PUCNFG) &
		    HIFN_PUCNFG_DRAMMASK;
		sc->sc_ramsize = 1 << ((cnfg >> 13) + 18);
	}
	return (0);
}