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
struct iwm_softc {int /*<<< orphan*/  sc_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWM_CSR_GP_CNTRL ; 
 int IWM_CSR_GP_CNTRL_REG_FLAG_HW_RF_KILL_SW ; 
 int /*<<< orphan*/  IWM_FLAG_RFKILL ; 
 int IWM_READ (struct iwm_softc*,int /*<<< orphan*/ ) ; 

int
iwm_check_rfkill(struct iwm_softc *sc)
{
	uint32_t v;
	int rv;

	/*
	 * "documentation" is not really helpful here:
	 *  27:	HW_RF_KILL_SW
	 *	Indicates state of (platform's) hardware RF-Kill switch
	 *
	 * But apparently when it's off, it's on ...
	 */
	v = IWM_READ(sc, IWM_CSR_GP_CNTRL);
	rv = (v & IWM_CSR_GP_CNTRL_REG_FLAG_HW_RF_KILL_SW) == 0;
	if (rv) {
		sc->sc_flags |= IWM_FLAG_RFKILL;
	} else {
		sc->sc_flags &= ~IWM_FLAG_RFKILL;
	}

	return rv;
}