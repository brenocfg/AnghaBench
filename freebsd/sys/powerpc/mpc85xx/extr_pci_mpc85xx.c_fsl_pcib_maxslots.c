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
struct fsl_pcib_softc {scalar_t__ sc_pcie; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int PCI_SLOTMAX ; 
 struct fsl_pcib_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
fsl_pcib_maxslots(device_t dev)
{
	struct fsl_pcib_softc *sc = device_get_softc(dev);

	return ((sc->sc_pcie) ? 0 : PCI_SLOTMAX);
}