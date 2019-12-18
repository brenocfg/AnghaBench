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
struct xbd_softc {int xbd_state; int /*<<< orphan*/  xbd_io_lock; int /*<<< orphan*/ * xbd_cm_q; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ EWOULDBLOCK ; 
 int /*<<< orphan*/  PRIBIO ; 
 size_t XBD_Q_BUSY ; 
 int XBD_STATE_SUSPENDED ; 
 struct xbd_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int hz ; 
 scalar_t__ msleep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ xbd_queue_length (struct xbd_softc*,size_t) ; 

__attribute__((used)) static int
xbd_suspend(device_t dev)
{
	struct xbd_softc *sc = device_get_softc(dev);
	int retval;
	int saved_state;

	/* Prevent new requests being issued until we fix things up. */
	mtx_lock(&sc->xbd_io_lock);
	saved_state = sc->xbd_state;
	sc->xbd_state = XBD_STATE_SUSPENDED;

	/* Wait for outstanding I/O to drain. */
	retval = 0;
	while (xbd_queue_length(sc, XBD_Q_BUSY) != 0) {
		if (msleep(&sc->xbd_cm_q[XBD_Q_BUSY], &sc->xbd_io_lock,
		    PRIBIO, "blkf_susp", 30 * hz) == EWOULDBLOCK) {
			retval = EBUSY;
			break;
		}
	}
	mtx_unlock(&sc->xbd_io_lock);

	if (retval != 0)
		sc->xbd_state = saved_state;

	return (retval);
}