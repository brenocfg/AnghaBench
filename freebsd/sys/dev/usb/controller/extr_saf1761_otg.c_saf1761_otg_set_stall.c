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
typedef  int uint8_t ;
struct usb_endpoint {TYPE_2__* edesc; } ;
struct TYPE_3__ {scalar_t__ usb_mode; } ;
struct usb_device {int /*<<< orphan*/  bus; TYPE_1__ flags; } ;
struct saf1761_otg_softc {int /*<<< orphan*/  sc_bus; } ;
struct TYPE_4__ {int bEndpointAddress; int bmAttributes; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*,struct usb_endpoint*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 struct saf1761_otg_softc* SAF1761_OTG_BUS2SC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAF1761_WRITE_LE_4 (struct saf1761_otg_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SOTG_CTRL_FUNC ; 
 int SOTG_CTRL_FUNC_STALL ; 
 int /*<<< orphan*/  SOTG_EP_INDEX ; 
 int SOTG_EP_INDEX_DIR_IN ; 
 int SOTG_EP_INDEX_DIR_OUT ; 
 int SOTG_EP_INDEX_ENDP_INDEX_SHIFT ; 
 int UE_ADDR ; 
 int UE_CONTROL ; 
 int UE_DIR_IN ; 
 int UE_DIR_OUT ; 
 int UE_XFERTYPE ; 
 int /*<<< orphan*/  USB_BUS_LOCK_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_BUS_SPIN_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USB_BUS_SPIN_UNLOCK (int /*<<< orphan*/ *) ; 
 scalar_t__ USB_MODE_DEVICE ; 

__attribute__((used)) static void
saf1761_otg_set_stall(struct usb_device *udev,
    struct usb_endpoint *ep, uint8_t *did_stall)
{
	struct saf1761_otg_softc *sc;
	uint8_t ep_no;
	uint8_t ep_type;
	uint8_t ep_dir;

	USB_BUS_LOCK_ASSERT(udev->bus, MA_OWNED);

	/* check mode */
	if (udev->flags.usb_mode != USB_MODE_DEVICE) {
		/* not supported */
		return;
	}

	DPRINTFN(5, "endpoint=%p\n", ep);

	/* set STALL bit */
	sc = SAF1761_OTG_BUS2SC(udev->bus);

	ep_no = (ep->edesc->bEndpointAddress & UE_ADDR);
	ep_dir = (ep->edesc->bEndpointAddress & (UE_DIR_IN | UE_DIR_OUT));
	ep_type = (ep->edesc->bmAttributes & UE_XFERTYPE);

	if (ep_type == UE_CONTROL) {
		/* should not happen */
		return;
	}
	USB_BUS_SPIN_LOCK(&sc->sc_bus);

	/* select the correct endpoint */
	SAF1761_WRITE_LE_4(sc, SOTG_EP_INDEX,
	    (ep_no << SOTG_EP_INDEX_ENDP_INDEX_SHIFT) |
	    ((ep_dir == UE_DIR_IN) ? SOTG_EP_INDEX_DIR_IN :
	    SOTG_EP_INDEX_DIR_OUT));

	/* set stall */
	SAF1761_WRITE_LE_4(sc, SOTG_CTRL_FUNC, SOTG_CTRL_FUNC_STALL);

	USB_BUS_SPIN_UNLOCK(&sc->sc_bus);
}