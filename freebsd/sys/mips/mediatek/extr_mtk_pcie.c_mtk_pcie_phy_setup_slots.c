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
typedef  int uint32_t ;
struct mtk_pci_softc {scalar_t__ socid; int pcie_link_status; int num_slots; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  MTK_PCIE_BAR0SETUP (int) ; 
 int /*<<< orphan*/  MTK_PCIE_BAR1SETUP (int) ; 
 int /*<<< orphan*/  MTK_PCIE_CLASS (int) ; 
 int /*<<< orphan*/  MTK_PCIE_IMBASEBAR0 (int) ; 
 int /*<<< orphan*/  MTK_PCIE_STATUS (int) ; 
 int /*<<< orphan*/  MTK_PCI_PCIENA ; 
 scalar_t__ MTK_SOC_MT7620A ; 
 scalar_t__ MTK_SOC_MT7621 ; 
 scalar_t__ MTK_SOC_MT7628 ; 
 scalar_t__ MTK_SOC_MT7688 ; 
 int MT_READ32 (struct mtk_pci_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MT_WRITE32 (struct mtk_pci_softc*,int /*<<< orphan*/ ,int) ; 
 int PCIR_IOBASEH_1 ; 
 int PCIR_IOBASEL_1 ; 
 int PCIR_IOLIMITH_1 ; 
 int PCIR_IOLIMITL_1 ; 
 int PCIR_MEMBASE_1 ; 
 int PCIR_MEMLIMIT_1 ; 
 int PCIR_PMBASEH_1 ; 
 int PCIR_PMBASEL_1 ; 
 int PCIR_PMLIMITH_1 ; 
 int PCIR_PMLIMITL_1 ; 
 struct mtk_pci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int mtk_pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mtk_pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void
mtk_pcie_phy_setup_slots(device_t dev)
{
	struct mtk_pci_softc *sc = device_get_softc(dev);
	uint32_t bar0_val, val;
	int i;

	/* Disable all PCIe interrupts */
	MT_WRITE32(sc, MTK_PCI_PCIENA, 0);

	/* Default bar0_val is 64M, enabled */
	bar0_val = 0x03FF0001;

	/* But we override it to 2G, enabled for some SoCs */
	if (sc->socid == MTK_SOC_MT7620A || sc->socid == MTK_SOC_MT7628 ||
	    sc->socid == MTK_SOC_MT7688 || sc->socid == MTK_SOC_MT7621)
		bar0_val = 0x7FFF0001;

	/* We still don't know which slots have linked up */
	sc->pcie_link_status = 0;

	/* XXX: I am not sure if this delay is really necessary */
	DELAY(500000);

	/*
	 * See which slots have links and mark them.
	 * Set up all slots' BARs and make them look like PCIe bridges.
	 */
	for (i = 0; i < sc->num_slots; i++) {
		/* If slot has link - mark it */
		if (MT_READ32(sc, MTK_PCIE_STATUS(i)) & 1)
			sc->pcie_link_status |= (1<<i);
		else
			continue;

		/* Generic slot configuration follows */

		/* We enable BAR0 */
		MT_WRITE32(sc, MTK_PCIE_BAR0SETUP(i), bar0_val);
		/* and disable BAR1 */
		MT_WRITE32(sc, MTK_PCIE_BAR1SETUP(i), 0);
		/* Internal memory base has no offset */
		MT_WRITE32(sc, MTK_PCIE_IMBASEBAR0(i), 0);
		/* We're a PCIe bridge */
		MT_WRITE32(sc, MTK_PCIE_CLASS(i), 0x06040001);

		val = mtk_pci_read_config(dev, 0, i, 0, 0x4, 4);
		mtk_pci_write_config(dev, 0, i, 0, 0x4, val | 0x4, 4);
		val = mtk_pci_read_config(dev, 0, i, 0, 0x70c, 4);
		val &= ~(0xff << 8);
		val |= (0x50 << 8);
		mtk_pci_write_config(dev, 0, i, 0, 0x70c, val, 4);

		mtk_pci_write_config(dev, 0, i, 0, PCIR_IOBASEL_1, 0xff, 1);
		mtk_pci_write_config(dev, 0, i, 0, PCIR_IOBASEH_1, 0xffff, 2);
		mtk_pci_write_config(dev, 0, i, 0, PCIR_IOLIMITL_1, 0, 1);
		mtk_pci_write_config(dev, 0, i, 0, PCIR_IOLIMITH_1, 0, 2);
		mtk_pci_write_config(dev, 0, i, 0, PCIR_MEMBASE_1, 0xffff, 2);
		mtk_pci_write_config(dev, 0, i, 0, PCIR_MEMLIMIT_1, 0, 2);
		mtk_pci_write_config(dev, 0, i, 0, PCIR_PMBASEL_1, 0xffff, 2);
		mtk_pci_write_config(dev, 0, i, 0, PCIR_PMBASEH_1, 0xffffffff,
		    4);
		mtk_pci_write_config(dev, 0, i, 0, PCIR_PMLIMITL_1, 0, 2);
		mtk_pci_write_config(dev, 0, i, 0, PCIR_PMLIMITH_1, 0, 4);
	}
}