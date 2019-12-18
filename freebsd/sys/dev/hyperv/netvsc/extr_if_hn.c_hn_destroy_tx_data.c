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
struct hn_softc {int hn_flags; int hn_tx_ring_cnt; scalar_t__ hn_tx_ring_inuse; int /*<<< orphan*/ * hn_tx_ring; int /*<<< orphan*/ * hn_chim; int /*<<< orphan*/  hn_dev; int /*<<< orphan*/  hn_chim_dma; } ;

/* Variables and functions */
 int HN_FLAG_CHIM_REF ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hn_tx_ring_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hyperv_dmamem_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
hn_destroy_tx_data(struct hn_softc *sc)
{
	int i;

	if (sc->hn_chim != NULL) {
		if ((sc->hn_flags & HN_FLAG_CHIM_REF) == 0) {
			hyperv_dmamem_free(&sc->hn_chim_dma, sc->hn_chim);
		} else {
			device_printf(sc->hn_dev,
			    "chimney sending buffer is referenced");
		}
		sc->hn_chim = NULL;
	}

	if (sc->hn_tx_ring_cnt == 0)
		return;

	for (i = 0; i < sc->hn_tx_ring_cnt; ++i)
		hn_tx_ring_destroy(&sc->hn_tx_ring[i]);

	free(sc->hn_tx_ring, M_DEVBUF);
	sc->hn_tx_ring = NULL;

	sc->hn_tx_ring_cnt = 0;
	sc->hn_tx_ring_inuse = 0;
}