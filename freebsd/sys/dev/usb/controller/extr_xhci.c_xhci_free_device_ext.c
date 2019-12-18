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
typedef  size_t uint8_t ;
struct TYPE_4__ {TYPE_1__* devs; } ;
struct xhci_softc {TYPE_2__ sc_hw; } ;
struct usb_device {size_t controller_slot_id; int /*<<< orphan*/  bus; } ;
struct TYPE_3__ {int /*<<< orphan*/ * endpoint_pc; int /*<<< orphan*/  input_pc; int /*<<< orphan*/  device_pc; } ;

/* Variables and functions */
 struct xhci_softc* XHCI_BUS2SC (int /*<<< orphan*/ ) ; 
 size_t XHCI_MAX_ENDPOINTS ; 
 int /*<<< orphan*/  usb_pc_free_mem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xhci_set_slot_pointer (struct xhci_softc*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xhci_free_device_ext(struct usb_device *udev)
{
	struct xhci_softc *sc = XHCI_BUS2SC(udev->bus);
	uint8_t index;
	uint8_t i;

	index = udev->controller_slot_id;
	xhci_set_slot_pointer(sc, index, 0);

	usb_pc_free_mem(&sc->sc_hw.devs[index].device_pc);
	usb_pc_free_mem(&sc->sc_hw.devs[index].input_pc);
	for (i = 0; i != XHCI_MAX_ENDPOINTS; i++)
		usb_pc_free_mem(&sc->sc_hw.devs[index].endpoint_pc[i]);
}