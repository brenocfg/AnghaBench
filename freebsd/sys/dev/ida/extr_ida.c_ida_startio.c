#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct idad_softc {int /*<<< orphan*/  drive; } ;
struct ida_softc {int flags; int /*<<< orphan*/  bio_queue; int /*<<< orphan*/  lock; } ;
struct ida_qcb {int error; struct ida_hardware_qcb* hwqcb; int /*<<< orphan*/  flags; struct bio* buf; } ;
struct TYPE_4__ {int /*<<< orphan*/  command; int /*<<< orphan*/  bcount; int /*<<< orphan*/  blkno; } ;
struct TYPE_3__ {int /*<<< orphan*/  drive; } ;
struct ida_hardware_qcb {TYPE_2__ req; TYPE_1__ hdr; } ;
struct bio {scalar_t__ bio_cmd; int /*<<< orphan*/  bio_bcount; int /*<<< orphan*/  bio_data; int /*<<< orphan*/  bio_pblkno; struct idad_softc* bio_driver1; } ;

/* Variables and functions */
 scalar_t__ BIO_READ ; 
 int /*<<< orphan*/  CMD_READ ; 
 int /*<<< orphan*/  CMD_WRITE ; 
 int /*<<< orphan*/  DEV_BSIZE ; 
 int /*<<< orphan*/  DMA_DATA_IN ; 
 int /*<<< orphan*/  DMA_DATA_OUT ; 
 int IDA_QFROZEN ; 
 int /*<<< orphan*/  MA_OWNED ; 
 struct bio* bioq_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bioq_remove (int /*<<< orphan*/ *,struct bio*) ; 
 int /*<<< orphan*/  howmany (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_done (struct ida_softc*,struct ida_qcb*) ; 
 struct ida_qcb* ida_get_qcb (struct ida_softc*) ; 
 int ida_map_qcb (struct ida_softc*,struct ida_qcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ida_startio(struct ida_softc *ida)
{
	struct ida_hardware_qcb *hwqcb;
	struct ida_qcb *qcb;
	struct idad_softc *drv;
	struct bio *bp;
	int error;

	mtx_assert(&ida->lock, MA_OWNED);
	for (;;) {
		if (ida->flags & IDA_QFROZEN)
			return;
		bp = bioq_first(&ida->bio_queue);
		if (bp == NULL)
			return;				/* no more buffers */

		qcb = ida_get_qcb(ida);
		if (qcb == NULL)
			return;				/* out of resources */

		bioq_remove(&ida->bio_queue, bp);
		qcb->buf = bp;
		qcb->flags = bp->bio_cmd == BIO_READ ? DMA_DATA_IN : DMA_DATA_OUT;

		hwqcb = qcb->hwqcb;
		drv = bp->bio_driver1;
		hwqcb->hdr.drive = drv->drive;
		hwqcb->req.blkno = bp->bio_pblkno;
		hwqcb->req.bcount = howmany(bp->bio_bcount, DEV_BSIZE);
		hwqcb->req.command = bp->bio_cmd == BIO_READ ? CMD_READ : CMD_WRITE;

		error = ida_map_qcb(ida, qcb, bp->bio_data, bp->bio_bcount);
		if (error) {
			qcb->error = error;
			ida_done(ida, qcb);
		}
	}
}