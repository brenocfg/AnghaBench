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
struct usie_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_if_sync_ch; } ;

/* Variables and functions */
 int /*<<< orphan*/  USIE_HIP_SYNC2M ; 
 int hz ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct usie_softc*) ; 
 int /*<<< orphan*/  usie_if_cmd (struct usie_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usie_if_sync_to ; 

__attribute__((used)) static void
usie_if_sync_cb(void *arg, int pending)
{
	struct usie_softc *sc = arg;

	mtx_lock(&sc->sc_mtx);

	/* call twice */
	usie_if_cmd(sc, USIE_HIP_SYNC2M);
	usie_if_cmd(sc, USIE_HIP_SYNC2M);

	usb_callout_reset(&sc->sc_if_sync_ch, 2 * hz, usie_if_sync_to, sc);

	mtx_unlock(&sc->sc_mtx);
}