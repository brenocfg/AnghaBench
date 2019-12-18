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
struct pci_softc {int /*<<< orphan*/  sc_dma_tag; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bus_dma_tag_t ;

/* Variables and functions */
 struct pci_softc* device_get_softc (int /*<<< orphan*/ ) ; 

bus_dma_tag_t
pci_get_dma_tag(device_t bus, device_t dev)
{
	struct pci_softc *sc = device_get_softc(bus);

	return (sc->sc_dma_tag);
}