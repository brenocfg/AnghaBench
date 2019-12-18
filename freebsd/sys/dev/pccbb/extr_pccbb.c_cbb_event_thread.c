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
struct cbb_softc {int flags; int /*<<< orphan*/  mtx; int /*<<< orphan*/  dev; int /*<<< orphan*/  intrhand; int /*<<< orphan*/ * sc_root_token; } ;

/* Variables and functions */
 int /*<<< orphan*/  CBB_CARD_PRESENT (int) ; 
 int CBB_FORCE_CV_TEST ; 
 int CBB_KTHREAD_DONE ; 
 int CBB_KTHREAD_RUNNING ; 
 int /*<<< orphan*/  CBB_SOCKET_FORCE ; 
 int /*<<< orphan*/  CBB_SOCKET_MASK ; 
 int CBB_SOCKET_MASK_CD ; 
 int CBB_SOCKET_MASK_CSTS ; 
 int /*<<< orphan*/  CBB_SOCKET_STATE ; 
 int CBB_STATE_NOT_A_CARD ; 
 int /*<<< orphan*/  DEVPRINTF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int EWOULDBLOCK ; 
 int cbb_get (struct cbb_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cbb_insert (struct cbb_softc*) ; 
 int /*<<< orphan*/  cbb_removal (struct cbb_softc*) ; 
 int /*<<< orphan*/  cbb_setb (struct cbb_softc*,int /*<<< orphan*/ ,int) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int hz ; 
 int /*<<< orphan*/  kproc_exit (int /*<<< orphan*/ ) ; 
 int msleep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pause (char*,int) ; 
 int /*<<< orphan*/  root_mount_rel (int /*<<< orphan*/ *) ; 

void
cbb_event_thread(void *arg)
{
	struct cbb_softc *sc = arg;
	uint32_t status;
	int err;
	int not_a_card = 0;

	/*
	 * We need to act as a power sequencer on startup.  Delay 2s/channel
	 * to ensure the other channels have had a chance to come up.  We likely
	 * should add a lock that's shared on a per-slot basis so that only
	 * one power event can happen per slot at a time.
	 */
	pause("cbbstart", hz * device_get_unit(sc->dev) * 2);
	mtx_lock(&sc->mtx);
	sc->flags |= CBB_KTHREAD_RUNNING;
	while ((sc->flags & CBB_KTHREAD_DONE) == 0) {
		mtx_unlock(&sc->mtx);
		status = cbb_get(sc, CBB_SOCKET_STATE);
		DPRINTF(("Status is 0x%x\n", status));
		if (!CBB_CARD_PRESENT(status)) {
			not_a_card = 0;		/* We know card type */
			cbb_removal(sc);
		} else if (status & CBB_STATE_NOT_A_CARD) {
			/*
			 * Up to 10 times, try to rescan the card when we see
			 * NOT_A_CARD.  10 is somehwat arbitrary.  When this
			 * pathology hits, there's a ~40% chance each try will
			 * fail.  10 tries takes about 5s and results in a
			 * 99.99% certainty of the results.
			 */
			if (not_a_card++ < 10) {
				DEVPRINTF((sc->dev,
				    "Not a card bit set, rescanning\n"));
				cbb_setb(sc, CBB_SOCKET_FORCE, CBB_FORCE_CV_TEST);
			} else {
				device_printf(sc->dev,
				    "Can't determine card type\n");
			}
		} else {
			not_a_card = 0;		/* We know card type */
			cbb_insert(sc);
		}

		/*
		 * First time through we need to tell mountroot that we're
		 * done.
		 */
		if (sc->sc_root_token) {
			root_mount_rel(sc->sc_root_token);
			sc->sc_root_token = NULL;
		}

		/*
		 * Wait until it has been 250ms since the last time we
		 * get an interrupt.  We handle the rest of the interrupt
		 * at the top of the loop.  Although we clear the bit in the
		 * ISR, we signal sc->cv from the detach path after we've
		 * set the CBB_KTHREAD_DONE bit, so we can't do a simple
		 * 250ms sleep here.
		 *
		 * In our ISR, we turn off the card changed interrupt.  Turn
		 * them back on here before we wait for them to happen.  We
		 * turn them on/off so that we can tolerate a large latency
		 * between the time we signal cbb_event_thread and it gets
		 * a chance to run.
		 */
		mtx_lock(&sc->mtx);
		cbb_setb(sc, CBB_SOCKET_MASK, CBB_SOCKET_MASK_CD | CBB_SOCKET_MASK_CSTS);
		msleep(&sc->intrhand, &sc->mtx, 0, "-", 0);
		err = 0;
		while (err != EWOULDBLOCK &&
		    (sc->flags & CBB_KTHREAD_DONE) == 0)
			err = msleep(&sc->intrhand, &sc->mtx, 0, "-", hz / 5);
	}
	DEVPRINTF((sc->dev, "Thread terminating\n"));
	sc->flags &= ~CBB_KTHREAD_RUNNING;
	mtx_unlock(&sc->mtx);
	kproc_exit(0);
}