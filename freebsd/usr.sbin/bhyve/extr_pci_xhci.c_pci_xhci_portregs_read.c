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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct pci_xhci_softc {TYPE_1__* portregs; } ;
struct TYPE_2__ {int portsc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int XHCI_MAX_DEVS ; 
 int XHCI_PS_SPEED_SET (int) ; 

__attribute__((used)) static uint64_t
pci_xhci_portregs_read(struct pci_xhci_softc *sc, uint64_t offset)
{
	int port;
	uint32_t *p;

	if (sc->portregs == NULL)
		return (0);

	port = (offset - 0x3F0) / 0x10;

	if (port > XHCI_MAX_DEVS) {
		DPRINTF(("pci_xhci: portregs_read port %d >= XHCI_MAX_DEVS\r\n",
		    port));

		/* return default value for unused port */
		return (XHCI_PS_SPEED_SET(3));
	}

	offset = (offset - 0x3F0) % 0x10;

	p = &sc->portregs[port].portsc;
	p += offset / sizeof(uint32_t);

	DPRINTF(("pci_xhci: portregs read offset 0x%lx port %u -> 0x%x\r\n",
	        offset, port, *p));

	return (*p);
}