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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ AR71XX_SOC_AR7240 ; 
 scalar_t__ AR71XX_SOC_AR7241 ; 
 scalar_t__ AR71XX_SOC_AR7242 ; 
 int /*<<< orphan*/  AR724X_PCI_APP ; 
 int AR724X_PCI_APP_LTSSM_ENABLE ; 
 int /*<<< orphan*/  AR724X_PCI_CRP_BASE ; 
 int /*<<< orphan*/  AR724X_PCI_RESET ; 
 int AR724X_PCI_RESET_LINK_UP ; 
 int ATH_READ_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATH_WRITE_REG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int ENXIO ; 
 int PCIM_CMD_BACKTOBACK ; 
 int PCIM_CMD_BUSMASTEREN ; 
 int PCIM_CMD_MEMEN ; 
 int PCIM_CMD_MWRICEN ; 
 int PCIM_CMD_PERRESPEN ; 
 int PCIM_CMD_SERRESPEN ; 
 int PCIR_COMMAND ; 
 scalar_t__ ar71xx_soc ; 
 int /*<<< orphan*/  ar724x_pci_write (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
ar724x_pci_setup(device_t dev)
{
	uint32_t reg;

	/* setup COMMAND register */
	reg = PCIM_CMD_BUSMASTEREN | PCIM_CMD_MEMEN | PCIM_CMD_SERRESPEN |
	    PCIM_CMD_BACKTOBACK | PCIM_CMD_PERRESPEN | PCIM_CMD_MWRICEN;

	ar724x_pci_write(AR724X_PCI_CRP_BASE, PCIR_COMMAND, reg, 2);
	ar724x_pci_write(AR724X_PCI_CRP_BASE, 0x20, 0x1ff01000, 4);
	ar724x_pci_write(AR724X_PCI_CRP_BASE, 0x24, 0x1ff01000, 4);

	reg = ATH_READ_REG(AR724X_PCI_RESET);
	if (reg != 0x7) {
		DELAY(100000);
		ATH_WRITE_REG(AR724X_PCI_RESET, 0);
		DELAY(100);
		ATH_WRITE_REG(AR724X_PCI_RESET, 4);
		DELAY(100000);
	}

	if (ar71xx_soc == AR71XX_SOC_AR7240)
		reg = AR724X_PCI_APP_LTSSM_ENABLE;
	else
		reg = 0x1ffc1;
	ATH_WRITE_REG(AR724X_PCI_APP, reg);
	/* Flush write */
	(void) ATH_READ_REG(AR724X_PCI_APP);

	DELAY(1000);

	reg = ATH_READ_REG(AR724X_PCI_RESET);
	if ((reg & AR724X_PCI_RESET_LINK_UP) == 0) {
		device_printf(dev, "no PCIe controller found\n");
		return (ENXIO);
	}

	if (ar71xx_soc == AR71XX_SOC_AR7241 ||
	    ar71xx_soc == AR71XX_SOC_AR7242) {
		reg = ATH_READ_REG(AR724X_PCI_APP);
		reg |= (1 << 16);
		ATH_WRITE_REG(AR724X_PCI_APP, reg);
	}

	return (0);
}