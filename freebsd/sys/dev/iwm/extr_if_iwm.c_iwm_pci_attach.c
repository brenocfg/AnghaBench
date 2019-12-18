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
typedef  int uint16_t ;
struct iwm_softc {int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_dmat; int /*<<< orphan*/ * sc_ih; int /*<<< orphan*/ * sc_irq; int /*<<< orphan*/ * sc_mem; int /*<<< orphan*/  sc_sh; int /*<<< orphan*/  sc_st; } ;
typedef  int /*<<< orphan*/  reg ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_NET ; 
 int PCIM_STATUS_INTxSTATE ; 
 int PCIR_BAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCIR_STATUS ; 
 int /*<<< orphan*/  PCI_CFG_RETRY_TIMEOUT ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct iwm_softc*,int /*<<< orphan*/ **) ; 
 struct iwm_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  iwm_intr ; 
 scalar_t__ pci_alloc_msi (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
iwm_pci_attach(device_t dev)
{
	struct iwm_softc *sc;
	int count, error, rid;
	uint16_t reg;

	sc = device_get_softc(dev);

	/* We disable the RETRY_TIMEOUT register (0x41) to keep
	 * PCI Tx retries from interfering with C3 CPU state */
	pci_write_config(dev, PCI_CFG_RETRY_TIMEOUT, 0x00, 1);

	/* Enable bus-mastering and hardware bug workaround. */
	pci_enable_busmaster(dev);
	reg = pci_read_config(dev, PCIR_STATUS, sizeof(reg));
	/* if !MSI */
	if (reg & PCIM_STATUS_INTxSTATE) {
		reg &= ~PCIM_STATUS_INTxSTATE;
	}
	pci_write_config(dev, PCIR_STATUS, reg, sizeof(reg));

	rid = PCIR_BAR(0);
	sc->sc_mem = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
	    RF_ACTIVE);
	if (sc->sc_mem == NULL) {
		device_printf(sc->sc_dev, "can't map mem space\n");
		return (ENXIO);
	}
	sc->sc_st = rman_get_bustag(sc->sc_mem);
	sc->sc_sh = rman_get_bushandle(sc->sc_mem);

	/* Install interrupt handler. */
	count = 1;
	rid = 0;
	if (pci_alloc_msi(dev, &count) == 0)
		rid = 1;
	sc->sc_irq = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid, RF_ACTIVE |
	    (rid != 0 ? 0 : RF_SHAREABLE));
	if (sc->sc_irq == NULL) {
		device_printf(dev, "can't map interrupt\n");
			return (ENXIO);
	}
	error = bus_setup_intr(dev, sc->sc_irq, INTR_TYPE_NET | INTR_MPSAFE,
	    NULL, iwm_intr, sc, &sc->sc_ih);
	if (sc->sc_ih == NULL) {
		device_printf(dev, "can't establish interrupt");
			return (ENXIO);
	}
	sc->sc_dmat = bus_get_dma_tag(sc->sc_dev);

	return (0);
}