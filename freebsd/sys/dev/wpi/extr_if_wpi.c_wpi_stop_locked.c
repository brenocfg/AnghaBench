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
struct wpi_softc {scalar_t__ sc_running; int /*<<< orphan*/  calib_to; int /*<<< orphan*/  scan_timeout; int /*<<< orphan*/  tx_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  WPI_LOCK_ASSERT (struct wpi_softc*) ; 
 int /*<<< orphan*/  WPI_RXON_LOCK (struct wpi_softc*) ; 
 int /*<<< orphan*/  WPI_RXON_UNLOCK (struct wpi_softc*) ; 
 int /*<<< orphan*/  WPI_TXQ_LOCK (struct wpi_softc*) ; 
 int /*<<< orphan*/  WPI_TXQ_STATE_LOCK (struct wpi_softc*) ; 
 int /*<<< orphan*/  WPI_TXQ_STATE_UNLOCK (struct wpi_softc*) ; 
 int /*<<< orphan*/  WPI_TXQ_UNLOCK (struct wpi_softc*) ; 
 int /*<<< orphan*/  WPI_TX_LOCK (struct wpi_softc*) ; 
 int /*<<< orphan*/  WPI_TX_UNLOCK (struct wpi_softc*) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpi_hw_stop (struct wpi_softc*) ; 

__attribute__((used)) static void
wpi_stop_locked(struct wpi_softc *sc)
{

	WPI_LOCK_ASSERT(sc);

	if (sc->sc_running == 0)
		return;

	WPI_TX_LOCK(sc);
	WPI_TXQ_LOCK(sc);
	sc->sc_running = 0;
	WPI_TXQ_UNLOCK(sc);
	WPI_TX_UNLOCK(sc);

	WPI_TXQ_STATE_LOCK(sc);
	callout_stop(&sc->tx_timeout);
	WPI_TXQ_STATE_UNLOCK(sc);

	WPI_RXON_LOCK(sc);
	callout_stop(&sc->scan_timeout);
	callout_stop(&sc->calib_to);
	WPI_RXON_UNLOCK(sc);

	/* Power OFF hardware. */
	wpi_hw_stop(sc);
}