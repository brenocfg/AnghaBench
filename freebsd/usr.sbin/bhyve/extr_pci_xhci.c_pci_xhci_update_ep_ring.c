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
typedef  int uint64_t ;
typedef  size_t uint32_t ;
struct xhci_endp_ctx {int qwEpCtx2; int /*<<< orphan*/  dwEpCtx0; } ;
struct pci_xhci_softc {int dummy; } ;
struct pci_xhci_dev_ep {int ep_ringaddr; int ep_ccs; int /*<<< orphan*/  ep_tr; TYPE_2__* ep_sctx; TYPE_1__* ep_sctx_trbs; } ;
struct pci_xhci_dev_emu {int dummy; } ;
struct TYPE_4__ {int qwSctx0; } ;
struct TYPE_3__ {int ringaddr; int ccs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 scalar_t__ XHCI_EPCTX_0_MAXP_STREAMS_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XHCI_GADDR (struct pci_xhci_softc*,int) ; 

__attribute__((used)) static void
pci_xhci_update_ep_ring(struct pci_xhci_softc *sc, struct pci_xhci_dev_emu *dev,
    struct pci_xhci_dev_ep *devep, struct xhci_endp_ctx *ep_ctx,
    uint32_t streamid, uint64_t ringaddr, int ccs)
{

	if (XHCI_EPCTX_0_MAXP_STREAMS_GET(ep_ctx->dwEpCtx0) != 0) {
		devep->ep_sctx[streamid].qwSctx0 = (ringaddr & ~0xFUL) |
		                                   (ccs & 0x1);

		devep->ep_sctx_trbs[streamid].ringaddr = ringaddr & ~0xFUL;
		devep->ep_sctx_trbs[streamid].ccs = ccs & 0x1;
		ep_ctx->qwEpCtx2 = (ep_ctx->qwEpCtx2 & ~0x1) | (ccs & 0x1);

		DPRINTF(("xhci update ep-ring stream %d, addr %lx\r\n",
		    streamid, devep->ep_sctx[streamid].qwSctx0));
	} else {
		devep->ep_ringaddr = ringaddr & ~0xFUL;
		devep->ep_ccs = ccs & 0x1;
		devep->ep_tr = XHCI_GADDR(sc, ringaddr & ~0xFUL);
		ep_ctx->qwEpCtx2 = (ringaddr & ~0xFUL) | (ccs & 0x1);

		DPRINTF(("xhci update ep-ring, addr %lx\r\n",
		    (devep->ep_ringaddr | devep->ep_ccs)));
	}
}