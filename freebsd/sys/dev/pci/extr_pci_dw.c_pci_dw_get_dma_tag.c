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
struct pci_dw_softc {int /*<<< orphan*/  dmat; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bus_dma_tag_t ;

/* Variables and functions */
 struct pci_dw_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bus_dma_tag_t
pci_dw_get_dma_tag(device_t dev, device_t child)
{
	struct pci_dw_softc *sc;

	sc = device_get_softc(dev);
	return (sc->dmat);
}