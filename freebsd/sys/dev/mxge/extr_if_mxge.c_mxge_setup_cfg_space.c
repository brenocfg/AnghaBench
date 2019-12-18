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
typedef  int uint16_t ;
struct TYPE_3__ {int link_width; int pectl; int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ mxge_softc_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCIY_EXPRESS ; 
 int /*<<< orphan*/  pci_enable_busmaster (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_find_cap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int pci_read_config (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void
mxge_setup_cfg_space(mxge_softc_t *sc)
{
	device_t dev = sc->dev;
	int reg;
	uint16_t lnk, pectl;

	/* find the PCIe link width and set max read request to 4KB*/
	if (pci_find_cap(dev, PCIY_EXPRESS, &reg) == 0) {
		lnk = pci_read_config(dev, reg + 0x12, 2);
		sc->link_width = (lnk >> 4) & 0x3f;

		if (sc->pectl == 0) {
			pectl = pci_read_config(dev, reg + 0x8, 2);
			pectl = (pectl & ~0x7000) | (5 << 12);
			pci_write_config(dev, reg + 0x8, pectl, 2);
			sc->pectl = pectl;
		} else {
			/* restore saved pectl after watchdog reset */
			pci_write_config(dev, reg + 0x8, sc->pectl, 2);
		}
	}

	/* Enable DMA and Memory space access */
	pci_enable_busmaster(dev);
}