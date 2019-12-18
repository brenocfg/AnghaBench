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
struct xbd_softc {scalar_t__ xbd_state; scalar_t__ xbd_qfrozen_cnt; int /*<<< orphan*/  xbd_ring; int /*<<< orphan*/  xbd_io_lock; } ;
struct xbd_command {int cm_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  RING_FULL (int /*<<< orphan*/ *) ; 
 int XBDCF_Q_FREEZE ; 
 int /*<<< orphan*/  XBD_Q_READY ; 
 scalar_t__ XBD_STATE_CONNECTED ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 struct xbd_command* xbd_bio_command (struct xbd_softc*) ; 
 int /*<<< orphan*/  xbd_cm_freeze (struct xbd_softc*,struct xbd_command*,int) ; 
 struct xbd_command* xbd_dequeue_cm (struct xbd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xbd_flush_requests (struct xbd_softc*) ; 
 int xbd_queue_request (struct xbd_softc*,struct xbd_command*) ; 

__attribute__((used)) static void
xbd_startio(struct xbd_softc *sc)
{
	struct xbd_command *cm;
	int error, queued = 0;

	mtx_assert(&sc->xbd_io_lock, MA_OWNED);

	if (sc->xbd_state != XBD_STATE_CONNECTED)
		return;

	while (!RING_FULL(&sc->xbd_ring)) {

		if (sc->xbd_qfrozen_cnt != 0)
			break;

		cm = xbd_dequeue_cm(sc, XBD_Q_READY);

		if (cm == NULL)
		    cm = xbd_bio_command(sc);

		if (cm == NULL)
			break;

		if ((cm->cm_flags & XBDCF_Q_FREEZE) != 0) {
			/*
			 * Single step command.  Future work is
			 * held off until this command completes.
			 */
			xbd_cm_freeze(sc, cm, XBDCF_Q_FREEZE);
		}

		if ((error = xbd_queue_request(sc, cm)) != 0) {
			printf("xbd_queue_request returned %d\n", error);
			break;
		}
		queued++;
	}

	if (queued != 0) 
		xbd_flush_requests(sc);
}