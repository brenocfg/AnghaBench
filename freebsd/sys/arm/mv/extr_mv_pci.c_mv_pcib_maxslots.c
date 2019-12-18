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
struct mv_pcib_softc {scalar_t__ sc_type; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ MV_TYPE_PCI ; 
 int PCI_SLOTMAX ; 
 struct mv_pcib_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mv_pcib_maxslots(device_t dev)
{
	struct mv_pcib_softc *sc = device_get_softc(dev);

	return ((sc->sc_type != MV_TYPE_PCI) ? 1 : PCI_SLOTMAX);
}