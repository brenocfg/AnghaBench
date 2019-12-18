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
 int /*<<< orphan*/  DELAY (int) ; 
 int ENXIO ; 
 int VIA_PCI_ACLINK_C00_READY ; 
 int /*<<< orphan*/  VIA_PCI_ACLINK_CTRL ; 
 int VIA_PCI_ACLINK_DESIRED ; 
 int VIA_PCI_ACLINK_EN ; 
 int VIA_PCI_ACLINK_NRST ; 
 int /*<<< orphan*/  VIA_PCI_ACLINK_STAT ; 
 int VIA_PCI_ACLINK_SYNC ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
via_chip_init(device_t dev)
{
	uint32_t data, cnt;

	/* Wake up and reset AC97 if necessary */
	data = pci_read_config(dev, VIA_PCI_ACLINK_STAT, 1);

	if ((data & VIA_PCI_ACLINK_C00_READY) == 0) {
		/* Cold reset per ac97r2.3 spec (page 95) */
		/* Assert low */
		pci_write_config(dev, VIA_PCI_ACLINK_CTRL,
		    VIA_PCI_ACLINK_EN, 1);
		/* Wait T_rst_low */
		DELAY(100);
		/* Assert high */
		pci_write_config(dev, VIA_PCI_ACLINK_CTRL,
		    VIA_PCI_ACLINK_EN | VIA_PCI_ACLINK_NRST, 1);
		/* Wait T_rst2clk */
		DELAY(5);
		/* Assert low */
		pci_write_config(dev, VIA_PCI_ACLINK_CTRL,
		    VIA_PCI_ACLINK_EN, 1);
	} else {
		/* Warm reset */
		/* Force no sync */
		pci_write_config(dev, VIA_PCI_ACLINK_CTRL,
		    VIA_PCI_ACLINK_EN, 1);
		DELAY(100);
		/* Sync */
		pci_write_config(dev, VIA_PCI_ACLINK_CTRL,
		    VIA_PCI_ACLINK_EN | VIA_PCI_ACLINK_SYNC, 1);
		/* Wait T_sync_high */
		DELAY(5);
		/* Force no sync */
		pci_write_config(dev, VIA_PCI_ACLINK_CTRL,
		    VIA_PCI_ACLINK_EN, 1);
		/* Wait T_sync2clk */
		DELAY(5);
	}

	/* Power everything up */
	pci_write_config(dev, VIA_PCI_ACLINK_CTRL, VIA_PCI_ACLINK_DESIRED, 1);

	/* Wait for codec to become ready (largest reported delay 310ms) */
	for (cnt = 0; cnt < 2000; cnt++) {
		data = pci_read_config(dev, VIA_PCI_ACLINK_STAT, 1);
		if (data & VIA_PCI_ACLINK_C00_READY)
			return (0);
		DELAY(5000);
	}
	device_printf(dev, "primary codec not ready (cnt = 0x%02x)\n", cnt);
	return (ENXIO);
}