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
struct xbd_softc {int /*<<< orphan*/  xbd_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  HYPERVISOR_yield () ; 
 int /*<<< orphan*/  RING_FINAL_CHECK_FOR_RESPONSES (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  XBD_Q_BUSY ; 
 int /*<<< orphan*/  xbd_int (struct xbd_softc*) ; 
 scalar_t__ xbd_queue_length (struct xbd_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xbd_quiesce(struct xbd_softc *sc)
{
	int mtd;

	// While there are outstanding requests
	while (xbd_queue_length(sc, XBD_Q_BUSY) != 0) {
		RING_FINAL_CHECK_FOR_RESPONSES(&sc->xbd_ring, mtd);
		if (mtd) {
			/* Received request completions, update queue. */
			xbd_int(sc);
		}
		if (xbd_queue_length(sc, XBD_Q_BUSY) != 0) {
			/*
			 * Still pending requests, wait for the disk i/o
			 * to complete.
			 */
			HYPERVISOR_yield();
		}
	}
}