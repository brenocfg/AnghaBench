#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  void* uint32_t ;
typedef  int uint16_t ;
struct TYPE_5__ {int /*<<< orphan*/  bdev; } ;
struct TYPE_6__ {TYPE_1__ sc_bus; } ;
typedef  TYPE_2__ ehci_softc_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ EHCI_EC_LEGSUP ; 
 scalar_t__ EHCI_EECP_ID (void*) ; 
 scalar_t__ EHCI_EECP_NEXT (void*) ; 
 int /*<<< orphan*/  EHCI_HCCPARAMS ; 
 scalar_t__ EHCI_HCC_EECP (void*) ; 
 scalar_t__ EHCI_LEGSUP_BIOS_SEM ; 
 scalar_t__ EHCI_LEGSUP_OS_SEM ; 
 void* EREAD4 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int hz ; 
 void* pci_read_config (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 int /*<<< orphan*/  usb_pause_mtx (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
ehci_pci_take_controller(device_t self)
{
	ehci_softc_t *sc = device_get_softc(self);
	uint32_t cparams;
	uint32_t eec;
	uint16_t to;
	uint8_t eecp;
	uint8_t bios_sem;

	cparams = EREAD4(sc, EHCI_HCCPARAMS);

	/* Synchronise with the BIOS if it owns the controller. */
	for (eecp = EHCI_HCC_EECP(cparams); eecp != 0;
	    eecp = EHCI_EECP_NEXT(eec)) {
		eec = pci_read_config(self, eecp, 4);
		if (EHCI_EECP_ID(eec) != EHCI_EC_LEGSUP) {
			continue;
		}
		bios_sem = pci_read_config(self, eecp +
		    EHCI_LEGSUP_BIOS_SEM, 1);
		if (bios_sem == 0) {
			continue;
		}
		device_printf(sc->sc_bus.bdev, "waiting for BIOS "
		    "to give up control\n");
		pci_write_config(self, eecp +
		    EHCI_LEGSUP_OS_SEM, 1, 1);
		to = 500;
		while (1) {
			bios_sem = pci_read_config(self, eecp +
			    EHCI_LEGSUP_BIOS_SEM, 1);
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