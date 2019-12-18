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
struct tws_softc {int /*<<< orphan*/  io_lock; int /*<<< orphan*/  data_tag; } ;
struct tws_request {int flags; int /*<<< orphan*/  dma_map; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int TWS_DIR_IN ; 
 int TWS_DIR_OUT ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

void 
tws_unmap_request(struct tws_softc *sc, struct tws_request *req)
{
    if (req->data != NULL) {
        if ( req->flags & TWS_DIR_IN )
            bus_dmamap_sync(sc->data_tag, req->dma_map, 
                                            BUS_DMASYNC_POSTREAD);
        if ( req->flags & TWS_DIR_OUT )
            bus_dmamap_sync(sc->data_tag, req->dma_map, 
                                            BUS_DMASYNC_POSTWRITE);
        mtx_lock(&sc->io_lock);
        bus_dmamap_unload(sc->data_tag, req->dma_map);
        mtx_unlock(&sc->io_lock);
    }
}