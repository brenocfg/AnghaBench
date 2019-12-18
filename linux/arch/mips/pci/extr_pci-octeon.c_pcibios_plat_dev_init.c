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
typedef  int uint16_t ;
struct pci_dev {scalar_t__ subordinate; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_BRIDGE_CONTROL ; 
 int PCI_BRIDGE_CTL_PARITY ; 
 int PCI_BRIDGE_CTL_SERR ; 
 int /*<<< orphan*/  PCI_CACHE_LINE_SIZE ; 
 int /*<<< orphan*/  PCI_COMMAND ; 
 int PCI_COMMAND_PARITY ; 
 int PCI_COMMAND_SERR ; 
 scalar_t__ PCI_ERR_CAP ; 
 int PCI_ERR_CAP_ECRC_CHKC ; 
 int PCI_ERR_CAP_ECRC_CHKE ; 
 int PCI_ERR_CAP_ECRC_GENC ; 
 int PCI_ERR_CAP_ECRC_GENE ; 
 scalar_t__ PCI_ERR_COR_MASK ; 
 scalar_t__ PCI_ERR_COR_STATUS ; 
 int PCI_ERR_ROOT_CMD_COR_EN ; 
 int PCI_ERR_ROOT_CMD_FATAL_EN ; 
 int PCI_ERR_ROOT_CMD_NONFATAL_EN ; 
 scalar_t__ PCI_ERR_ROOT_COMMAND ; 
 scalar_t__ PCI_ERR_ROOT_STATUS ; 
 scalar_t__ PCI_ERR_UNCOR_MASK ; 
 scalar_t__ PCI_ERR_UNCOR_STATUS ; 
 int /*<<< orphan*/  PCI_EXP_DEVCTL ; 
 int PCI_EXP_DEVCTL_CERE ; 
 int PCI_EXP_DEVCTL_FERE ; 
 int PCI_EXP_DEVCTL_NFERE ; 
 int PCI_EXP_DEVCTL_URRE ; 
 int /*<<< orphan*/  PCI_EXT_CAP_ID_ERR ; 
 int /*<<< orphan*/  PCI_LATENCY_TIMER ; 
 int /*<<< orphan*/  PCI_SEC_LATENCY_TIMER ; 
 int pci_find_ext_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,scalar_t__,int*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,scalar_t__,int) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcie_capability_set_word (struct pci_dev*,int /*<<< orphan*/ ,int) ; 

int pcibios_plat_dev_init(struct pci_dev *dev)
{
	uint16_t config;
	uint32_t dconfig;
	int pos;
	/*
	 * Force the Cache line setting to 64 bytes. The standard
	 * Linux bus scan doesn't seem to set it. Octeon really has
	 * 128 byte lines, but Intel bridges get really upset if you
	 * try and set values above 64 bytes. Value is specified in
	 * 32bit words.
	 */
	pci_write_config_byte(dev, PCI_CACHE_LINE_SIZE, 64 / 4);
	/* Set latency timers for all devices */
	pci_write_config_byte(dev, PCI_LATENCY_TIMER, 64);

	/* Enable reporting System errors and parity errors on all devices */
	/* Enable parity checking and error reporting */
	pci_read_config_word(dev, PCI_COMMAND, &config);
	config |= PCI_COMMAND_PARITY | PCI_COMMAND_SERR;
	pci_write_config_word(dev, PCI_COMMAND, config);

	if (dev->subordinate) {
		/* Set latency timers on sub bridges */
		pci_write_config_byte(dev, PCI_SEC_LATENCY_TIMER, 64);
		/* More bridge error detection */
		pci_read_config_word(dev, PCI_BRIDGE_CONTROL, &config);
		config |= PCI_BRIDGE_CTL_PARITY | PCI_BRIDGE_CTL_SERR;
		pci_write_config_word(dev, PCI_BRIDGE_CONTROL, config);
	}

	/* Enable the PCIe normal error reporting */
	config = PCI_EXP_DEVCTL_CERE; /* Correctable Error Reporting */
	config |= PCI_EXP_DEVCTL_NFERE; /* Non-Fatal Error Reporting */
	config |= PCI_EXP_DEVCTL_FERE;	/* Fatal Error Reporting */
	config |= PCI_EXP_DEVCTL_URRE;	/* Unsupported Request */
	pcie_capability_set_word(dev, PCI_EXP_DEVCTL, config);

	/* Find the Advanced Error Reporting capability */
	pos = pci_find_ext_capability(dev, PCI_EXT_CAP_ID_ERR);
	if (pos) {
		/* Clear Uncorrectable Error Status */
		pci_read_config_dword(dev, pos + PCI_ERR_UNCOR_STATUS,
				      &dconfig);
		pci_write_config_dword(dev, pos + PCI_ERR_UNCOR_STATUS,
				       dconfig);
		/* Enable reporting of all uncorrectable errors */
		/* Uncorrectable Error Mask - turned on bits disable errors */
		pci_write_config_dword(dev, pos + PCI_ERR_UNCOR_MASK, 0);
		/*
		 * Leave severity at HW default. This only controls if
		 * errors are reported as uncorrectable or
		 * correctable, not if the error is reported.
		 */
		/* PCI_ERR_UNCOR_SEVER - Uncorrectable Error Severity */
		/* Clear Correctable Error Status */
		pci_read_config_dword(dev, pos + PCI_ERR_COR_STATUS, &dconfig);
		pci_write_config_dword(dev, pos + PCI_ERR_COR_STATUS, dconfig);
		/* Enable reporting of all correctable errors */
		/* Correctable Error Mask - turned on bits disable errors */
		pci_write_config_dword(dev, pos + PCI_ERR_COR_MASK, 0);
		/* Advanced Error Capabilities */
		pci_read_config_dword(dev, pos + PCI_ERR_CAP, &dconfig);
		/* ECRC Generation Enable */
		if (config & PCI_ERR_CAP_ECRC_GENC)
			config |= PCI_ERR_CAP_ECRC_GENE;
		/* ECRC Check Enable */
		if (config & PCI_ERR_CAP_ECRC_CHKC)
			config |= PCI_ERR_CAP_ECRC_CHKE;
		pci_write_config_dword(dev, pos + PCI_ERR_CAP, dconfig);
		/* PCI_ERR_HEADER_LOG - Header Log Register (16 bytes) */
		/* Report all errors to the root complex */
		pci_write_config_dword(dev, pos + PCI_ERR_ROOT_COMMAND,
				       PCI_ERR_ROOT_CMD_COR_EN |
				       PCI_ERR_ROOT_CMD_NONFATAL_EN |
				       PCI_ERR_ROOT_CMD_FATAL_EN);
		/* Clear the Root status register */
		pci_read_config_dword(dev, pos + PCI_ERR_ROOT_STATUS, &dconfig);
		pci_write_config_dword(dev, pos + PCI_ERR_ROOT_STATUS, dconfig);
	}

	return 0;
}