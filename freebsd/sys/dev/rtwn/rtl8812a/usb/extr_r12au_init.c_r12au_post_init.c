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
struct rtwn_softc {int sc_flags; scalar_t__ sc_ratectl_sysctl; scalar_t__ sc_ratectl; } ;

/* Variables and functions */
 scalar_t__ R12A_EARLY_MODE_CONTROL ; 
 scalar_t__ R12A_SDIO_CTRL ; 
 scalar_t__ R92C_ACLK_MON ; 
 int /*<<< orphan*/  R92C_QUEUE_CTRL ; 
 scalar_t__ R92C_USB_HRPWM ; 
 int RTWN_FW_LOADED ; 
 scalar_t__ RTWN_RATECTL_FW ; 
 scalar_t__ RTWN_RATECTL_NET80211 ; 
 scalar_t__ RTWN_RATECTL_NONE ; 
 int /*<<< orphan*/  rtwn_setbits_1 (struct rtwn_softc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtwn_write_1 (struct rtwn_softc*,scalar_t__,int) ; 

void
r12au_post_init(struct rtwn_softc *sc)
{

	/* Setup RTS BW (equal to data BW). */
	rtwn_setbits_1(sc, R92C_QUEUE_CTRL, 0x08, 0);

	rtwn_write_1(sc, R12A_EARLY_MODE_CONTROL + 3, 0x01);

	/* Reset USB mode switch setting. */
	rtwn_write_1(sc, R12A_SDIO_CTRL, 0);
	rtwn_write_1(sc, R92C_ACLK_MON, 0);

	rtwn_write_1(sc, R92C_USB_HRPWM, 0);

#ifndef RTWN_WITHOUT_UCODE
	if (sc->sc_flags & RTWN_FW_LOADED) {
		if (sc->sc_ratectl_sysctl == RTWN_RATECTL_FW) {
			/* TODO: implement */
			sc->sc_ratectl = RTWN_RATECTL_NET80211;
		} else
			sc->sc_ratectl = sc->sc_ratectl_sysctl;
	} else
#endif
		sc->sc_ratectl = RTWN_RATECTL_NONE;
}