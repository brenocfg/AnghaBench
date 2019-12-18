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
typedef  int /*<<< orphan*/  uint16_t ;
struct jme_softc {int /*<<< orphan*/  jme_dev; int /*<<< orphan*/  jme_chip_rev; int /*<<< orphan*/  jme_phyaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMCR_PDOWN ; 
 int CHIPMODE_REVFM (int /*<<< orphan*/ ) ; 
 int CSR_READ_4 (struct jme_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct jme_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  JME_PCI_PE1 ; 
 int /*<<< orphan*/  JME_PHYPOWDN ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int PE1_GIGA_PDOWN_DIS ; 
 int PE1_GIGA_PDOWN_MASK ; 
 int /*<<< orphan*/  jme_miibus_readreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jme_miibus_writereg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
jme_phy_up(struct jme_softc *sc)
{
	uint32_t reg;
	uint16_t bmcr;

	bmcr = jme_miibus_readreg(sc->jme_dev, sc->jme_phyaddr, MII_BMCR);
	bmcr &= ~BMCR_PDOWN;
	jme_miibus_writereg(sc->jme_dev, sc->jme_phyaddr, MII_BMCR, bmcr);
	if (CHIPMODE_REVFM(sc->jme_chip_rev) >= 5) {
		reg = CSR_READ_4(sc, JME_PHYPOWDN);
		reg &= ~0x0000000F;
		CSR_WRITE_4(sc, JME_PHYPOWDN, reg);
		reg = pci_read_config(sc->jme_dev, JME_PCI_PE1, 4);
		reg &= ~PE1_GIGA_PDOWN_MASK;
		reg |= PE1_GIGA_PDOWN_DIS;
		pci_write_config(sc->jme_dev, JME_PCI_PE1, reg, 4);
	}
}