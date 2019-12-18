#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* width; scalar_t__ offset; scalar_t__ period; } ;
struct TYPE_3__ {void* width; scalar_t__ offset; scalar_t__ period; } ;
struct ncr53c9x_tinfo {int flags; TYPE_2__ curr; TYPE_1__ goal; int /*<<< orphan*/  luns; } ;
struct ncr53c9x_softc {scalar_t__ sc_state; int sc_ntarg; scalar_t__ sc_minsync; int sc_cfflags; struct ncr53c9x_tinfo* sc_tinfo; int /*<<< orphan*/  sc_prevphase; int /*<<< orphan*/  sc_phase; scalar_t__ sc_msgoutq; scalar_t__ sc_msgout; scalar_t__ sc_msgpriq; scalar_t__ sc_flags; int /*<<< orphan*/ * sc_nexus; int /*<<< orphan*/  ready_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_CMD_TIMEOUT ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  INVALID_PHASE ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 void* MSG_EXT_WDTR_BUS_8_BIT ; 
 int /*<<< orphan*/  NCRCMD (struct ncr53c9x_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NCRCMD_RSTSCSI ; 
 scalar_t__ NCR_IDLE ; 
 int /*<<< orphan*/  NCR_LOCK_ASSERT (struct ncr53c9x_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NCR_MISC (char*) ; 
 scalar_t__ NCR_SBR ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int T_RSELECTOFF ; 
 int T_SDTRSENT ; 
 int T_SYNCHOFF ; 
 int T_WDTRSENT ; 
 int /*<<< orphan*/  memset (struct ncr53c9x_tinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ncr53c9x_clear (struct ncr53c9x_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ncr53c9x_reset (struct ncr53c9x_softc*) ; 
 int /*<<< orphan*/  ncr53c9x_sched (struct ncr53c9x_softc*) ; 

__attribute__((used)) static void
ncr53c9x_init(struct ncr53c9x_softc *sc, int doreset)
{
	struct ncr53c9x_tinfo *ti;
	int r;

	NCR_LOCK_ASSERT(sc, MA_OWNED);

	NCR_MISC(("[NCR_INIT(%d) %d] ", doreset, sc->sc_state));

	if (sc->sc_state == 0) {
		/* First time through; initialize. */

		TAILQ_INIT(&sc->ready_list);
		sc->sc_nexus = NULL;
		memset(sc->sc_tinfo, 0, sizeof(*sc->sc_tinfo));
		for (r = 0; r < sc->sc_ntarg; r++) {
			LIST_INIT(&sc->sc_tinfo[r].luns);
		}
	} else
		ncr53c9x_clear(sc, CAM_CMD_TIMEOUT);

	/*
	 * Reset the chip to a known state.
	 */
	ncr53c9x_reset(sc);

	sc->sc_flags = 0;
	sc->sc_msgpriq = sc->sc_msgout = sc->sc_msgoutq = 0;
	sc->sc_phase = sc->sc_prevphase = INVALID_PHASE;

	/*
	 * If we're the first time through, set the default parameters
	 * for all targets.  Otherwise we only clear their current transfer
	 * settings so we'll renegotiate their goal settings with the next
	 * command.
	 */
	if (sc->sc_state == 0) {
		for (r = 0; r < sc->sc_ntarg; r++) {
			ti = &sc->sc_tinfo[r];
/* XXX - config flags per target: low bits: no reselect; high bits: no synch */

			ti->flags = ((sc->sc_minsync != 0 &&
			    (sc->sc_cfflags & (1 << ((r & 7) + 8))) == 0) ?
			    0 : T_SYNCHOFF) |
			    ((sc->sc_cfflags & (1 << (r & 7))) == 0 ?
			    0 : T_RSELECTOFF);
			ti->curr.period = ti->goal.period = 0;
			ti->curr.offset = ti->goal.offset = 0;
			ti->curr.width = ti->goal.width =
			    MSG_EXT_WDTR_BUS_8_BIT;
		}
	} else {
		for (r = 0; r < sc->sc_ntarg; r++) {
			ti = &sc->sc_tinfo[r];
			ti->flags &= ~(T_SDTRSENT | T_WDTRSENT);
			ti->curr.period = 0;
			ti->curr.offset = 0;
			ti->curr.width = MSG_EXT_WDTR_BUS_8_BIT;
		}
	}

	if (doreset) {
		sc->sc_state = NCR_SBR;
		NCRCMD(sc, NCRCMD_RSTSCSI);
		/* Give the bus a fighting chance to settle. */
		DELAY(250000);
	} else {
		sc->sc_state = NCR_IDLE;
		ncr53c9x_sched(sc);
	}
}