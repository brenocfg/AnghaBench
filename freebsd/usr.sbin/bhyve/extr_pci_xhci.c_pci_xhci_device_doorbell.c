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
typedef  int uint64_t ;
typedef  size_t uint32_t ;
struct xhci_trb {int dwTrb3; } ;
struct xhci_stream_ctx {int dummy; } ;
struct xhci_endp_ctx {int qwEpCtx2; int /*<<< orphan*/  dwEpCtx0; int /*<<< orphan*/  dwEpCtx4; int /*<<< orphan*/  dwEpCtx1; } ;
struct xhci_dev_ctx {struct xhci_endp_ctx* ctx_ep; } ;
struct pci_xhci_trb_ring {int ringaddr; size_t ccs; } ;
struct pci_xhci_softc {size_t ndevices; } ;
struct pci_xhci_dev_ep {int ep_ringaddr; size_t ep_ccs; struct xhci_trb* ep_tr; struct pci_xhci_trb_ring* ep_sctx_trbs; TYPE_1__* ep_xfer; } ;
struct pci_xhci_dev_emu {struct pci_xhci_dev_ep* eps; } ;
struct TYPE_2__ {scalar_t__ ndata; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 scalar_t__ XHCI_EPCTX_0_MAXP_STREAMS_GET (int /*<<< orphan*/ ) ; 
 struct xhci_trb* XHCI_GADDR (struct pci_xhci_softc*,int) ; 
 size_t XHCI_MAX_ENDPOINTS ; 
 struct pci_xhci_dev_emu* XHCI_SLOTDEV_PTR (struct pci_xhci_softc*,size_t) ; 
 int XHCI_TRB_3_CYCLE_BIT ; 
 scalar_t__ XHCI_TRB_3_TYPE_GET (int) ; 
 int /*<<< orphan*/  pci_xhci_find_stream (struct pci_xhci_softc*,struct xhci_endp_ctx*,size_t,struct xhci_stream_ctx**) ; 
 struct xhci_dev_ctx* pci_xhci_get_dev_ctx (struct pci_xhci_softc*,size_t) ; 
 int /*<<< orphan*/  pci_xhci_handle_transfer (struct pci_xhci_softc*,struct pci_xhci_dev_emu*,struct pci_xhci_dev_ep*,struct xhci_endp_ctx*,struct xhci_trb*,size_t,size_t,int,size_t,size_t) ; 
 int /*<<< orphan*/  pci_xhci_try_usb_xfer (struct pci_xhci_softc*,struct pci_xhci_dev_emu*,struct pci_xhci_dev_ep*,struct xhci_endp_ctx*,size_t,size_t) ; 

__attribute__((used)) static void
pci_xhci_device_doorbell(struct pci_xhci_softc *sc, uint32_t slot,
    uint32_t epid, uint32_t streamid)
{
	struct pci_xhci_dev_emu *dev;
	struct pci_xhci_dev_ep	*devep;
	struct xhci_dev_ctx	*dev_ctx;
	struct xhci_endp_ctx	*ep_ctx;
	struct pci_xhci_trb_ring *sctx_tr;
	struct xhci_trb	*trb;
	uint64_t	ringaddr;
	uint32_t	ccs;

	DPRINTF(("pci_xhci doorbell slot %u epid %u stream %u\r\n",
	    slot, epid, streamid));

	if (slot == 0 || slot > sc->ndevices) {
		DPRINTF(("pci_xhci: invalid doorbell slot %u\r\n", slot));
		return;
	}

	if (epid == 0 || epid >= XHCI_MAX_ENDPOINTS) {
		DPRINTF(("pci_xhci: invalid endpoint %u\r\n", epid));
		return;
	}

	dev = XHCI_SLOTDEV_PTR(sc, slot);
	devep = &dev->eps[epid];
	dev_ctx = pci_xhci_get_dev_ctx(sc, slot);
	if (!dev_ctx) {
		return;
	}
	ep_ctx = &dev_ctx->ctx_ep[epid];

	sctx_tr = NULL;

	DPRINTF(("pci_xhci: device doorbell ep[%u] %08x %08x %016lx %08x\r\n",
	        epid, ep_ctx->dwEpCtx0, ep_ctx->dwEpCtx1, ep_ctx->qwEpCtx2,
	        ep_ctx->dwEpCtx4));

	if (ep_ctx->qwEpCtx2 == 0)
		return;

	/* handle pending transfers */
	if (devep->ep_xfer->ndata > 0) {
		pci_xhci_try_usb_xfer(sc, dev, devep, ep_ctx, slot, epid);
		return;
	}

	/* get next trb work item */
	if (XHCI_EPCTX_0_MAXP_STREAMS_GET(ep_ctx->dwEpCtx0) != 0) {
		struct xhci_stream_ctx *sctx;

		/*
		 * Stream IDs of 0, 65535 (any stream), and 65534
		 * (prime) are invalid.
		 */
		if (streamid == 0 || streamid == 65534 || streamid == 65535) {
			DPRINTF(("pci_xhci: invalid stream %u\r\n", streamid));
			return;
		}

		sctx = NULL;
		pci_xhci_find_stream(sc, ep_ctx, streamid, &sctx);
		if (sctx == NULL) {
			DPRINTF(("pci_xhci: invalid stream %u\r\n", streamid));
			return;
		}
		sctx_tr = &devep->ep_sctx_trbs[streamid];
		ringaddr = sctx_tr->ringaddr;
		ccs = sctx_tr->ccs;
		trb = XHCI_GADDR(sc, sctx_tr->ringaddr & ~0xFUL);
		DPRINTF(("doorbell, stream %u, ccs %lx, trb ccs %x\r\n",
		        streamid, ep_ctx->qwEpCtx2 & XHCI_TRB_3_CYCLE_BIT,
		        trb->dwTrb3 & XHCI_TRB_3_CYCLE_BIT));
	} else {
		if (streamid != 0) {
			DPRINTF(("pci_xhci: invalid stream %u\r\n", streamid));
			return;
		}
		ringaddr = devep->ep_ringaddr;
		ccs = devep->ep_ccs;
		trb = devep->ep_tr;
		DPRINTF(("doorbell, ccs %lx, trb ccs %x\r\n",
		        ep_ctx->qwEpCtx2 & XHCI_TRB_3_CYCLE_BIT,
		        trb->dwTrb3 & XHCI_TRB_3_CYCLE_BIT));
	}

	if (XHCI_TRB_3_TYPE_GET(trb->dwTrb3) == 0) {
		DPRINTF(("pci_xhci: ring %lx trb[%lx] EP %u is RESERVED?\r\n",
		        ep_ctx->qwEpCtx2, devep->ep_ringaddr, epid));
		return;
	}

	pci_xhci_handle_transfer(sc, dev, devep, ep_ctx, trb, slot, epid,
	                         ringaddr, ccs, streamid);
}