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
typedef  int uint32_t ;
struct xhci_trb {int qwTrb0; int dwTrb2; int dwTrb3; } ;
struct xhci_stream_ctx {int dummy; } ;
struct xhci_endp_ctx {int dwEpCtx0; int qwEpCtx2; } ;
struct xhci_dev_ctx {struct xhci_endp_ctx* ctx_ep; } ;
struct pci_xhci_softc {int dummy; } ;
struct pci_xhci_dev_ep {int ep_ringaddr; int ep_ccs; int /*<<< orphan*/  ep_tr; TYPE_2__* ep_sctx_trbs; TYPE_1__* ep_sctx; } ;
struct pci_xhci_dev_emu {struct pci_xhci_dev_ep* eps; struct xhci_dev_ctx* dev_ctx; } ;
struct TYPE_4__ {int ringaddr; int /*<<< orphan*/  ccs; } ;
struct TYPE_3__ {int qwSctx0; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int XHCI_EPCTX_0_EPSTATE_GET (int) ; 
 scalar_t__ XHCI_EPCTX_0_MAXP_STREAMS_GET (int) ; 
 int /*<<< orphan*/  XHCI_EPCTX_2_DCS_GET (int) ; 
 int /*<<< orphan*/  XHCI_GADDR (struct pci_xhci_softc*,int) ; 
 struct pci_xhci_dev_emu* XHCI_SLOTDEV_PTR (struct pci_xhci_softc*,int) ; 
#define  XHCI_ST_EPCTX_ERROR 129 
#define  XHCI_ST_EPCTX_STOPPED 128 
 int XHCI_TRB_2_STREAM_GET (int) ; 
 int XHCI_TRB_3_EP_GET (int) ; 
 int /*<<< orphan*/  XHCI_TRB_3_SLOT_GET (int) ; 
 int XHCI_TRB_ERROR_CONTEXT_STATE ; 
 int XHCI_TRB_ERROR_SUCCESS ; 
 int XHCI_TRB_ERROR_TRB ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_xhci_dump_trb (int /*<<< orphan*/ ) ; 
 int pci_xhci_find_stream (struct pci_xhci_softc*,struct xhci_endp_ctx*,int,struct xhci_stream_ctx**) ; 

__attribute__((used)) static uint32_t
pci_xhci_cmd_set_tr(struct pci_xhci_softc *sc, uint32_t slot,
    struct xhci_trb *trb)
{
	struct pci_xhci_dev_emu	*dev;
	struct pci_xhci_dev_ep	*devep;
	struct xhci_dev_ctx	*dev_ctx;
	struct xhci_endp_ctx	*ep_ctx;
	uint32_t	cmderr, epid;
	uint32_t	streamid;

	cmderr = XHCI_TRB_ERROR_SUCCESS;

	dev = XHCI_SLOTDEV_PTR(sc, slot);
	assert(dev != NULL);

	DPRINTF(("pci_xhci set_tr: new-tr x%016lx, SCT %u DCS %u\r\n"
	         "                 stream-id %u, slot %u, epid %u, C %u\r\n",
	         (trb->qwTrb0 & ~0xF),  (uint32_t)((trb->qwTrb0 >> 1) & 0x7),
	         (uint32_t)(trb->qwTrb0 & 0x1), (trb->dwTrb2 >> 16) & 0xFFFF,
	         XHCI_TRB_3_SLOT_GET(trb->dwTrb3),
	         XHCI_TRB_3_EP_GET(trb->dwTrb3), trb->dwTrb3 & 0x1));

	epid = XHCI_TRB_3_EP_GET(trb->dwTrb3);
	if (epid < 1 || epid > 31) {
		DPRINTF(("pci_xhci: set_tr_deq: invalid epid %u\r\n", epid));
		cmderr = XHCI_TRB_ERROR_TRB;
		goto done;
	}

	dev_ctx = dev->dev_ctx;
	assert(dev_ctx != NULL);

	ep_ctx = &dev_ctx->ctx_ep[epid];
	devep = &dev->eps[epid];

	switch (XHCI_EPCTX_0_EPSTATE_GET(ep_ctx->dwEpCtx0)) {
	case XHCI_ST_EPCTX_STOPPED:
	case XHCI_ST_EPCTX_ERROR:
		break;
	default:
		DPRINTF(("pci_xhci cmd set_tr invalid state %x\r\n",
		        XHCI_EPCTX_0_EPSTATE_GET(ep_ctx->dwEpCtx0)));
		cmderr = XHCI_TRB_ERROR_CONTEXT_STATE;
		goto done;
	}

	streamid = XHCI_TRB_2_STREAM_GET(trb->dwTrb2);
	if (XHCI_EPCTX_0_MAXP_STREAMS_GET(ep_ctx->dwEpCtx0) > 0) {
		struct xhci_stream_ctx *sctx;

		sctx = NULL;
		cmderr = pci_xhci_find_stream(sc, ep_ctx, streamid, &sctx);
		if (sctx != NULL) {
			assert(devep->ep_sctx != NULL);
			
			devep->ep_sctx[streamid].qwSctx0 = trb->qwTrb0;
			devep->ep_sctx_trbs[streamid].ringaddr =
			    trb->qwTrb0 & ~0xF;
			devep->ep_sctx_trbs[streamid].ccs =
			    XHCI_EPCTX_2_DCS_GET(trb->qwTrb0);
		}
	} else {
		if (streamid != 0) {
			DPRINTF(("pci_xhci cmd set_tr streamid %x != 0\r\n",
			        streamid));
		}
		ep_ctx->qwEpCtx2 = trb->qwTrb0 & ~0xFUL;
		devep->ep_ringaddr = ep_ctx->qwEpCtx2 & ~0xFUL;
		devep->ep_ccs = trb->qwTrb0 & 0x1;
		devep->ep_tr = XHCI_GADDR(sc, devep->ep_ringaddr);

		DPRINTF(("pci_xhci set_tr first TRB:\r\n"));
		pci_xhci_dump_trb(devep->ep_tr);
	}
	ep_ctx->dwEpCtx0 = (ep_ctx->dwEpCtx0 & ~0x7) | XHCI_ST_EPCTX_STOPPED;

done:
	return (cmderr);
}