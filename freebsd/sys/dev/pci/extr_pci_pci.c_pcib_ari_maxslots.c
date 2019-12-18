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
struct pcib_softc {int flags; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int PCIB_ENABLE_ARI ; 
 int PCIE_ARI_SLOTMAX ; 
 struct pcib_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int pcib_maxslots (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pcib_ari_maxslots(device_t dev)
{
	struct pcib_softc *sc;

	sc = device_get_softc(dev);

	if (sc->flags & PCIB_ENABLE_ARI)
		return (PCIE_ARI_SLOTMAX);
	else
		return (pcib_maxslots(dev));
}