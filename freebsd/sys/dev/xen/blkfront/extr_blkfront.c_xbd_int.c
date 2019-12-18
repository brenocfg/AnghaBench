#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ rsp_cons; scalar_t__ req_prod_pvt; TYPE_1__* sring; } ;
struct xbd_softc {scalar_t__ xbd_state; int /*<<< orphan*/  xbd_io_lock; int /*<<< orphan*/ * xbd_cm_q; TYPE_4__ xbd_ring; int /*<<< orphan*/  xbd_io_dmat; struct xbd_command* xbd_shadow; } ;
struct xbd_command {scalar_t__ cm_operation; int /*<<< orphan*/  (* cm_complete ) (struct xbd_command*) ;scalar_t__ cm_bp; int /*<<< orphan*/  cm_status; int /*<<< orphan*/  cm_map; int /*<<< orphan*/  cm_sg_refs; int /*<<< orphan*/  cm_nseg; } ;
struct TYPE_7__ {size_t id; int /*<<< orphan*/  status; } ;
typedef  TYPE_2__ blkif_response_t ;
struct TYPE_6__ {scalar_t__ rsp_prod; scalar_t__ rsp_event; } ;
typedef  scalar_t__ RING_IDX ;

/* Variables and functions */
 scalar_t__ BLKIF_OP_READ ; 
 scalar_t__ BLKIF_OP_WRITE ; 
 scalar_t__ BLKIF_OP_WRITE_BARRIER ; 
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_POSTWRITE ; 
 int /*<<< orphan*/  RING_FINAL_CHECK_FOR_RESPONSES (TYPE_4__*,int) ; 
 TYPE_2__* RING_GET_RESPONSE (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  XBDF_WAIT_IDLE ; 
 size_t XBD_Q_BUSY ; 
 scalar_t__ XBD_STATE_DISCONNECTED ; 
 scalar_t__ XBD_STATE_SUSPENDED ; 
 scalar_t__ __predict_false (int) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gnttab_end_foreign_access_references (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  stub1 (struct xbd_command*) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xbd_bio_complete (struct xbd_softc*,struct xbd_command*) ; 
 int /*<<< orphan*/  xbd_cm_thaw (struct xbd_softc*,struct xbd_command*) ; 
 int /*<<< orphan*/  xbd_free_command (struct xbd_command*) ; 
 scalar_t__ xbd_queue_length (struct xbd_softc*,size_t) ; 
 int /*<<< orphan*/  xbd_remove_cm (struct xbd_command*,size_t) ; 
 int /*<<< orphan*/  xbd_startio (struct xbd_softc*) ; 
 int /*<<< orphan*/  xbd_thaw (struct xbd_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xbd_int(void *xsc)
{
	struct xbd_softc *sc = xsc;
	struct xbd_command *cm;
	blkif_response_t *bret;
	RING_IDX i, rp;
	int op;

	mtx_lock(&sc->xbd_io_lock);

	if (__predict_false(sc->xbd_state == XBD_STATE_DISCONNECTED)) {
		mtx_unlock(&sc->xbd_io_lock);
		return;
	}

 again:
	rp = sc->xbd_ring.sring->rsp_prod;
	rmb(); /* Ensure we see queued responses up to 'rp'. */

	for (i = sc->xbd_ring.rsp_cons; i != rp;) {
		bret = RING_GET_RESPONSE(&sc->xbd_ring, i);
		cm   = &sc->xbd_shadow[bret->id];

		xbd_remove_cm(cm, XBD_Q_BUSY);
		gnttab_end_foreign_access_references(cm->cm_nseg,
		    cm->cm_sg_refs);
		i++;

		if (cm->cm_operation == BLKIF_OP_READ)
			op = BUS_DMASYNC_POSTREAD;
		else if (cm->cm_operation == BLKIF_OP_WRITE ||
		    cm->cm_operation == BLKIF_OP_WRITE_BARRIER)
			op = BUS_DMASYNC_POSTWRITE;
		else
			op = 0;
		bus_dmamap_sync(sc->xbd_io_dmat, cm->cm_map, op);
		bus_dmamap_unload(sc->xbd_io_dmat, cm->cm_map);

		/*
		 * Release any hold this command has on future command
		 * dispatch. 
		 */
		xbd_cm_thaw(sc, cm);

		/*
		 * Directly call the i/o complete routine to save an
		 * an indirection in the common case.
		 */
		cm->cm_status = bret->status;
		if (cm->cm_bp)
			xbd_bio_complete(sc, cm);
		else if (cm->cm_complete != NULL)
			cm->cm_complete(cm);
		else
			xbd_free_command(cm);
	}

	sc->xbd_ring.rsp_cons = i;

	if (i != sc->xbd_ring.req_prod_pvt) {
		int more_to_do;
		RING_FINAL_CHECK_FOR_RESPONSES(&sc->xbd_ring, more_to_do);
		if (more_to_do)
			goto again;
	} else {
		sc->xbd_ring.sring->rsp_event = i + 1;
	}

	if (xbd_queue_length(sc, XBD_Q_BUSY) == 0)
		xbd_thaw(sc, XBDF_WAIT_IDLE);

	xbd_startio(sc);

	if (__predict_false(sc->xbd_state == XBD_STATE_SUSPENDED))
		wakeup(&sc->xbd_cm_q[XBD_Q_BUSY]);

	mtx_unlock(&sc->xbd_io_lock);
}