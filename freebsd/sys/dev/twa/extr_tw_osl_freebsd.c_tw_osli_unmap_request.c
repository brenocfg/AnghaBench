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
struct twa_softc {int /*<<< orphan*/  dma_tag; int /*<<< orphan*/  io_lock; int /*<<< orphan*/  ioctl_map; int /*<<< orphan*/  ioctl_tag; } ;
struct tw_osli_req_context {int flags; int /*<<< orphan*/  real_length; int /*<<< orphan*/  length; int /*<<< orphan*/ * real_data; int /*<<< orphan*/ * data; int /*<<< orphan*/  dma_map; struct twa_softc* ctlr; } ;
typedef  int /*<<< orphan*/  TW_VOID ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int /*<<< orphan*/  TW_OSLI_MALLOC_CLASS ; 
 int TW_OSLI_REQ_FLAGS_DATA_COPY_NEEDED ; 
 int TW_OSLI_REQ_FLAGS_DATA_IN ; 
 int TW_OSLI_REQ_FLAGS_DATA_OUT ; 
 int TW_OSLI_REQ_FLAGS_PASSTHRU ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw_osli_dbg_dprintf (int,struct twa_softc*,char*) ; 

TW_VOID
tw_osli_unmap_request(struct tw_osli_req_context *req)
{
	struct twa_softc	*sc = req->ctlr;

	tw_osli_dbg_dprintf(10, sc, "entered");

	/* If the command involved data, unmap that too. */
	if (req->data != NULL) {
		if (req->flags & TW_OSLI_REQ_FLAGS_PASSTHRU) {
			/* Lock against multiple simultaneous ioctl calls. */
			mtx_lock_spin(sc->io_lock);

			if (req->flags & TW_OSLI_REQ_FLAGS_DATA_IN) {
				bus_dmamap_sync(sc->ioctl_tag,
					sc->ioctl_map, BUS_DMASYNC_POSTREAD);

				/* 
				 * If we are using a bounce buffer, and we are
				 * reading data, copy the real data in.
				 */
				if (req->flags & TW_OSLI_REQ_FLAGS_DATA_COPY_NEEDED)
					bcopy(req->data, req->real_data,
						req->real_length);
			}

			if (req->flags & TW_OSLI_REQ_FLAGS_DATA_OUT)
				bus_dmamap_sync(sc->ioctl_tag, sc->ioctl_map,
					BUS_DMASYNC_POSTWRITE);

			bus_dmamap_unload(sc->ioctl_tag, sc->ioctl_map);

			mtx_unlock_spin(sc->io_lock);
		} else {
			if (req->flags & TW_OSLI_REQ_FLAGS_DATA_IN) {
				bus_dmamap_sync(sc->dma_tag,
					req->dma_map, BUS_DMASYNC_POSTREAD);

				/* 
				 * If we are using a bounce buffer, and we are
				 * reading data, copy the real data in.
				 */
				if (req->flags & TW_OSLI_REQ_FLAGS_DATA_COPY_NEEDED)
					bcopy(req->data, req->real_data,
						req->real_length);
			}
			if (req->flags & TW_OSLI_REQ_FLAGS_DATA_OUT)
				bus_dmamap_sync(sc->dma_tag, req->dma_map,
					BUS_DMASYNC_POSTWRITE);

			bus_dmamap_unload(sc->dma_tag, req->dma_map);
		}
	}

	/* Free alignment buffer if it was used. */
	if (req->flags & TW_OSLI_REQ_FLAGS_DATA_COPY_NEEDED) {
		free(req->data, TW_OSLI_MALLOC_CLASS);
		/* Restore original data pointer and length. */
		req->data = req->real_data;
		req->length = req->real_length;
	}
}