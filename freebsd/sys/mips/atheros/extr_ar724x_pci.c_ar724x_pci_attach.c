#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* rm_descr; void* rm_type; } ;
struct ar71xx_pci_softc {int /*<<< orphan*/  sc_ih; int /*<<< orphan*/ * sc_irq; TYPE_1__ sc_irq_rman; TYPE_1__ sc_mem_rman; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ AR71XX_PCI_IRQ_END ; 
 scalar_t__ AR71XX_PCI_IRQ_START ; 
 scalar_t__ AR71XX_PCI_MEM_BASE ; 
 scalar_t__ AR71XX_PCI_MEM_SIZE ; 
 int /*<<< orphan*/  AR724X_PCI_INTR_MASK ; 
 int /*<<< orphan*/  AR724X_PCI_INTR_STATUS ; 
 int /*<<< orphan*/  AR724X_RESET_PCIE ; 
 int /*<<< orphan*/  AR724X_RESET_PCIE_PHY ; 
 int /*<<< orphan*/  AR724X_RESET_PCIE_PHY_SERIAL ; 
 int /*<<< orphan*/  ATH_WRITE_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int ENXIO ; 
 int /*<<< orphan*/  INTR_TYPE_MISC ; 
 int PCIM_CMD_BACKTOBACK ; 
 int PCIM_CMD_BUSMASTEREN ; 
 int PCIM_CMD_MEMEN ; 
 int PCIM_CMD_MWRICEN ; 
 int PCIM_CMD_PERRESPEN ; 
 int PCIM_CMD_SERRESPEN ; 
 int /*<<< orphan*/  PCIR_COMMAND ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 void* RMAN_ARRAY ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  ar71xx_device_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar71xx_device_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar724x_pci_intr ; 
 scalar_t__ ar724x_pci_setup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar724x_pci_slot_fixup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar724x_pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ar71xx_pci_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 struct ar71xx_pci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ rman_init (TYPE_1__*) ; 
 scalar_t__ rman_manage_region (TYPE_1__*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int
ar724x_pci_attach(device_t dev)
{
	struct ar71xx_pci_softc *sc = device_get_softc(dev);
	int rid = 0;

	sc->sc_mem_rman.rm_type = RMAN_ARRAY;
	sc->sc_mem_rman.rm_descr = "ar724x PCI memory window";
	if (rman_init(&sc->sc_mem_rman) != 0 || 
	    rman_manage_region(&sc->sc_mem_rman, AR71XX_PCI_MEM_BASE, 
		AR71XX_PCI_MEM_BASE + AR71XX_PCI_MEM_SIZE - 1) != 0) {
		panic("ar724x_pci_attach: failed to set up I/O rman");
	}

	sc->sc_irq_rman.rm_type = RMAN_ARRAY;
	sc->sc_irq_rman.rm_descr = "ar724x PCI IRQs";
	if (rman_init(&sc->sc_irq_rman) != 0 ||
	    rman_manage_region(&sc->sc_irq_rman, AR71XX_PCI_IRQ_START, 
	        AR71XX_PCI_IRQ_END) != 0)
		panic("ar724x_pci_attach: failed to set up IRQ rman");

	/* Disable interrupts */
	ATH_WRITE_REG(AR724X_PCI_INTR_STATUS, 0);
	ATH_WRITE_REG(AR724X_PCI_INTR_MASK, 0);

	/* Hook up our interrupt handler. */
	if ((sc->sc_irq = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid,
	    RF_SHAREABLE | RF_ACTIVE)) == NULL) {
		device_printf(dev, "unable to allocate IRQ resource\n");
		return (ENXIO);
	}

	if ((bus_setup_intr(dev, sc->sc_irq, INTR_TYPE_MISC,
			    ar724x_pci_intr, NULL, sc, &sc->sc_ih))) {
		device_printf(dev, 
		    "WARNING: unable to register interrupt handler\n");
		return (ENXIO);
	}

	/* Reset PCIe core and PCIe PHY */
	ar71xx_device_stop(AR724X_RESET_PCIE);
	ar71xx_device_stop(AR724X_RESET_PCIE_PHY);
	ar71xx_device_stop(AR724X_RESET_PCIE_PHY_SERIAL);
	DELAY(100);

	ar71xx_device_start(AR724X_RESET_PCIE_PHY_SERIAL);
	DELAY(100);
	ar71xx_device_start(AR724X_RESET_PCIE_PHY);
	ar71xx_device_start(AR724X_RESET_PCIE);

	if (ar724x_pci_setup(dev))
		return (ENXIO);

#ifdef	AR71XX_ATH_EEPROM
	ar724x_pci_slot_fixup(dev);
#endif	/* AR71XX_ATH_EEPROM */

	/* Fixup internal PCI bridge */
	ar724x_pci_write_config(dev, 0, 0, 0, PCIR_COMMAND, 
            PCIM_CMD_BUSMASTEREN | PCIM_CMD_MEMEN 
	    | PCIM_CMD_SERRESPEN | PCIM_CMD_BACKTOBACK
	    | PCIM_CMD_PERRESPEN | PCIM_CMD_MWRICEN, 2);

	device_add_child(dev, "pci", -1);
	return (bus_generic_attach(dev));
}