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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct pci_xhci_softc {int dboff; int /*<<< orphan*/ * portregs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  XHCI_DB_SID_GET (int) ; 
 int /*<<< orphan*/  XHCI_DB_TARGET_GET (int) ; 
 scalar_t__ XHCI_HALTED (struct pci_xhci_softc*) ; 
 int /*<<< orphan*/  pci_xhci_complete_commands (struct pci_xhci_softc*) ; 
 int /*<<< orphan*/  pci_xhci_device_doorbell (struct pci_xhci_softc*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pci_xhci_dbregs_write(struct pci_xhci_softc *sc, uint64_t offset,
    uint64_t value)
{

	offset = (offset - sc->dboff) / sizeof(uint32_t);

	DPRINTF(("pci_xhci: doorbell write offset 0x%lx: 0x%lx\r\n",
	        offset, value));

	if (XHCI_HALTED(sc)) {
		DPRINTF(("pci_xhci: controller halted\r\n"));
		return;
	}

	if (offset == 0)
		pci_xhci_complete_commands(sc);
	else if (sc->portregs != NULL)
		pci_xhci_device_doorbell(sc, offset,
		   XHCI_DB_TARGET_GET(value), XHCI_DB_SID_GET(value));
}