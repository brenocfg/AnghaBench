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
struct avr32dci_softc {int dummy; } ;
struct TYPE_2__ {int bEndpointAddress; } ;

/* Variables and functions */
 struct avr32dci_softc* AVR32_BUS2SC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVR32_EPTSETSTA (int) ; 
 int /*<<< orphan*/  AVR32_EPTSTA_FRCESTALL ; 
 int /*<<< orphan*/  AVR32_WRITE_4 (struct avr32dci_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINTFN (int,char*,struct usb_endpoint*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int UE_ADDR ; 
 int /*<<< orphan*/  USB_BUS_LOCK_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
avr32dci_set_stall(struct usb_device *udev,
    struct usb_endpoint *pipe, uint8_t *did_stall)
{
	struct avr32dci_softc *sc;
	uint8_t ep_no;

	USB_BUS_LOCK_ASSERT(udev->bus, MA_OWNED);

	DPRINTFN(5, "pipe=%p\n", pipe);

	sc = AVR32_BUS2SC(udev->bus);
	/* get endpoint number */
	ep_no = (pipe->edesc->bEndpointAddress & UE_ADDR);
	/* set stall */
	AVR32_WRITE_4(sc, AVR32_EPTSETSTA(ep_no), AVR32_EPTSTA_FRCESTALL);
}