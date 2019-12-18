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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  u_long ;
struct psycho_softc {scalar_t__ sc_half; int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int FILTER_HANDLED ; 
 scalar_t__ PCICTL_READ8 (struct psycho_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCR_AFA ; 
 int /*<<< orphan*/  PCR_AFS ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
psycho_pci_bus(void *arg)
{
	struct psycho_softc *sc = arg;
	uint64_t afar, afsr;

	afar = PCICTL_READ8(sc, PCR_AFA);
	afsr = PCICTL_READ8(sc, PCR_AFS);
	panic("%s: PCI bus %c error AFAR %#lx AFSR %#lx",
	    device_get_nameunit(sc->sc_dev), 'A' + sc->sc_half, (u_long)afar,
	    (u_long)afsr);
	return (FILTER_HANDLED);
}