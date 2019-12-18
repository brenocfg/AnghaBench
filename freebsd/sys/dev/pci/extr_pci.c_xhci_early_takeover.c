#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int PCIR_BAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 scalar_t__ XHCI_CAPLENGTH ; 
 int XHCI_HCS0_XECP (int) ; 
 int XHCI_HCSPARAMS0 ; 
 scalar_t__ XHCI_ID_USB_LEGACY ; 
 scalar_t__ XHCI_USBCMD ; 
 int XHCI_USBSTS ; 
 scalar_t__ XHCI_XECP_BIOS_SEM ; 
 scalar_t__ XHCI_XECP_ID (int) ; 
 int XHCI_XECP_NEXT (int) ; 
 scalar_t__ XHCI_XECP_OS_SEM ; 
 scalar_t__ bootverbose ; 
 struct resource* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int bus_read_1 (struct resource*,scalar_t__) ; 
 int bus_read_4 (struct resource*,int) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct resource*) ; 
 int /*<<< orphan*/  bus_write_1 (struct resource*,scalar_t__,int) ; 
 int /*<<< orphan*/  bus_write_4 (struct resource*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
xhci_early_takeover(device_t self)
{
	struct resource *res;
	uint32_t cparams;
	uint32_t eec;
	uint8_t eecp;
	uint8_t bios_sem;
	uint8_t offs;
	int rid;
	int i;

	rid = PCIR_BAR(0);
	res = bus_alloc_resource_any(self, SYS_RES_MEMORY, &rid, RF_ACTIVE);
	if (res == NULL)
		return;

	cparams = bus_read_4(res, XHCI_HCSPARAMS0);

	eec = -1;

	/* Synchronise with the BIOS if it owns the controller. */
	for (eecp = XHCI_HCS0_XECP(cparams) << 2; eecp != 0 && XHCI_XECP_NEXT(eec);
	    eecp += XHCI_XECP_NEXT(eec) << 2) {
		eec = bus_read_4(res, eecp);

		if (XHCI_XECP_ID(eec) != XHCI_ID_USB_LEGACY)
			continue;

		bios_sem = bus_read_1(res, eecp + XHCI_XECP_BIOS_SEM);
		if (bios_sem == 0)
			continue;

		if (bootverbose)
			printf("xhci early: "
			    "SMM active, request owner change\n");

		bus_write_1(res, eecp + XHCI_XECP_OS_SEM, 1);

		/* wait a maximum of 5 second */

		for (i = 0; (i < 5000) && (bios_sem != 0); i++) {
			DELAY(1000);
			bios_sem = bus_read_1(res, eecp +
			    XHCI_XECP_BIOS_SEM);
		}

		if (bios_sem != 0) {
			if (bootverbose)
				printf("xhci early: "
				    "SMM does not respond\n");
		}

		/* Disable interrupts */
		offs = bus_read_1(res, XHCI_CAPLENGTH);
		bus_write_4(res, offs + XHCI_USBCMD, 0);
		bus_read_4(res, offs + XHCI_USBSTS);
	}
	bus_release_resource(self, SYS_RES_MEMORY, rid, res);
}