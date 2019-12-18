#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tsec_softc {TYPE_1__* tsec_ifp; int /*<<< orphan*/  dev; scalar_t__ sc_rres; } ;
struct TYPE_4__ {int if_capenable; } ;

/* Variables and functions */
 int IFCAP_POLLING ; 
 int /*<<< orphan*/  ether_ifdetach (TYPE_1__*) ; 
 int /*<<< orphan*/  ether_poll_deregister (TYPE_1__*) ; 
 int /*<<< orphan*/  if_free (TYPE_1__*) ; 
 int /*<<< orphan*/  tsec_free_dma (struct tsec_softc*) ; 
 int /*<<< orphan*/  tsec_shutdown (int /*<<< orphan*/ ) ; 

int
tsec_detach(struct tsec_softc *sc)
{

	if (sc->tsec_ifp != NULL) {
#ifdef DEVICE_POLLING
		if (sc->tsec_ifp->if_capenable & IFCAP_POLLING)
			ether_poll_deregister(sc->tsec_ifp);
#endif

		/* Stop TSEC controller and free TX queue */
		if (sc->sc_rres)
			tsec_shutdown(sc->dev);

		/* Detach network interface */
		ether_ifdetach(sc->tsec_ifp);
		if_free(sc->tsec_ifp);
		sc->tsec_ifp = NULL;
	}

	/* Free DMA resources */
	tsec_free_dma(sc);

	return (0);
}