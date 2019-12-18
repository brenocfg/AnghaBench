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
struct atmegadci_softc {int dummy; } ;
struct TYPE_2__ {int bEndpointAddress; } ;

/* Variables and functions */
 struct atmegadci_softc* ATMEGA_BUS2SC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATMEGA_UECONX ; 
 int ATMEGA_UECONX_EPEN ; 
 int ATMEGA_UECONX_STALLRQ ; 
 int /*<<< orphan*/  ATMEGA_UENUM ; 
 int /*<<< orphan*/  ATMEGA_WRITE_1 (struct atmegadci_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DPRINTFN (int,char*,struct usb_endpoint*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int UE_ADDR ; 
 int /*<<< orphan*/  USB_BUS_LOCK_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
atmegadci_set_stall(struct usb_device *udev,
    struct usb_endpoint *ep, uint8_t *did_stall)
{
	struct atmegadci_softc *sc;
	uint8_t ep_no;

	USB_BUS_LOCK_ASSERT(udev->bus, MA_OWNED);

	DPRINTFN(5, "endpoint=%p\n", ep);

	sc = ATMEGA_BUS2SC(udev->bus);
	/* get endpoint number */
	ep_no = (ep->edesc->bEndpointAddress & UE_ADDR);
	/* select endpoint number */
	ATMEGA_WRITE_1(sc, ATMEGA_UENUM, ep_no);
	/* set stall */
	ATMEGA_WRITE_1(sc, ATMEGA_UECONX,
	    ATMEGA_UECONX_EPEN |
	    ATMEGA_UECONX_STALLRQ);
}