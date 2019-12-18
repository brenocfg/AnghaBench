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
struct vga_pci_softc {int /*<<< orphan*/ * vga_msi_child; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int ENXIO ; 
 struct vga_pci_softc* device_get_softc (int /*<<< orphan*/ *) ; 
 int pci_release_msi (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
vga_pci_release_msi(device_t dev, device_t child)
{
	struct vga_pci_softc *sc;
	int error;

	sc = device_get_softc(dev);
	if (sc->vga_msi_child != child)
		return (ENXIO);
	error = pci_release_msi(dev);
	if (error == 0)
		sc->vga_msi_child = NULL;
	return (error);
}