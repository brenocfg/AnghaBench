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
struct ncr53c9x_softc {int dummy; } ;
struct esp_pci_softc {int /*<<< orphan*/ * sc_res; int /*<<< orphan*/  sc_pdmat; int /*<<< orphan*/  sc_xferdmat; int /*<<< orphan*/  sc_xferdmam; int /*<<< orphan*/  sc_ih; int /*<<< orphan*/  sc_dev; struct ncr53c9x_softc sc_ncr53c9x; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 size_t ESP_PCI_RES_INTR ; 
 int /*<<< orphan*/  NCR_LOCK_DESTROY (struct ncr53c9x_softc*) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct esp_pci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_pci_res_spec ; 
 int ncr53c9x_detach (struct ncr53c9x_softc*) ; 

__attribute__((used)) static int
esp_pci_detach(device_t dev)
{
	struct ncr53c9x_softc *sc;
	struct esp_pci_softc *esc;
	int error;

	esc = device_get_softc(dev);
	sc = &esc->sc_ncr53c9x;

	bus_teardown_intr(esc->sc_dev, esc->sc_res[ESP_PCI_RES_INTR],
	    esc->sc_ih);
	error = ncr53c9x_detach(sc);
	if (error != 0)
		return (error);
	bus_dmamap_destroy(esc->sc_xferdmat, esc->sc_xferdmam);
	bus_dma_tag_destroy(esc->sc_xferdmat);
	bus_dma_tag_destroy(esc->sc_pdmat);
	bus_release_resources(dev, esp_pci_res_spec, esc->sc_res);
	NCR_LOCK_DESTROY(sc);

	return (0);
}