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
struct xhci_endp_ctx {int qwEpCtx2; int /*<<< orphan*/  dwEpCtx0; } ;
struct xhci_dev_ctx {struct xhci_endp_ctx* ctx_ep; } ;
struct usb_data_xfer {int dummy; } ;
struct pci_xhci_trb_ring {int dummy; } ;
struct pci_xhci_dev_ep {int ep_ringaddr; int /*<<< orphan*/ * ep_xfer; int /*<<< orphan*/  ep_ccs; void* ep_tr; TYPE_1__* ep_sctx; TYPE_2__* ep_sctx_trbs; } ;
struct pci_xhci_dev_emu {int /*<<< orphan*/  xsc; struct pci_xhci_dev_ep* eps; struct xhci_dev_ctx* dev_ctx; } ;
struct TYPE_4__ {int ringaddr; int /*<<< orphan*/  ccs; } ;
struct TYPE_3__ {int qwSctx0; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  USB_DATA_XFER_INIT (int /*<<< orphan*/ *) ; 
 int XHCI_EPCTX_0_MAXP_STREAMS_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XHCI_EPCTX_2_DCS_GET (int) ; 
 int XHCI_EPCTX_2_TR_DQ_PTR_MASK ; 
 void* XHCI_GADDR (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XHCI_SCTX_0_DCS_GET (int) ; 
 int XHCI_SCTX_0_TR_DQ_PTR_MASK ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_2__* calloc (int,int) ; 
 int /*<<< orphan*/ * malloc (int) ; 

__attribute__((used)) static void
pci_xhci_init_ep(struct pci_xhci_dev_emu *dev, int epid)
{
	struct xhci_dev_ctx    *dev_ctx;
	struct pci_xhci_dev_ep *devep;
	struct xhci_endp_ctx   *ep_ctx;
	uint32_t	pstreams;
	int		i;

	dev_ctx = dev->dev_ctx;
	ep_ctx = &dev_ctx->ctx_ep[epid];
	devep = &dev->eps[epid];
	pstreams = XHCI_EPCTX_0_MAXP_STREAMS_GET(ep_ctx->dwEpCtx0);
	if (pstreams > 0) {
		DPRINTF(("init_ep %d with pstreams %d\r\n", epid, pstreams));
		assert(devep->ep_sctx_trbs == NULL);

		devep->ep_sctx = XHCI_GADDR(dev->xsc, ep_ctx->qwEpCtx2 &
		                            XHCI_EPCTX_2_TR_DQ_PTR_MASK);
		devep->ep_sctx_trbs = calloc(pstreams,
		                      sizeof(struct pci_xhci_trb_ring));
		for (i = 0; i < pstreams; i++) {
			devep->ep_sctx_trbs[i].ringaddr =
			                         devep->ep_sctx[i].qwSctx0 &
			                         XHCI_SCTX_0_TR_DQ_PTR_MASK;
			devep->ep_sctx_trbs[i].ccs =
			     XHCI_SCTX_0_DCS_GET(devep->ep_sctx[i].qwSctx0);
		}
	} else {
		DPRINTF(("init_ep %d with no pstreams\r\n", epid));
		devep->ep_ringaddr = ep_ctx->qwEpCtx2 &
		                     XHCI_EPCTX_2_TR_DQ_PTR_MASK;
		devep->ep_ccs = XHCI_EPCTX_2_DCS_GET(ep_ctx->qwEpCtx2);
		devep->ep_tr = XHCI_GADDR(dev->xsc, devep->ep_ringaddr);
		DPRINTF(("init_ep tr DCS %x\r\n", devep->ep_ccs));
	}

	if (devep->ep_xfer == NULL) {
		devep->ep_xfer = malloc(sizeof(struct usb_data_xfer));
		USB_DATA_XFER_INIT(devep->ep_xfer);
	}
}