#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  arge_rx_tag; struct arge_rxdesc* arge_rxdesc; } ;
struct arge_softc {TYPE_1__ arge_cdata; } ;
struct arge_rxdesc {int /*<<< orphan*/ * rx_m; int /*<<< orphan*/  rx_dmamap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARGE_LOCK_ASSERT (struct arge_softc*) ; 
 int ARGE_RX_RING_COUNT ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
arge_rx_ring_free(struct arge_softc *sc)
{
	int i;
	struct arge_rxdesc	*rxd;

	ARGE_LOCK_ASSERT(sc);

	for (i = 0; i < ARGE_RX_RING_COUNT; i++) {
		rxd = &sc->arge_cdata.arge_rxdesc[i];
		/* Unmap the mbuf */
		if (rxd->rx_m != NULL) {
			bus_dmamap_unload(sc->arge_cdata.arge_rx_tag,
			    rxd->rx_dmamap);
			m_free(rxd->rx_m);
			rxd->rx_m = NULL;
		}
	}
}