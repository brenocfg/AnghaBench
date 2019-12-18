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
struct malo_softc {int malo_invalid; int /*<<< orphan*/  malo_dmat; } ;
struct malo_pci_softc {scalar_t__ malo_msi; int /*<<< orphan*/ * malo_res_mem; int /*<<< orphan*/  malo_mem_spec; int /*<<< orphan*/ * malo_res_irq; int /*<<< orphan*/  malo_irq_spec; int /*<<< orphan*/ * malo_intrhand; struct malo_softc malo_sc; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int MALO_MSI_MESSAGES ; 
 int /*<<< orphan*/  bus_child_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct malo_pci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malo_detach (struct malo_softc*) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
malo_pci_detach(device_t dev)
{
	int i;
	struct malo_pci_softc *psc = device_get_softc(dev);
	struct malo_softc *sc = &psc->malo_sc;

	/* check if device was removed */
	sc->malo_invalid = !bus_child_present(dev);

	malo_detach(sc);

	bus_generic_detach(dev);

	if (psc->malo_msi == 0)
		bus_teardown_intr(dev, psc->malo_res_irq[0],
		    psc->malo_intrhand[0]);
	else {
		for (i = 0; i < MALO_MSI_MESSAGES; i++)
			bus_teardown_intr(dev, psc->malo_res_irq[i],
			    psc->malo_intrhand[i]);

		pci_release_msi(dev);
	}

	bus_release_resources(dev, psc->malo_irq_spec, psc->malo_res_irq);
	bus_dma_tag_destroy(sc->malo_dmat);
	bus_release_resources(dev, psc->malo_mem_spec, psc->malo_res_mem);

	return (0);
}