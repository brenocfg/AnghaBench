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
struct schizo_softc {scalar_t__ sc_mode; scalar_t__ sc_half; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int PCI_SLOTMAX ; 
 scalar_t__ SCHIZO_MODE_SCZ ; 
 struct schizo_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
schizo_maxslots(device_t dev)
{
	struct schizo_softc *sc;

	sc = device_get_softc(dev);
	if (sc->sc_mode == SCHIZO_MODE_SCZ)
		return (sc->sc_half == 0 ? 4 : 6);

	/* XXX: is this correct? */
	return (PCI_SLOTMAX);
}