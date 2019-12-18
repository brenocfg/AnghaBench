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
struct pps_softc {int /*<<< orphan*/  pps_mtx; int /*<<< orphan*/  pps_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  PPS_CAPTUREASSERT ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pps_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gpiopps_ithrd(void *arg)
{
	struct pps_softc *sc = arg;

	/*
	 * Go create a pps event from the data captured in the filter handler.
	 *
	 * Note that we DO need locking here, unlike the case with the filter
	 * handler.  The pps_event() routine updates the non-capture part of the
	 * pps_state structure, and the ioctl() code could be accessing that
	 * data right now in a non-interrupt context, so we need an interlock.
	 */
	mtx_lock(&sc->pps_mtx);
	pps_event(&sc->pps_state, PPS_CAPTUREASSERT);
	mtx_unlock(&sc->pps_mtx);
}