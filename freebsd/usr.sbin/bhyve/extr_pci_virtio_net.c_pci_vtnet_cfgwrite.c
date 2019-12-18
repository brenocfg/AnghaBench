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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/ * mac; } ;
struct pci_vtnet_softc {TYPE_1__ vsc_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
pci_vtnet_cfgwrite(void *vsc, int offset, int size, uint32_t value)
{
	struct pci_vtnet_softc *sc = vsc;
	void *ptr;

	if (offset < (int)sizeof(sc->vsc_config.mac)) {
		assert(offset + size <= (int)sizeof(sc->vsc_config.mac));
		/*
		 * The driver is allowed to change the MAC address
		 */
		ptr = &sc->vsc_config.mac[offset];
		memcpy(ptr, &value, size);
	} else {
		/* silently ignore other writes */
		DPRINTF(("vtnet: write to readonly reg %d\n\r", offset));
	}

	return (0);
}