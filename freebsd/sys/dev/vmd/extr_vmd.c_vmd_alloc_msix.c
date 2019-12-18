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
struct vmd_softc {int vmd_flags; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int PCIB_ALLOC_MSIX (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int PCIB_DISABLE_MSIX ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct vmd_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vmd_alloc_msix(device_t pcib, device_t dev, int *irq)
{
	struct vmd_softc *sc = device_get_softc(pcib);
	device_t bus;
	int ret;

	if (sc->vmd_flags & PCIB_DISABLE_MSIX)
		return (ENXIO);
	bus = device_get_parent(pcib);
	ret = PCIB_ALLOC_MSIX(device_get_parent(bus), dev, irq);
        return (ret);
}