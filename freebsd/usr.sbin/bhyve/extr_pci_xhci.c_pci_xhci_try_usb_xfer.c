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
typedef  int uint32_t ;
struct xhci_endp_ctx {int /*<<< orphan*/  dwEpCtx0; } ;
struct usb_data_xfer {size_t head; int /*<<< orphan*/ * data; } ;
struct pci_xhci_softc {int dummy; } ;
struct pci_xhci_dev_ep {struct usb_data_xfer* ep_xfer; } ;
struct pci_xhci_dev_emu {int /*<<< orphan*/  dev_sc; TYPE_1__* dev_ue; } ;
struct TYPE_2__ {int (* ue_data ) (int /*<<< orphan*/ ,struct usb_data_xfer*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FIELD_REPLACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ USB_DATA_GET_ERRCODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USB_DATA_XFER_LOCK (struct usb_data_xfer*) ; 
 int /*<<< orphan*/  USB_DATA_XFER_RESET (struct usb_data_xfer*) ; 
 int /*<<< orphan*/  USB_DATA_XFER_UNLOCK (struct usb_data_xfer*) ; 
 int USB_ERR_CANCELLED ; 
 scalar_t__ USB_NAK ; 
 int /*<<< orphan*/  USB_XFER_IN ; 
 int /*<<< orphan*/  USB_XFER_OUT ; 
 int /*<<< orphan*/  XHCI_ST_EPCTX_RUNNING ; 
 int XHCI_TRB_ERROR_SUCCESS ; 
 int /*<<< orphan*/  pci_xhci_assert_interrupt (struct pci_xhci_softc*) ; 
 int pci_xhci_xfer_complete (struct pci_xhci_softc*,struct usb_data_xfer*,int,int,int*) ; 
 int stub1 (int /*<<< orphan*/ ,struct usb_data_xfer*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
pci_xhci_try_usb_xfer(struct pci_xhci_softc *sc,
    struct pci_xhci_dev_emu *dev, struct pci_xhci_dev_ep *devep,
    struct xhci_endp_ctx *ep_ctx, uint32_t slot, uint32_t epid)
{
	struct usb_data_xfer *xfer;
	int		err;
	int		do_intr;

	ep_ctx->dwEpCtx0 = FIELD_REPLACE(
		    ep_ctx->dwEpCtx0, XHCI_ST_EPCTX_RUNNING, 0x7, 0);

	err = 0;
	do_intr = 0;

	xfer = devep->ep_xfer;
	USB_DATA_XFER_LOCK(xfer);

	/* outstanding requests queued up */
	if (dev->dev_ue->ue_data != NULL) {
		err = dev->dev_ue->ue_data(dev->dev_sc, xfer,
		            epid & 0x1 ? USB_XFER_IN : USB_XFER_OUT, epid/2);
		if (err == USB_ERR_CANCELLED) {
			if (USB_DATA_GET_ERRCODE(&xfer->data[xfer->head]) ==
			    USB_NAK)
				err = XHCI_TRB_ERROR_SUCCESS;
		} else {
			err = pci_xhci_xfer_complete(sc, xfer, slot, epid,
			                             &do_intr);
			if (err == XHCI_TRB_ERROR_SUCCESS && do_intr) {
				pci_xhci_assert_interrupt(sc);
			}


			/* XXX should not do it if error? */
			USB_DATA_XFER_RESET(xfer);
		}
	}

	USB_DATA_XFER_UNLOCK(xfer);


	return (err);
}