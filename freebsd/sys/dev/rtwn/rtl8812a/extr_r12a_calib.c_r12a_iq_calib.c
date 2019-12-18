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

/* Variables and functions */
 int RTWN_FW_LOADED ; 
 int /*<<< orphan*/  r12a_iq_calib_fw (struct rtwn_softc*) ; 
 scalar_t__ rtwn_r12a_iq_calib_fw_supported (struct rtwn_softc*) ; 
 int /*<<< orphan*/  rtwn_r12a_iq_calib_sw (struct rtwn_softc*) ; 

void
r12a_iq_calib(struct rtwn_softc *sc)
{
#ifndef RTWN_WITHOUT_UCODE
	if ((sc->sc_flags & RTWN_FW_LOADED) &&
	    rtwn_r12a_iq_calib_fw_supported(sc))
		r12a_iq_calib_fw(sc);
	else
#endif
		rtwn_r12a_iq_calib_sw(sc);
}