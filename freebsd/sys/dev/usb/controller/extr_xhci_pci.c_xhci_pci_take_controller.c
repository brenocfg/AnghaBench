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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_2__ {int /*<<< orphan*/  bdev; } ;
struct xhci_softc {TYPE_1__ sc_bus; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int XHCI_HCS0_XECP (int) ; 
 int XHCI_HCSPARAMS0 ; 
 scalar_t__ XHCI_ID_USB_LEGACY ; 
 scalar_t__ XHCI_XECP_BIOS_SEM ; 
 scalar_t__ XHCI_XECP_ID (int) ; 
 int XHCI_XECP_NEXT (int) ; 
 scalar_t__ XHCI_XECP_OS_SEM ; 
 scalar_t__ XREAD1 (struct xhci_softc*,int /*<<< orphan*/ ,scalar_t__) ; 
 int XREAD4 (struct xhci_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XWRITE1 (struct xhci_softc*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  capa ; 
 struct xhci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int hz ; 
 int /*<<< orphan*/  usb_pause_mtx (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
xhci_pci_take_controller(device_t self)
{
	struct xhci_softc *sc = device_get_softc(self);
	uint32_t cparams;
	uint32_t eecp;
	uint32_t eec;
	uint16_t to;
	uint8_t bios_sem;

	cparams = XREAD4(sc, capa, XHCI_HCSPARAMS0);

	eec = -1;

	/* Synchronise with the BIOS if it owns the controller. */
	for (eecp = XHCI_HCS0_XECP(cparams) << 2; eecp != 0 && XHCI_XECP_NEXT(eec);
	    eecp += XHCI_XECP_NEXT(eec) << 2) {
		eec = XREAD4(sc, capa, eecp);

		if (XHCI_XECP_ID(eec) != XHCI_ID_USB_LEGACY)
			continue;
		bios_sem = XREAD1(sc, capa, eecp +
		    XHCI_XECP_BIOS_SEM);
		if (bios_sem == 0)
			continue;
		device_printf(sc->sc_bus.bdev, "waiting for BIOS "
		    "to give up control\n");
		XWRITE1(sc, capa, eecp +
		    XHCI_XECP_OS_SEM, 1);
		to = 500;
		while (1) {
			bios_sem = XREAD1(sc, capa, eecp +
			    XHCI_XECP_BIOS_SEM);
			if (bios_sem == 0)
				break;

			if (--to == 0) {
				device_printf(sc->sc_bus.bdev,
				    "timed out waiting for BIOS\n");
				break;
			}
			usb_pause_mtx(NULL, hz / 100);	/* wait 10ms */
		}
	}
	return (0);
}