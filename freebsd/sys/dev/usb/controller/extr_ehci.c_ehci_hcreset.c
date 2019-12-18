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
struct TYPE_8__ {TYPE_1__ sc_bus; } ;
typedef  TYPE_2__ ehci_softc_t ;

/* Variables and functions */
 int EHCI_STS_HCH ; 
 int /*<<< orphan*/  EHCI_USBCMD ; 
 int /*<<< orphan*/  EHCI_USBSTS ; 
 int EOREAD4 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EOWRITE4 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ehci_reset (TYPE_2__*) ; 
 int hz ; 
 int /*<<< orphan*/  usb_pause_mtx (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static usb_error_t
ehci_hcreset(ehci_softc_t *sc)
{
	uint32_t hcr;
	int i;

	EOWRITE4(sc, EHCI_USBCMD, 0);	/* Halt controller */
	for (i = 0; i < 100; i++) {
		usb_pause_mtx(NULL, hz / 128);
		hcr = EOREAD4(sc, EHCI_USBSTS) & EHCI_STS_HCH;
		if (hcr)
			break;
	}
	if (!hcr)
		/*
                 * Fall through and try reset anyway even though
                 * Table 2-9 in the EHCI spec says this will result
                 * in undefined behavior.
                 */
		device_printf(sc->sc_bus.bdev, "stop timeout\n");

	return (ehci_reset(sc));
}