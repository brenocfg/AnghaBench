#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ida_softc {int flags; int /*<<< orphan*/  ch; scalar_t__ qactive; int /*<<< orphan*/  dev; int /*<<< orphan*/  hwqcb_dmamap; int /*<<< orphan*/  hwqcb_dmat; int /*<<< orphan*/  buffer_dmat; int /*<<< orphan*/  lock; } ;
struct ida_qcb {scalar_t__ state; int flags; char* error; TYPE_3__* buf; TYPE_2__* hwqcb; int /*<<< orphan*/  dmamap; } ;
typedef  int bus_dmasync_op_t ;
struct TYPE_6__ {scalar_t__ bio_cmd; int /*<<< orphan*/  bio_flags; } ;
struct TYPE_4__ {int error; } ;
struct TYPE_5__ {TYPE_1__ req; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_ERROR ; 
 scalar_t__ BIO_READ ; 
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_POSTWRITE ; 
 int CMD_REJECTED ; 
#define  DMA_DATA_IN 129 
 int const DMA_DATA_OUT ; 
#define  DMA_DATA_TRANSFER 128 
 int HARD_ERROR ; 
 int IDA_COMMAND ; 
 int IDA_INTERRUPTS ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 scalar_t__ QCB_FREE ; 
 scalar_t__ QCB_TIMEDOUT ; 
 int SOFT_ERROR ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct ida_softc*) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dumping ; 
 int hz ; 
 int /*<<< orphan*/  ida_free_qcb (struct ida_softc*,struct ida_qcb*) ; 
 int /*<<< orphan*/  ida_timeout ; 
 int /*<<< orphan*/  idad_intr (TYPE_3__*) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (struct ida_qcb*) ; 

__attribute__((used)) static void
ida_done(struct ida_softc *ida, struct ida_qcb *qcb)
{
	bus_dmasync_op_t op;
	int active, error = 0;

	/*
	 * finish up command
	 */
	if (!dumping)
		mtx_assert(&ida->lock, MA_OWNED);
	active = (qcb->state != QCB_FREE);
	if (qcb->flags & DMA_DATA_TRANSFER && active) {
		switch (qcb->flags & DMA_DATA_TRANSFER) {
		case DMA_DATA_TRANSFER:
			op = BUS_DMASYNC_POSTREAD | BUS_DMASYNC_POSTWRITE;
			break;
		case DMA_DATA_IN:
			op = BUS_DMASYNC_POSTREAD;
			break;
		default:
			KASSERT((qcb->flags & DMA_DATA_TRANSFER) ==
			    DMA_DATA_OUT, ("bad DMA data flags"));
			op = BUS_DMASYNC_POSTWRITE;
			break;
		}
		bus_dmamap_sync(ida->buffer_dmat, qcb->dmamap, op);
		bus_dmamap_unload(ida->buffer_dmat, qcb->dmamap);
	}
	if (active)
		bus_dmamap_sync(ida->hwqcb_dmat, ida->hwqcb_dmamap,
		    BUS_DMASYNC_POSTREAD | BUS_DMASYNC_POSTWRITE);

	if (qcb->hwqcb->req.error & SOFT_ERROR) {
		if (qcb->buf)
			device_printf(ida->dev, "soft %s error\n",
				qcb->buf->bio_cmd == BIO_READ ?
					"read" : "write");
		else
			device_printf(ida->dev, "soft error\n");
	}
	if (qcb->hwqcb->req.error & HARD_ERROR) {
		error = 1;
		if (qcb->buf)
			device_printf(ida->dev, "hard %s error\n",
				qcb->buf->bio_cmd == BIO_READ ?
					"read" : "write");
		else
			device_printf(ida->dev, "hard error\n");
	}
	if (qcb->hwqcb->req.error & CMD_REJECTED) {
		error = 1;
		device_printf(ida->dev, "invalid request\n");
	}
	if (qcb->error) {
		error = 1;
		device_printf(ida->dev, "request failed to map: %d\n", qcb->error);
	}

	if (qcb->flags & IDA_COMMAND) {
		if (ida->flags & IDA_INTERRUPTS)
			wakeup(qcb);
		if (qcb->state == QCB_TIMEDOUT)
			ida_free_qcb(ida, qcb);
	} else {
		KASSERT(qcb->buf != NULL, ("ida_done(): qcb->buf is NULL!"));
		if (error)
			qcb->buf->bio_flags |= BIO_ERROR;
		idad_intr(qcb->buf);
		ida_free_qcb(ida, qcb);
	}

	if (!active)
		return;

	ida->qactive--;
	/* Reschedule or cancel timeout */
	if (ida->qactive)
		callout_reset(&ida->ch, hz * 5, ida_timeout, ida);
	else
		callout_stop(&ida->ch);
}