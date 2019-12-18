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
typedef  int uint32_t ;
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  OHCI_ALL_INTRS ; 
 int /*<<< orphan*/  OHCI_COMMAND_STATUS ; 
 int /*<<< orphan*/  OHCI_CONTROL ; 
 int /*<<< orphan*/  OHCI_HCFS_RESET ; 
 int /*<<< orphan*/  OHCI_INTERRUPT_DISABLE ; 
 int OHCI_IR ; 
 int /*<<< orphan*/  OHCI_OCR ; 
 int PCIR_BAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 scalar_t__ bootverbose ; 
 struct resource* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int bus_read_4 (struct resource*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct resource*) ; 
 int /*<<< orphan*/  bus_write_4 (struct resource*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
ohci_early_takeover(device_t self)
{
	struct resource *res;
	uint32_t ctl;
	int rid;
	int i;

	rid = PCIR_BAR(0);
	res = bus_alloc_resource_any(self, SYS_RES_MEMORY, &rid, RF_ACTIVE);
	if (res == NULL)
		return;

	ctl = bus_read_4(res, OHCI_CONTROL);
	if (ctl & OHCI_IR) {
		if (bootverbose)
			printf("ohci early: "
			    "SMM active, request owner change\n");
		bus_write_4(res, OHCI_COMMAND_STATUS, OHCI_OCR);
		for (i = 0; (i < 100) && (ctl & OHCI_IR); i++) {
			DELAY(1000);
			ctl = bus_read_4(res, OHCI_CONTROL);
		}
		if (ctl & OHCI_IR) {
			if (bootverbose)
				printf("ohci early: "
				    "SMM does not respond, resetting\n");
			bus_write_4(res, OHCI_CONTROL, OHCI_HCFS_RESET);
		}
		/* Disable interrupts */
		bus_write_4(res, OHCI_INTERRUPT_DISABLE, OHCI_ALL_INTRS);
	}

	bus_release_resource(self, SYS_RES_MEMORY, rid, res);
}