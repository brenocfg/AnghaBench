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
struct rtwn_softc {int sc_flags; scalar_t__ sc_ratectl_sysctl; scalar_t__ sc_ratectl; struct r92c_softc* sc_priv; } ;
struct r92c_softc {int /*<<< orphan*/  rs_c2h_timeout; int /*<<< orphan*/  rs_c2h_report; } ;

/* Variables and functions */
 int /*<<< orphan*/  R92C_POWER_STATUS ; 
 int RTWN_FW_LOADED ; 
 scalar_t__ RTWN_RATECTL_FW ; 
 scalar_t__ RTWN_RATECTL_NET80211 ; 
 scalar_t__ RTWN_RATECTL_NONE ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rtwn_softc*) ; 
 int /*<<< orphan*/  r92c_handle_c2h_report ; 
 int /*<<< orphan*/  r92c_iq_calib (struct rtwn_softc*) ; 
 int /*<<< orphan*/  r92c_lc_calib (struct rtwn_softc*) ; 
 int /*<<< orphan*/  r92c_pa_bias_init (struct rtwn_softc*) ; 
 int /*<<< orphan*/  rtwn_write_1 (struct rtwn_softc*,int,int) ; 
 int /*<<< orphan*/  rtwn_write_4 (struct rtwn_softc*,int /*<<< orphan*/ ,int) ; 

void
r92cu_post_init(struct rtwn_softc *sc)
{

	rtwn_write_4(sc, R92C_POWER_STATUS, 0x5);

	/* Perform LO and IQ calibrations. */
	r92c_iq_calib(sc);
	/* Perform LC calibration. */
	r92c_lc_calib(sc);

	/* Fix USB interference issue. */
	rtwn_write_1(sc, 0xfe40, 0xe0);
	rtwn_write_1(sc, 0xfe41, 0x8d);
	rtwn_write_1(sc, 0xfe42, 0x80);

	r92c_pa_bias_init(sc);

	/* Fix for lower temperature. */
	rtwn_write_1(sc, 0x15, 0xe9);

#ifndef RTWN_WITHOUT_UCODE
	if (sc->sc_flags & RTWN_FW_LOADED) {
		struct r92c_softc *rs = sc->sc_priv;

		if (sc->sc_ratectl_sysctl == RTWN_RATECTL_FW) {
			/* XXX firmware RA does not work yet */
			sc->sc_ratectl = RTWN_RATECTL_NET80211;
		} else
			sc->sc_ratectl = sc->sc_ratectl_sysctl;

		/* Start C2H event handling. */
		callout_reset(&rs->rs_c2h_report, rs->rs_c2h_timeout,
		    r92c_handle_c2h_report, sc);
	} else
#endif
		sc->sc_ratectl = RTWN_RATECTL_NONE;
}