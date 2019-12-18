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
typedef  int uint32_t ;
struct usb_xfer {int interval; int fps_shift; int max_packet_count; int nframes; void** td_start; struct octusb_td** qh_start; TYPE_4__* xroot; TYPE_3__* endpoint; int /*<<< orphan*/  address; int /*<<< orphan*/  endpointno; int /*<<< orphan*/  max_packet_size; int /*<<< orphan*/  max_frame_size; } ;
struct usb_setup_params {int hc_max_packet_size; int hc_max_packet_count; int hc_max_frame_size; scalar_t__ buf; void* err; struct usb_xfer* curr_xfer; TYPE_1__* udev; } ;
struct usb_page_search {struct octusb_td* buffer; int /*<<< orphan*/  physaddr; } ;
struct usb_page_cache {int dummy; } ;
struct usb_device {struct usb_device* parent_hub; int /*<<< orphan*/  port_index; } ;
struct octusb_td {int ep_type; int ep_interval; int ep_mult; void* obj_next; struct octusb_td* qh; struct octusb_td* fixup_buf; struct usb_page_cache* fixup_pc; int /*<<< orphan*/  fixup_phys; int /*<<< orphan*/  hs_hub_port; int /*<<< orphan*/  hs_hub_addr; int /*<<< orphan*/  root_port_index; int /*<<< orphan*/  dev_speed; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  ep_num; int /*<<< orphan*/  max_packet_size; int /*<<< orphan*/  max_frame_size; void* sc; } ;
struct octusb_softc {int dummy; } ;
struct octusb_qh {int ep_type; int ep_interval; int ep_mult; void* obj_next; struct octusb_qh* qh; struct octusb_qh* fixup_buf; struct usb_page_cache* fixup_pc; int /*<<< orphan*/  fixup_phys; int /*<<< orphan*/  hs_hub_port; int /*<<< orphan*/  hs_hub_addr; int /*<<< orphan*/  root_port_index; int /*<<< orphan*/  dev_speed; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  ep_num; int /*<<< orphan*/  max_packet_size; int /*<<< orphan*/  max_frame_size; void* sc; } ;
struct TYPE_10__ {int /*<<< orphan*/  hs_port_no; int /*<<< orphan*/  hs_hub_addr; struct usb_device* parent_hub; int /*<<< orphan*/  port_index; } ;
struct TYPE_9__ {TYPE_5__* udev; int /*<<< orphan*/  bus; } ;
struct TYPE_8__ {TYPE_2__* edesc; } ;
struct TYPE_7__ {int bmAttributes; } ;
struct TYPE_6__ {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 void* OCTUSB_BUS2SC (int /*<<< orphan*/ ) ; 
 int OCTUSB_MAX_FIXUP ; 
#define  UE_INTERRUPT 129 
#define  UE_ISOCHRONOUS 128 
 int UE_XFERTYPE ; 
 void* USB_ERR_NOMEM ; 
 int USB_HOST_ALIGN ; 
 int /*<<< orphan*/  USB_SPEED_HIGH ; 
 int /*<<< orphan*/  usbd_get_page (struct usb_page_cache*,int /*<<< orphan*/ ,struct usb_page_search*) ; 
 int /*<<< orphan*/  usbd_get_speed (TYPE_5__*) ; 
 int /*<<< orphan*/  usbd_transfer_setup_sub (struct usb_setup_params*) ; 
 scalar_t__ usbd_transfer_setup_sub_malloc (struct usb_setup_params*,struct usb_page_cache**,int,int,int) ; 

__attribute__((used)) static void
octusb_xfer_setup(struct usb_setup_params *parm)
{
	struct usb_page_search page_info;
	struct usb_page_cache *pc;
	struct octusb_softc *sc;
	struct octusb_qh *qh;
	struct usb_xfer *xfer;
	struct usb_device *hub;
	void *last_obj;
	uint32_t n;
	uint32_t ntd;

	sc = OCTUSB_BUS2SC(parm->udev->bus);
	xfer = parm->curr_xfer;
	qh = NULL;

	/*
	 * NOTE: This driver does not use any of the parameters that
	 * are computed from the following values. Just set some
	 * reasonable dummies:
	 */

	parm->hc_max_packet_size = 0x400;
	parm->hc_max_packet_count = 3;
	parm->hc_max_frame_size = 0xC00;

	usbd_transfer_setup_sub(parm);

	if (parm->err)
		return;

	/* Allocate a queue head */

	if (usbd_transfer_setup_sub_malloc(
	    parm, &pc, sizeof(struct octusb_qh),
	    USB_HOST_ALIGN, 1)) {
		parm->err = USB_ERR_NOMEM;
		return;
	}
	if (parm->buf) {
		usbd_get_page(pc, 0, &page_info);

		qh = page_info.buffer;

		/* fill out QH */

		qh->sc = OCTUSB_BUS2SC(xfer->xroot->bus);
		qh->max_frame_size = xfer->max_frame_size;
		qh->max_packet_size = xfer->max_packet_size;
		qh->ep_num = xfer->endpointno;
		qh->ep_type = xfer->endpoint->edesc->bmAttributes;
		qh->dev_addr = xfer->address;
		qh->dev_speed = usbd_get_speed(xfer->xroot->udev);
		qh->root_port_index = xfer->xroot->udev->port_index;
		/* We need Octeon USB HUB's port index, not the local port */
		hub = xfer->xroot->udev->parent_hub;
		while(hub && hub->parent_hub) {
			qh->root_port_index = hub->port_index;
			hub = hub->parent_hub;
		}

		switch (xfer->endpoint->edesc->bmAttributes & UE_XFERTYPE) {
		case UE_INTERRUPT:
			if (usbd_get_speed(xfer->xroot->udev) == USB_SPEED_HIGH)
				qh->ep_interval = xfer->interval * 8;
			else
				qh->ep_interval = xfer->interval * 1;
			break;
		case UE_ISOCHRONOUS:
			qh->ep_interval = 1 << xfer->fps_shift;
			break;
		default:
			qh->ep_interval = 0;
			break;
		}

		qh->ep_mult = xfer->max_packet_count & 3;
		qh->hs_hub_addr = xfer->xroot->udev->hs_hub_addr;
		qh->hs_hub_port = xfer->xroot->udev->hs_port_no;
	}
	xfer->qh_start[0] = qh;

	/* Allocate a fixup buffer */

	if (usbd_transfer_setup_sub_malloc(
	    parm, &pc, OCTUSB_MAX_FIXUP,
	    OCTUSB_MAX_FIXUP, 1)) {
		parm->err = USB_ERR_NOMEM;
		return;
	}
	if (parm->buf) {
		usbd_get_page(pc, 0, &page_info);

		qh->fixup_phys = page_info.physaddr;
		qh->fixup_pc = pc;
		qh->fixup_buf = page_info.buffer;
	}
	/* Allocate transfer descriptors */

	last_obj = NULL;

	ntd = xfer->nframes + 1 /* STATUS */ + 1 /* SYNC */ ;

	if (usbd_transfer_setup_sub_malloc(
	    parm, &pc, sizeof(struct octusb_td),
	    USB_HOST_ALIGN, ntd)) {
		parm->err = USB_ERR_NOMEM;
		return;
	}
	if (parm->buf) {
		for (n = 0; n != ntd; n++) {
			struct octusb_td *td;

			usbd_get_page(pc + n, 0, &page_info);

			td = page_info.buffer;

			td->qh = qh;
			td->obj_next = last_obj;

			last_obj = td;
		}
	}
	xfer->td_start[0] = last_obj;
}