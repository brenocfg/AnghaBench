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
struct dtsec_softc {scalar_t__ sc_mode; int /*<<< orphan*/  sc_lock; int /*<<< orphan*/ * sc_ifnet; } ;
typedef  int /*<<< orphan*/ * if_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DTSEC_LOCK (struct dtsec_softc*) ; 
 scalar_t__ DTSEC_MODE_REGULAR ; 
 int /*<<< orphan*/  DTSEC_UNLOCK (struct dtsec_softc*) ; 
 struct dtsec_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_is_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtsec_fm_mac_free (struct dtsec_softc*) ; 
 int /*<<< orphan*/  dtsec_fm_port_free_both (struct dtsec_softc*) ; 
 int /*<<< orphan*/  dtsec_if_deinit_locked (struct dtsec_softc*) ; 
 int /*<<< orphan*/  dtsec_rm_fi_pool_free (struct dtsec_softc*) ; 
 int /*<<< orphan*/  dtsec_rm_fqr_rx_free (struct dtsec_softc*) ; 
 int /*<<< orphan*/  dtsec_rm_fqr_tx_free (struct dtsec_softc*) ; 
 int /*<<< orphan*/  dtsec_rm_pool_rx_free (struct dtsec_softc*) ; 
 int /*<<< orphan*/  ether_ifdetach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  if_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 

int
dtsec_detach(device_t dev)
{
	struct dtsec_softc *sc;
	if_t ifp;

	sc = device_get_softc(dev);
	ifp = sc->sc_ifnet;

	if (device_is_attached(dev)) {
		ether_ifdetach(ifp);
		/* Shutdown interface */
		DTSEC_LOCK(sc);
		dtsec_if_deinit_locked(sc);
		DTSEC_UNLOCK(sc);
	}

	if (sc->sc_ifnet) {
		if_free(sc->sc_ifnet);
		sc->sc_ifnet = NULL;
	}

	if (sc->sc_mode == DTSEC_MODE_REGULAR) {
		/* Free RX/TX FQRs */
		dtsec_rm_fqr_rx_free(sc);
		dtsec_rm_fqr_tx_free(sc);

		/* Free frame info pool */
		dtsec_rm_fi_pool_free(sc);

		/* Free RX buffer pool */
		dtsec_rm_pool_rx_free(sc);
	}

	dtsec_fm_mac_free(sc);
	dtsec_fm_port_free_both(sc);

	/* Destroy lock */
	mtx_destroy(&sc->sc_lock);

	return (0);
}