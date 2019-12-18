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
struct TYPE_2__ {scalar_t__ rbd_idx; } ;
struct bwi_ring_data {int /*<<< orphan*/  rdata_paddr; int /*<<< orphan*/  rdata_txrx_ctrl; int /*<<< orphan*/  rdata_dmap; } ;
struct bwi_softc {int /*<<< orphan*/  sc_rxring_dtag; int /*<<< orphan*/  sc_dev; TYPE_1__ sc_rx_bdata; struct bwi_ring_data sc_rx_rdata; } ;
struct bwi_rxbuf_hdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int BWI_RX_NDESC ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bwi_init_rxdesc_ring32 (struct bwi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int bwi_newbuf (struct bwi_softc*,int,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
bwi_init_rx_ring32(struct bwi_softc *sc)
{
	struct bwi_ring_data *rd = &sc->sc_rx_rdata;
	int i, error;

	sc->sc_rx_bdata.rbd_idx = 0;

	for (i = 0; i < BWI_RX_NDESC; ++i) {
		error = bwi_newbuf(sc, i, 1);
		if (error) {
			device_printf(sc->sc_dev,
				  "can't allocate %dth RX buffer\n", i);
			return error;
		}
	}
	bus_dmamap_sync(sc->sc_rxring_dtag, rd->rdata_dmap,
			BUS_DMASYNC_PREWRITE);

	bwi_init_rxdesc_ring32(sc, rd->rdata_txrx_ctrl, rd->rdata_paddr,
			       sizeof(struct bwi_rxbuf_hdr), BWI_RX_NDESC);
	return 0;
}