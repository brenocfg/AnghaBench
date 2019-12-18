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
typedef  scalar_t__ uint8_t ;
typedef  void* uint32_t ;
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 scalar_t__ EHCI_CAPLENGTH (void*) ; 
 int /*<<< orphan*/  EHCI_CAPLEN_HCIVERSION ; 
 scalar_t__ EHCI_EC_LEGSUP ; 
 scalar_t__ EHCI_EECP_ID (void*) ; 
 scalar_t__ EHCI_EECP_NEXT (void*) ; 
 int /*<<< orphan*/  EHCI_HCCPARAMS ; 
 scalar_t__ EHCI_HCC_EECP (void*) ; 
 scalar_t__ EHCI_LEGSUP_BIOS_SEM ; 
 scalar_t__ EHCI_LEGSUP_OS_SEM ; 
 scalar_t__ EHCI_USBINTR ; 
 int PCIR_BAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 scalar_t__ bootverbose ; 
 struct resource* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 void* bus_read_4 (struct resource*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct resource*) ; 
 int /*<<< orphan*/  bus_write_4 (struct resource*,scalar_t__,int /*<<< orphan*/ ) ; 
 void* pci_read_config (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
ehci_early_takeover(device_t self)
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

	cparams = bus_read_4(res, EHCI_HCCPARAMS);

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
		if (bootverbose)
			printf("ehci early: "
			    "SMM active, request owner change\n");

		pci_write_config(self, eecp + EHCI_LEGSUP_OS_SEM, 1, 1);

		for (i = 0; (i < 100) && (bios_sem != 0); i++) {
			DELAY(1000);
			bios_sem = pci_read_config(self, eecp +
			    EHCI_LEGSUP_BIOS_SEM, 1);
		}

		if (bios_sem != 0) {
			if (bootverbose)
				printf("ehci early: "
				    "SMM does not respond\n");
		}
		/* Disable interrupts */
		offs = EHCI_CAPLENGTH(bus_read_4(res, EHCI_CAPLEN_HCIVERSION));
		bus_write_4(res, offs + EHCI_USBINTR, 0);
	}
	bus_release_resource(self, SYS_RES_MEMORY, rid, res);
}