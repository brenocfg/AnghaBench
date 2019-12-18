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
struct uath_softc {scalar_t__ sc_tx_timer; int /*<<< orphan*/  watchdog_ch; int /*<<< orphan*/  stat_ch; int /*<<< orphan*/  sc_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  UATH_ASSERT_LOCKED (struct uath_softc*) ; 
 int /*<<< orphan*/  UATH_FLAG_INITDONE ; 
 int /*<<< orphan*/  WDCMSG_TARGET_STOP ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uath_abort_xfers (struct uath_softc*) ; 
 int /*<<< orphan*/  uath_cmd_write (struct uath_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uath_flush (struct uath_softc*) ; 
 int /*<<< orphan*/  uath_set_ledstate (struct uath_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
uath_stop(struct uath_softc *sc)
{

	UATH_ASSERT_LOCKED(sc);

	sc->sc_flags &= ~UATH_FLAG_INITDONE;

	callout_stop(&sc->stat_ch);
	callout_stop(&sc->watchdog_ch);
	sc->sc_tx_timer = 0;
	/* abort pending transmits  */
	uath_abort_xfers(sc);
	/* flush data & control requests into the target  */
	(void)uath_flush(sc);
	/* set a LED status to the disconnected.  */
	uath_set_ledstate(sc, 0);
	/* stop the target  */
	uath_cmd_write(sc, WDCMSG_TARGET_STOP, NULL, 0, 0);
}