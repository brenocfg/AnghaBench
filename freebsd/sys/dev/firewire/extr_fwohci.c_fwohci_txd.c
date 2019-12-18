#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int u_int ;
struct fwohcidb_tr {struct fw_xfer* xfer; int /*<<< orphan*/  dma_map; } ;
struct TYPE_6__ {int /*<<< orphan*/  res; } ;
struct TYPE_7__ {TYPE_1__ desc; } ;
struct fwohcidb {TYPE_2__ db; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct TYPE_10__ {scalar_t__ queued; } ;
struct fwohci_dbch {int flags; TYPE_5__ xferq; struct fwohcidb_tr* top; struct fwohcidb_tr* bottom; int /*<<< orphan*/  dmat; int /*<<< orphan*/  am; } ;
struct fwohci_softc {TYPE_3__ fc; struct fwohci_dbch atrs; struct fwohci_dbch atrq; } ;
struct TYPE_9__ {scalar_t__ pay_len; } ;
struct fw_xfer {int flag; int resp; TYPE_4__ recv; int /*<<< orphan*/  tv; } ;
struct firewire_comm {scalar_t__ status; } ;

/* Variables and functions */
 int ATRQ_CH ; 
 int ATRS_CH ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int EAGAIN ; 
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ FWBUSINIT ; 
#define  FWOHCIEV_ACKBSA 144 
#define  FWOHCIEV_ACKBSB 143 
#define  FWOHCIEV_ACKBSX 142 
#define  FWOHCIEV_ACKCOMPL 141 
#define  FWOHCIEV_ACKDERR 140 
#define  FWOHCIEV_ACKPEND 139 
#define  FWOHCIEV_ACKTARD 138 
#define  FWOHCIEV_ACKTERR 137 
#define  FWOHCIEV_DESCERR 136 
#define  FWOHCIEV_DTRDERR 135 
#define  FWOHCIEV_FLUSHED 134 
 int FWOHCIEV_MASK ; 
#define  FWOHCIEV_MISSACK 133 
#define  FWOHCIEV_OVRRUN 132 
#define  FWOHCIEV_TCODERR 131 
#define  FWOHCIEV_TIMEOUT 130 
#define  FWOHCIEV_UNDRRUN 129 
#define  FWOHCIEV_UNKNOWN 128 
 int FWOHCI_DBCH_FULL ; 
 int FWOHCI_DMA_READ (int /*<<< orphan*/ ) ; 
 int FWXF_BUSY ; 
 int FWXF_RCVD ; 
 int FWXF_SENT ; 
 int FWXF_SENTERR ; 
 int /*<<< orphan*/  FW_GLOCK (struct firewire_comm*) ; 
 int /*<<< orphan*/  FW_GUNLOCK (struct firewire_comm*) ; 
 int /*<<< orphan*/  LAST_DB (struct fwohcidb_tr*,struct fwohcidb*) ; 
 int /*<<< orphan*/  OHCI_ATQOFF ; 
 int /*<<< orphan*/  OHCI_ATSOFF ; 
 int OHCI_CNTL_DMA_ACTIVE ; 
 int OHCI_CNTL_DMA_DEAD ; 
 int OHCI_CNTL_DMA_RUN ; 
 int /*<<< orphan*/  OHCI_DMACTLCLR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OHCI_HCCCTL ; 
 int /*<<< orphan*/  OHCI_HCCCTLCLR ; 
 int OHCI_HCC_LINKEN ; 
 int OHCI_HCC_LPS ; 
 int OHCI_STATUS_SHIFT ; 
 int /*<<< orphan*/  OWRITE (struct fwohci_softc*,int /*<<< orphan*/ ,int) ; 
 struct fwohcidb_tr* STAILQ_NEXT (struct fwohcidb_tr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dump_db (struct fwohci_softc*,int) ; 
 int firewire_debug ; 
 int /*<<< orphan*/  fw_xfer_done (struct fw_xfer*) ; 
 int /*<<< orphan*/  fwdma_sync_multiseg_all (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwohci_start (struct fwohci_softc*,struct fwohci_dbch*) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  microtime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int splfw () ; 
 int /*<<< orphan*/  splx (int) ; 

void
fwohci_txd(struct fwohci_softc *sc, struct fwohci_dbch *dbch)
{
	int s, ch, err = 0;
	struct fwohcidb_tr *tr;
	struct fwohcidb *db;
	struct fw_xfer *xfer;
	uint32_t off;
	u_int stat, status;
	int	packets;
	struct firewire_comm *fc = (struct firewire_comm *)sc;

	if (&sc->atrq == dbch) {
		off = OHCI_ATQOFF;
		ch = ATRQ_CH;
	} else if (&sc->atrs == dbch) {
		off = OHCI_ATSOFF;
		ch = ATRS_CH;
	} else {
		return;
	}
	s = splfw();
	tr = dbch->bottom;
	packets = 0;
	fwdma_sync_multiseg_all(dbch->am, BUS_DMASYNC_POSTREAD);
	fwdma_sync_multiseg_all(dbch->am, BUS_DMASYNC_POSTWRITE);
	while (dbch->xferq.queued > 0) {
		LAST_DB(tr, db);
		status = FWOHCI_DMA_READ(db->db.desc.res) >> OHCI_STATUS_SHIFT;
		if (!(status & OHCI_CNTL_DMA_ACTIVE)) {
			if (fc->status != FWBUSINIT)
				/* maybe out of order?? */
				goto out;
		}
		bus_dmamap_sync(dbch->dmat, tr->dma_map,
			BUS_DMASYNC_POSTWRITE);
		bus_dmamap_unload(dbch->dmat, tr->dma_map);
#if 1
		if (firewire_debug > 1)
			dump_db(sc, ch);
#endif
		if (status & OHCI_CNTL_DMA_DEAD) {
			/* Stop DMA */
			OWRITE(sc, OHCI_DMACTLCLR(off), OHCI_CNTL_DMA_RUN);
			device_printf(sc->fc.dev, "force reset AT FIFO\n");
			OWRITE(sc, OHCI_HCCCTLCLR, OHCI_HCC_LINKEN);
			OWRITE(sc, OHCI_HCCCTL, OHCI_HCC_LPS | OHCI_HCC_LINKEN);
			OWRITE(sc, OHCI_DMACTLCLR(off), OHCI_CNTL_DMA_RUN);
		}
		stat = status & FWOHCIEV_MASK;
		switch (stat) {
		case FWOHCIEV_ACKPEND:
		case FWOHCIEV_ACKCOMPL:
			err = 0;
			break;
		case FWOHCIEV_ACKBSA:
		case FWOHCIEV_ACKBSB:
		case FWOHCIEV_ACKBSX:
			err = EBUSY;
			break;
		case FWOHCIEV_FLUSHED:
		case FWOHCIEV_ACKTARD:
			err = EAGAIN;
			break;
		case FWOHCIEV_MISSACK:
		case FWOHCIEV_UNDRRUN:
		case FWOHCIEV_OVRRUN:
		case FWOHCIEV_DESCERR:
		case FWOHCIEV_DTRDERR:
		case FWOHCIEV_TIMEOUT:
		case FWOHCIEV_TCODERR:
		case FWOHCIEV_UNKNOWN:
		case FWOHCIEV_ACKDERR:
		case FWOHCIEV_ACKTERR:
		default:
			err = EINVAL;
			break;
		}
		if (tr->xfer != NULL) {
			xfer = tr->xfer;
			if (xfer->flag & FWXF_RCVD) {
#if 0
				if (firewire_debug)
					printf("already rcvd\n");
#endif
				fw_xfer_done(xfer);
			} else {
				microtime(&xfer->tv);
				xfer->flag = FWXF_SENT;
				if (err == EBUSY) {
					xfer->flag = FWXF_BUSY;
					xfer->resp = err;
					xfer->recv.pay_len = 0;
					fw_xfer_done(xfer);
				} else if (stat != FWOHCIEV_ACKPEND) {
					if (stat != FWOHCIEV_ACKCOMPL)
						xfer->flag = FWXF_SENTERR;
					xfer->resp = err;
					xfer->recv.pay_len = 0;
					fw_xfer_done(xfer);
				}
			}
			/*
			 * The watchdog timer takes care of split
			 * transaction timeout for ACKPEND case.
			 */
		} else {
			printf("this shouldn't happen\n");
		}
		FW_GLOCK(fc);
		dbch->xferq.queued--;
		FW_GUNLOCK(fc);
		tr->xfer = NULL;

		packets++;
		tr = STAILQ_NEXT(tr, link);
		dbch->bottom = tr;
		if (dbch->bottom == dbch->top) {
			/* we reaches the end of context program */
			if (firewire_debug && dbch->xferq.queued > 0)
				printf("queued > 0\n");
			break;
		}
	}
out:
	if ((dbch->flags & FWOHCI_DBCH_FULL) && packets > 0) {
		printf("make free slot\n");
		dbch->flags &= ~FWOHCI_DBCH_FULL;
		FW_GLOCK(fc);
		fwohci_start(sc, dbch);
		FW_GUNLOCK(fc);
	}
	splx(s);
}