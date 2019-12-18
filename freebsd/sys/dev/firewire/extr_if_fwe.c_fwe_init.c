#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  ext_size; } ;
struct TYPE_13__ {int /*<<< orphan*/  len; } ;
struct mbuf {TYPE_6__ m_ext; TYPE_5__ m_pkthdr; int /*<<< orphan*/  m_len; } ;
struct ifnet {int /*<<< orphan*/  if_drv_flags; int /*<<< orphan*/  if_flags; } ;
struct TYPE_16__ {struct firewire_comm* fc; } ;
struct TYPE_10__ {int chtag; } ;
struct TYPE_11__ {TYPE_2__ stream; } ;
struct TYPE_12__ {TYPE_3__ mode; } ;
struct TYPE_9__ {struct ifnet* ifp; } ;
struct fwe_softc {size_t dma_ch; int stream_ch; int /*<<< orphan*/  xferlist; TYPE_8__ fd; TYPE_4__ pkt_hdr; TYPE_1__ eth_softc; } ;
struct fwe_eth_softc {struct fwe_softc* fwe; } ;
struct fw_xferq {int flag; int bnchunk; int bnpacket; struct fw_xfer* bulkxfer; int /*<<< orphan*/  stfree; int /*<<< orphan*/ * stproc; int /*<<< orphan*/  stdma; int /*<<< orphan*/  stvalid; int /*<<< orphan*/ * buf; scalar_t__ queued; int /*<<< orphan*/  psize; int /*<<< orphan*/  hand; void* sc; } ;
struct TYPE_15__ {int /*<<< orphan*/  spd; } ;
struct fw_xfer {int /*<<< orphan*/  hand; void* sc; struct firewire_comm* fc; TYPE_7__ send; struct mbuf* mbuf; } ;
struct fw_bulkxfer {int /*<<< orphan*/  hand; void* sc; struct firewire_comm* fc; TYPE_7__ send; struct mbuf* mbuf; } ;
struct firewire_comm {int /*<<< orphan*/  (* irx_enable ) (struct firewire_comm*,size_t) ;struct fw_xferq** ir; } ;
typedef  void* caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  FWEDEBUG (struct ifnet*,char*) ; 
 int FWXFERQ_EXTBUF ; 
 int FWXFERQ_HANDLER ; 
 int FWXFERQ_RUNNING ; 
 int FWXFERQ_STREAM ; 
 int /*<<< orphan*/  IFF_DRV_OACTIVE ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IFF_PROMISC ; 
 int /*<<< orphan*/  MCLBYTES ; 
 int /*<<< orphan*/  MT_DATA ; 
 int /*<<< orphan*/  M_FWE ; 
 int /*<<< orphan*/  M_PKTHDR ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct fw_xfer*,int /*<<< orphan*/ ) ; 
 int TX_MAX_QUEUE ; 
 size_t fw_open_isodma (struct firewire_comm*,int /*<<< orphan*/ ) ; 
 struct fw_xfer* fw_xfer_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwe_as_input ; 
 int /*<<< orphan*/  fwe_output_callback ; 
 int /*<<< orphan*/  fwe_start (struct ifnet*) ; 
 int /*<<< orphan*/  link ; 
 struct mbuf* m_getcl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rx_queue_len ; 
 int stream_ch ; 
 int /*<<< orphan*/  stub1 (struct firewire_comm*,size_t) ; 
 int /*<<< orphan*/  tx_speed ; 

__attribute__((used)) static void
fwe_init(void *arg)
{
	struct fwe_softc *fwe = ((struct fwe_eth_softc *)arg)->fwe;
	struct firewire_comm *fc;
	struct ifnet *ifp = fwe->eth_softc.ifp;
	struct fw_xferq *xferq;
	struct fw_xfer *xfer;
	struct mbuf *m;
	int i;

	FWEDEBUG(ifp, "initializing\n");

	/* XXX keep promiscoud mode */
	ifp->if_flags |= IFF_PROMISC;

	fc = fwe->fd.fc;
	if (fwe->dma_ch < 0) {
		fwe->dma_ch = fw_open_isodma(fc, /* tx */0);
		if (fwe->dma_ch < 0)
			return;
		xferq = fc->ir[fwe->dma_ch];
		xferq->flag |= FWXFERQ_EXTBUF |
				FWXFERQ_HANDLER | FWXFERQ_STREAM;
		fwe->stream_ch = stream_ch;
		fwe->pkt_hdr.mode.stream.chtag = fwe->stream_ch;
		xferq->flag &= ~0xff;
		xferq->flag |= fwe->stream_ch & 0xff;
		/* register fwe_input handler */
		xferq->sc = (caddr_t) fwe;
		xferq->hand = fwe_as_input;
		xferq->bnchunk = rx_queue_len;
		xferq->bnpacket = 1;
		xferq->psize = MCLBYTES;
		xferq->queued = 0;
		xferq->buf = NULL;
		xferq->bulkxfer = (struct fw_bulkxfer *) malloc(
			sizeof(struct fw_bulkxfer) * xferq->bnchunk,
							M_FWE, M_WAITOK);
		STAILQ_INIT(&xferq->stvalid);
		STAILQ_INIT(&xferq->stfree);
		STAILQ_INIT(&xferq->stdma);
		xferq->stproc = NULL;
		for (i = 0; i < xferq->bnchunk; i++) {
			m = m_getcl(M_WAITOK, MT_DATA, M_PKTHDR);
			xferq->bulkxfer[i].mbuf = m;
			m->m_len = m->m_pkthdr.len = m->m_ext.ext_size;
			STAILQ_INSERT_TAIL(&xferq->stfree,
					&xferq->bulkxfer[i], link);
		}
		STAILQ_INIT(&fwe->xferlist);
		for (i = 0; i < TX_MAX_QUEUE; i++) {
			xfer = fw_xfer_alloc(M_FWE);
			if (xfer == NULL)
				break;
			xfer->send.spd = tx_speed;
			xfer->fc = fwe->fd.fc;
			xfer->sc = (caddr_t)fwe;
			xfer->hand = fwe_output_callback;
			STAILQ_INSERT_TAIL(&fwe->xferlist, xfer, link);
		}
	} else
		xferq = fc->ir[fwe->dma_ch];


	/* start dma */
	if ((xferq->flag & FWXFERQ_RUNNING) == 0)
		fc->irx_enable(fc, fwe->dma_ch);

	ifp->if_drv_flags |= IFF_DRV_RUNNING;
	ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;

#if 0
	/* attempt to start output */
	fwe_start(ifp);
#endif
}