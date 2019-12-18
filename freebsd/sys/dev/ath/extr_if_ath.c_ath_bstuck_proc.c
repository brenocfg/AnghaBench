#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  ast_bstuck; } ;
struct ath_softc {scalar_t__ sc_bmisscount; TYPE_1__ sc_stats; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_alq; int /*<<< orphan*/  sc_ah; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH_ALQ_STUCK_BEACON ; 
 int /*<<< orphan*/  ATH_RESET_NOLOSS ; 
 scalar_t__ ath_hal_gethangstate (int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int /*<<< orphan*/  ath_reset (struct ath_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ if_ath_alq_checkdebug (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_ath_alq_post (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ath_bstuck_proc(void *arg, int pending)
{
	struct ath_softc *sc = arg;
	uint32_t hangs = 0;

	if (ath_hal_gethangstate(sc->sc_ah, 0xff, &hangs) && hangs != 0)
		device_printf(sc->sc_dev, "bb hang detected (0x%x)\n", hangs);

#ifdef	ATH_DEBUG_ALQ
	if (if_ath_alq_checkdebug(&sc->sc_alq, ATH_ALQ_STUCK_BEACON))
		if_ath_alq_post(&sc->sc_alq, ATH_ALQ_STUCK_BEACON, 0, NULL);
#endif

	device_printf(sc->sc_dev, "stuck beacon; resetting (bmiss count %u)\n",
	    sc->sc_bmisscount);
	sc->sc_stats.ast_bstuck++;
	/*
	 * This assumes that there's no simultaneous channel mode change
	 * occurring.
	 */
	ath_reset(sc, ATH_RESET_NOLOSS);
}