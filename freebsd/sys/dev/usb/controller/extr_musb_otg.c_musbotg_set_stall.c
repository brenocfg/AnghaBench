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
typedef  int uint8_t ;
struct usb_endpoint {TYPE_1__* edesc; } ;
struct usb_device {int /*<<< orphan*/  bus; } ;
struct musbotg_softc {int dummy; } ;
struct TYPE_2__ {int bEndpointAddress; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*,struct usb_endpoint*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int MUSB2_MASK_CSRL_RXSENDSTALL ; 
 int MUSB2_MASK_CSRL_TXSENDSTALL ; 
 int /*<<< orphan*/  MUSB2_REG_EPINDEX ; 
 int /*<<< orphan*/  MUSB2_REG_RXCSRL ; 
 int /*<<< orphan*/  MUSB2_REG_TXCSRL ; 
 int /*<<< orphan*/  MUSB2_WRITE_1 (struct musbotg_softc*,int /*<<< orphan*/ ,int) ; 
 struct musbotg_softc* MUSBOTG_BUS2SC (int /*<<< orphan*/ ) ; 
 int UE_ADDR ; 
 int UE_DIR_IN ; 
 int /*<<< orphan*/  USB_BUS_LOCK_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
musbotg_set_stall(struct usb_device *udev,
    struct usb_endpoint *ep, uint8_t *did_stall)
{
	struct musbotg_softc *sc;
	uint8_t ep_no;

	USB_BUS_LOCK_ASSERT(udev->bus, MA_OWNED);

	DPRINTFN(4, "endpoint=%p\n", ep);

	/* set FORCESTALL */
	sc = MUSBOTG_BUS2SC(udev->bus);

	ep_no = (ep->edesc->bEndpointAddress & UE_ADDR);

	/* select endpoint */
	MUSB2_WRITE_1(sc, MUSB2_REG_EPINDEX, ep_no);

	if (ep->edesc->bEndpointAddress & UE_DIR_IN) {
		MUSB2_WRITE_1(sc, MUSB2_REG_TXCSRL,
		    MUSB2_MASK_CSRL_TXSENDSTALL);
	} else {
		MUSB2_WRITE_1(sc, MUSB2_REG_RXCSRL,
		    MUSB2_MASK_CSRL_RXSENDSTALL);
	}
}