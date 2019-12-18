#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  usb_error_t ;
typedef  size_t uint8_t ;
typedef  int uint32_t ;
struct TYPE_7__ {TYPE_2__* devs; } ;
struct xhci_softc {TYPE_3__ sc_hw; int /*<<< orphan*/  sc_exit_lat_max; } ;
struct TYPE_8__ {int /*<<< orphan*/  dwSctx3; int /*<<< orphan*/  dwSctx2; int /*<<< orphan*/  dwSctx1; int /*<<< orphan*/  dwSctx0; } ;
struct xhci_input_dev_ctx {TYPE_4__ ctx_slot; } ;
struct usb_page_search {struct xhci_input_dev_ctx* buffer; } ;
struct usb_page_cache {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  bDeviceProtocol; } ;
struct usb_device {size_t controller_slot_id; size_t depth; int port_no; int speed; int /*<<< orphan*/  hs_port_no; struct usb_device* parent_hs_hub; TYPE_1__ ddesc; struct usb_device* parent_hub; int /*<<< orphan*/  bus; } ;
struct TYPE_6__ {scalar_t__ nports; int /*<<< orphan*/  tt; int /*<<< orphan*/  state; scalar_t__ context_num; struct usb_page_cache input_pc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,...) ; 
 int /*<<< orphan*/  UDPROTO_HSHUBMTT ; 
#define  USB_SPEED_FULL 133 
#define  USB_SPEED_HIGH 132 
#define  USB_SPEED_LOW 131 
#define  USB_SPEED_SUPER 130 
 struct xhci_softc* XHCI_BUS2SC (int /*<<< orphan*/ ) ; 
 int XHCI_SCTX_0_CTX_NUM_SET (scalar_t__) ; 
 int XHCI_SCTX_0_HUB_SET (int) ; 
 int XHCI_SCTX_0_MTT_SET (int) ; 
 int XHCI_SCTX_0_ROUTE_SET (int) ; 
 int XHCI_SCTX_0_SPEED_SET (int) ; 
 int XHCI_SCTX_1_MAX_EL_SET (int /*<<< orphan*/ ) ; 
 int XHCI_SCTX_1_NUM_PORTS_SET (scalar_t__) ; 
 int XHCI_SCTX_1_RH_PORT_SET (int) ; 
 int XHCI_SCTX_2_IRQ_TARGET_SET (int /*<<< orphan*/ ) ; 
 int XHCI_SCTX_2_TT_HUB_SID_SET (size_t) ; 
 int XHCI_SCTX_2_TT_PORT_NUM_SET (int /*<<< orphan*/ ) ; 
 int XHCI_SCTX_2_TT_THINK_TIME_SET (int /*<<< orphan*/ ) ; 
 int XHCI_SCTX_3_DEV_ADDR_SET (int /*<<< orphan*/ ) ; 
 int XHCI_SCTX_3_SLOT_STATE_SET (int /*<<< orphan*/ ) ; 
#define  XHCI_ST_ADDRESSED 129 
#define  XHCI_ST_CONFIGURED 128 
 int /*<<< orphan*/  usb_pc_cpu_flush (struct usb_page_cache*) ; 
 int /*<<< orphan*/  usbd_get_page (struct usb_page_cache*,int /*<<< orphan*/ ,struct usb_page_search*) ; 
 int /*<<< orphan*/  xhci_ctx_set_le32 (struct xhci_softc*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  xhci_dump_device (struct xhci_softc*,TYPE_4__*) ; 

__attribute__((used)) static usb_error_t
xhci_configure_device(struct usb_device *udev)
{
	struct xhci_softc *sc = XHCI_BUS2SC(udev->bus);
	struct usb_page_search buf_inp;
	struct usb_page_cache *pcinp;
	struct xhci_input_dev_ctx *pinp;
	struct usb_device *hubdev;
	uint32_t temp;
	uint32_t route;
	uint32_t rh_port;
	uint8_t is_hub;
	uint8_t index;
	uint8_t depth;

	index = udev->controller_slot_id;

	DPRINTF("index=%u\n", index);

	pcinp = &sc->sc_hw.devs[index].input_pc;

	usbd_get_page(pcinp, 0, &buf_inp);

	pinp = buf_inp.buffer;

	rh_port = 0;
	route = 0;

	/* figure out route string and root HUB port number */

	for (hubdev = udev; hubdev != NULL; hubdev = hubdev->parent_hub) {

		if (hubdev->parent_hub == NULL)
			break;

		depth = hubdev->parent_hub->depth;

		/*
		 * NOTE: HS/FS/LS devices and the SS root HUB can have
		 * more than 15 ports
		 */

		rh_port = hubdev->port_no;

		if (depth == 0)
			break;

		if (rh_port > 15)
			rh_port = 15;

		if (depth < 6)
			route |= rh_port << (4 * (depth - 1));
	}

	DPRINTF("Route=0x%08x\n", route);

	temp = XHCI_SCTX_0_ROUTE_SET(route) |
	    XHCI_SCTX_0_CTX_NUM_SET(
	    sc->sc_hw.devs[index].context_num + 1);

	switch (udev->speed) {
	case USB_SPEED_LOW:
		temp |= XHCI_SCTX_0_SPEED_SET(2);
		if (udev->parent_hs_hub != NULL &&
		    udev->parent_hs_hub->ddesc.bDeviceProtocol ==
		    UDPROTO_HSHUBMTT) {
			DPRINTF("Device inherits MTT\n");
			temp |= XHCI_SCTX_0_MTT_SET(1);
		}
		break;
	case USB_SPEED_HIGH:
		temp |= XHCI_SCTX_0_SPEED_SET(3);
		if (sc->sc_hw.devs[index].nports != 0 &&
		    udev->ddesc.bDeviceProtocol == UDPROTO_HSHUBMTT) {
			DPRINTF("HUB supports MTT\n");
			temp |= XHCI_SCTX_0_MTT_SET(1);
		}
		break;
	case USB_SPEED_FULL:
		temp |= XHCI_SCTX_0_SPEED_SET(1);
		if (udev->parent_hs_hub != NULL &&
		    udev->parent_hs_hub->ddesc.bDeviceProtocol ==
		    UDPROTO_HSHUBMTT) {
			DPRINTF("Device inherits MTT\n");
			temp |= XHCI_SCTX_0_MTT_SET(1);
		}
		break;
	default:
		temp |= XHCI_SCTX_0_SPEED_SET(4);
		break;
	}

	is_hub = sc->sc_hw.devs[index].nports != 0 &&
	    (udev->speed == USB_SPEED_SUPER ||
	    udev->speed == USB_SPEED_HIGH);

	if (is_hub)
		temp |= XHCI_SCTX_0_HUB_SET(1);

	xhci_ctx_set_le32(sc, &pinp->ctx_slot.dwSctx0, temp);

	temp = XHCI_SCTX_1_RH_PORT_SET(rh_port);

	if (is_hub) {
		temp |= XHCI_SCTX_1_NUM_PORTS_SET(
		    sc->sc_hw.devs[index].nports);
	}

	switch (udev->speed) {
	case USB_SPEED_SUPER:
		switch (sc->sc_hw.devs[index].state) {
		case XHCI_ST_ADDRESSED:
		case XHCI_ST_CONFIGURED:
			/* enable power save */
			temp |= XHCI_SCTX_1_MAX_EL_SET(sc->sc_exit_lat_max);
			break;
		default:
			/* disable power save */
			break;
		}
		break;
	default:
		break;
	}

	xhci_ctx_set_le32(sc, &pinp->ctx_slot.dwSctx1, temp);

	temp = XHCI_SCTX_2_IRQ_TARGET_SET(0);

	if (is_hub) {
		temp |= XHCI_SCTX_2_TT_THINK_TIME_SET(
		    sc->sc_hw.devs[index].tt);
	}

	hubdev = udev->parent_hs_hub;

	/* check if we should activate the transaction translator */
	switch (udev->speed) {
	case USB_SPEED_FULL:
	case USB_SPEED_LOW:
		if (hubdev != NULL) {
			temp |= XHCI_SCTX_2_TT_HUB_SID_SET(
			    hubdev->controller_slot_id);
			temp |= XHCI_SCTX_2_TT_PORT_NUM_SET(
			    udev->hs_port_no);
		}
		break;
	default:
		break;
	}

	xhci_ctx_set_le32(sc, &pinp->ctx_slot.dwSctx2, temp);

	/*
	 * These fields should be initialized to zero, according to
	 * XHCI section 6.2.2 - slot context:
	 */
	temp = XHCI_SCTX_3_DEV_ADDR_SET(0) |
	    XHCI_SCTX_3_SLOT_STATE_SET(0);

	xhci_ctx_set_le32(sc, &pinp->ctx_slot.dwSctx3, temp);

#ifdef USB_DEBUG
	xhci_dump_device(sc, &pinp->ctx_slot);
#endif
	usb_pc_cpu_flush(pcinp);

	return (0);		/* success */
}