#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  usb_error_t ;
typedef  int uint32_t ;
struct TYPE_7__ {int /*<<< orphan*/  bdev; } ;
struct TYPE_8__ {TYPE_1__ sc_bus; int /*<<< orphan*/  (* sc_vendor_post_reset ) (TYPE_2__*) ;} ;
typedef  TYPE_2__ ehci_softc_t ;

/* Variables and functions */
 int EHCI_CMD_HCRESET ; 
 int /*<<< orphan*/  EHCI_USBCMD ; 
 int EOREAD4 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EOWRITE4 (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  USB_ERR_IOERROR ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int hz ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  usb_pause_mtx (int /*<<< orphan*/ *,int) ; 

usb_error_t
ehci_reset(ehci_softc_t *sc)
{
	uint32_t hcr;
	int i;

	EOWRITE4(sc, EHCI_USBCMD, EHCI_CMD_HCRESET);
	for (i = 0; i < 100; i++) {
		usb_pause_mtx(NULL, hz / 128);
		hcr = EOREAD4(sc, EHCI_USBCMD) & EHCI_CMD_HCRESET;
		if (!hcr) {
			if (sc->sc_vendor_post_reset != NULL)
				sc->sc_vendor_post_reset(sc);
			return (0);
		}
	}
	device_printf(sc->sc_bus.bdev, "reset timeout\n");
	return (USB_ERR_IOERROR);
}