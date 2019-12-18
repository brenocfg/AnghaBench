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
struct xbd_softc {scalar_t__ xbd_state; int xbd_flags; int /*<<< orphan*/  xbd_max_request_segments; int /*<<< orphan*/  xbd_callback; } ;
struct xbd_command {void* cm_operation; int /*<<< orphan*/  cm_flags; scalar_t__ cm_sector_number; struct bio* cm_bp; int /*<<< orphan*/  cm_gref_head; } ;
struct bio {int bio_cmd; int bio_flags; scalar_t__ bio_pblkno; } ;
typedef  scalar_t__ blkif_sector_t ;

/* Variables and functions */
#define  BIO_FLUSH 130 
 int BIO_ORDERED ; 
#define  BIO_READ 129 
#define  BIO_WRITE 128 
 void* BLKIF_OP_FLUSH_DISKCACHE ; 
 void* BLKIF_OP_READ ; 
 void* BLKIF_OP_WRITE ; 
 void* BLKIF_OP_WRITE_BARRIER ; 
 int /*<<< orphan*/  XBDCF_Q_FREEZE ; 
 int XBDF_BARRIER ; 
 int /*<<< orphan*/  XBDF_CM_SHORTAGE ; 
 int XBDF_FLUSH ; 
 int /*<<< orphan*/  XBDF_GNT_SHORTAGE ; 
 int /*<<< orphan*/  XBDF_WAIT_IDLE ; 
 int /*<<< orphan*/  XBD_Q_BUSY ; 
 int /*<<< orphan*/  XBD_Q_FREE ; 
 int /*<<< orphan*/  XBD_Q_READY ; 
 scalar_t__ XBD_STATE_CONNECTED ; 
 scalar_t__ __predict_false (int) ; 
 scalar_t__ gnttab_alloc_grant_references (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gnttab_request_free_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct xbd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,...) ; 
 struct bio* xbd_dequeue_bio (struct xbd_softc*) ; 
 struct xbd_command* xbd_dequeue_cm (struct xbd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xbd_enqueue_cm (struct xbd_command*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xbd_freeze (struct xbd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xbd_queue_length (struct xbd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xbd_requeue_bio (struct xbd_softc*,struct bio*) ; 
 int /*<<< orphan*/  xbd_requeue_cm (struct xbd_command*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xbd_restart_queue_callback ; 

__attribute__((used)) static struct xbd_command *
xbd_bio_command(struct xbd_softc *sc)
{
	struct xbd_command *cm;
	struct bio *bp;

	if (__predict_false(sc->xbd_state != XBD_STATE_CONNECTED))
		return (NULL);

	bp = xbd_dequeue_bio(sc);
	if (bp == NULL)
		return (NULL);

	if ((cm = xbd_dequeue_cm(sc, XBD_Q_FREE)) == NULL) {
		xbd_freeze(sc, XBDF_CM_SHORTAGE);
		xbd_requeue_bio(sc, bp);
		return (NULL);
	}

	if (gnttab_alloc_grant_references(sc->xbd_max_request_segments,
	    &cm->cm_gref_head) != 0) {
		gnttab_request_free_callback(&sc->xbd_callback,
		    xbd_restart_queue_callback, sc,
		    sc->xbd_max_request_segments);
		xbd_freeze(sc, XBDF_GNT_SHORTAGE);
		xbd_requeue_bio(sc, bp);
		xbd_enqueue_cm(cm, XBD_Q_FREE);
		return (NULL);
	}

	cm->cm_bp = bp;
	cm->cm_sector_number = (blkif_sector_t)bp->bio_pblkno;

	switch (bp->bio_cmd) {
	case BIO_READ:
		cm->cm_operation = BLKIF_OP_READ;
		break;
	case BIO_WRITE:
		cm->cm_operation = BLKIF_OP_WRITE;
		if ((bp->bio_flags & BIO_ORDERED) != 0) {
			if ((sc->xbd_flags & XBDF_BARRIER) != 0) {
				cm->cm_operation = BLKIF_OP_WRITE_BARRIER;
			} else {
				/*
				 * Single step this command.
				 */
				cm->cm_flags |= XBDCF_Q_FREEZE;
				if (xbd_queue_length(sc, XBD_Q_BUSY) != 0) {
					/*
					 * Wait for in-flight requests to
					 * finish.
					 */
					xbd_freeze(sc, XBDF_WAIT_IDLE);
					xbd_requeue_cm(cm, XBD_Q_READY);
					return (NULL);
				}
			}
		}
		break;
	case BIO_FLUSH:
		if ((sc->xbd_flags & XBDF_FLUSH) != 0)
			cm->cm_operation = BLKIF_OP_FLUSH_DISKCACHE;
		else if ((sc->xbd_flags & XBDF_BARRIER) != 0)
			cm->cm_operation = BLKIF_OP_WRITE_BARRIER;
		else
			panic("flush request, but no flush support available");
		break;
	default:
		panic("unknown bio command %d", bp->bio_cmd);
	}

	return (cm);
}