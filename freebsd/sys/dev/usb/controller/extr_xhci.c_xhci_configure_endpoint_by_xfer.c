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
typedef  size_t usb_stream_t ;
typedef  int /*<<< orphan*/  usb_error_t ;
typedef  scalar_t__ uint64_t ;
struct xhci_trb {int dummy; } ;
struct xhci_endpoint_ext {int /*<<< orphan*/  page_cache; TYPE_1__* trb; scalar_t__ physaddr; } ;
struct usb_xfer {TYPE_3__* endpoint; int /*<<< orphan*/  max_frame_size; int /*<<< orphan*/  max_packet_size; int /*<<< orphan*/  max_packet_count; int /*<<< orphan*/  interval; TYPE_2__* xroot; } ;
struct usb_endpoint_ss_comp_descriptor {int /*<<< orphan*/  bmAttributes; } ;
struct TYPE_6__ {int /*<<< orphan*/  ep_mode; int /*<<< orphan*/  edesc; struct usb_endpoint_ss_comp_descriptor* ecomp; } ;
struct TYPE_5__ {int /*<<< orphan*/  udev; } ;
struct TYPE_4__ {scalar_t__ dwTrb3; scalar_t__ dwTrb2; int /*<<< orphan*/  qwTrb0; } ;

/* Variables and functions */
 int UE_GET_SS_ISO_MULT (int /*<<< orphan*/ ) ; 
 size_t XHCI_MAX_STREAMS ; 
 size_t XHCI_MAX_TRANSFERS ; 
 scalar_t__ XHCI_SCTX_0_SCT_SEC_TR_RING ; 
 int /*<<< orphan*/  htole64 (scalar_t__) ; 
 int /*<<< orphan*/  usb_pc_cpu_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_get_fps_shift (struct usb_xfer*) ; 
 int /*<<< orphan*/  xhci_configure_endpoint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xhci_endpoint_ext*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct xhci_endpoint_ext* xhci_get_endpoint_ext (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static usb_error_t
xhci_configure_endpoint_by_xfer(struct usb_xfer *xfer)
{
	struct xhci_endpoint_ext *pepext;
	struct usb_endpoint_ss_comp_descriptor *ecomp;
	usb_stream_t x;

	pepext = xhci_get_endpoint_ext(xfer->xroot->udev,
	    xfer->endpoint->edesc);

	ecomp = xfer->endpoint->ecomp;

	for (x = 0; x != XHCI_MAX_STREAMS; x++) {
		uint64_t temp;

		/* halt any transfers */
		pepext->trb[x * XHCI_MAX_TRANSFERS].dwTrb3 = 0;

		/* compute start of TRB ring for stream "x" */
		temp = pepext->physaddr +
		    (x * XHCI_MAX_TRANSFERS * sizeof(struct xhci_trb)) +
		    XHCI_SCTX_0_SCT_SEC_TR_RING;

		/* make tree structure */
		pepext->trb[(XHCI_MAX_TRANSFERS *
		    XHCI_MAX_STREAMS) + x].qwTrb0 = htole64(temp);

		/* reserved fields */
		pepext->trb[(XHCI_MAX_TRANSFERS *
                    XHCI_MAX_STREAMS) + x].dwTrb2 = 0;
		pepext->trb[(XHCI_MAX_TRANSFERS *
		    XHCI_MAX_STREAMS) + x].dwTrb3 = 0;
	}
	usb_pc_cpu_flush(pepext->page_cache);

	return (xhci_configure_endpoint(xfer->xroot->udev,
	    xfer->endpoint->edesc, pepext,
	    xfer->interval, xfer->max_packet_count,
	    (ecomp != NULL) ? UE_GET_SS_ISO_MULT(ecomp->bmAttributes) + 1 : 1,
	    usbd_xfer_get_fps_shift(xfer), xfer->max_packet_size,
	    xfer->max_frame_size, xfer->endpoint->ep_mode));
}