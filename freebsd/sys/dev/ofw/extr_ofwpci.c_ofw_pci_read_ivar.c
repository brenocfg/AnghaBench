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
struct ofw_pci_softc {uintptr_t sc_pci_domain; uintptr_t sc_bus; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOENT ; 
#define  PCIB_IVAR_BUS 129 
#define  PCIB_IVAR_DOMAIN 128 
 struct ofw_pci_softc* device_get_softc (int /*<<< orphan*/ ) ; 

int
ofw_pci_read_ivar(device_t dev, device_t child, int which, uintptr_t *result)
{
	struct ofw_pci_softc *sc;

	sc = device_get_softc(dev);

	switch (which) {
	case PCIB_IVAR_DOMAIN:
		*result = sc->sc_pci_domain;
		return (0);
	case PCIB_IVAR_BUS:
		*result = sc->sc_bus;
		return (0);
	default:
		break;
	}

	return (ENOENT);
}