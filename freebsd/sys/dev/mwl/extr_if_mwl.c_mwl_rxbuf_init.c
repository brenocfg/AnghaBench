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
struct TYPE_2__ {int /*<<< orphan*/  mst_rxbuf_failed; } ;
struct mwl_softc {TYPE_1__ sc_stats; } ;
struct mwl_rxdesc {int /*<<< orphan*/  RxControl; int /*<<< orphan*/  pPhysBuffData; scalar_t__ SQ2; int /*<<< orphan*/  PktLen; scalar_t__ Channel; int /*<<< orphan*/  Status; scalar_t__ RSSI; scalar_t__ QosCtrl; } ;
struct mwl_rxbuf {int /*<<< orphan*/ * bf_data; struct mwl_rxdesc* bf_desc; } ;

/* Variables and functions */
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  EAGLE_RXD_CTRL_DRIVER_OWN ; 
 int /*<<< orphan*/  EAGLE_RXD_CTRL_OS_OWN ; 
 int /*<<< orphan*/  EAGLE_RXD_STATUS_IDLE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MWL_AGGR_SIZE ; 
 int /*<<< orphan*/  MWL_JUMBO_DMA_ADDR (struct mwl_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MWL_RXDESC_SYNC (struct mwl_softc*,struct mwl_rxdesc*,int) ; 
 int /*<<< orphan*/  htole16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htole32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mwl_getrxdma (struct mwl_softc*) ; 

__attribute__((used)) static int
mwl_rxbuf_init(struct mwl_softc *sc, struct mwl_rxbuf *bf)
{
	struct mwl_rxdesc *ds;

	ds = bf->bf_desc;
	if (bf->bf_data == NULL) {
		bf->bf_data = mwl_getrxdma(sc);
		if (bf->bf_data == NULL) {
			/* mark descriptor to be skipped */
			ds->RxControl = EAGLE_RXD_CTRL_OS_OWN;
			/* NB: don't need PREREAD */
			MWL_RXDESC_SYNC(sc, ds, BUS_DMASYNC_PREWRITE);
			sc->sc_stats.mst_rxbuf_failed++;
			return ENOMEM;
		}
	}
	/*
	 * NB: DMA buffer contents is known to be unmodified
	 *     so there's no need to flush the data cache.
	 */

	/*
	 * Setup descriptor.
	 */
	ds->QosCtrl = 0;
	ds->RSSI = 0;
	ds->Status = EAGLE_RXD_STATUS_IDLE;
	ds->Channel = 0;
	ds->PktLen = htole16(MWL_AGGR_SIZE);
	ds->SQ2 = 0;
	ds->pPhysBuffData = htole32(MWL_JUMBO_DMA_ADDR(sc, bf->bf_data));
	/* NB: don't touch pPhysNext, set once */
	ds->RxControl = EAGLE_RXD_CTRL_DRIVER_OWN;
	MWL_RXDESC_SYNC(sc, ds, BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);

	return 0;
}