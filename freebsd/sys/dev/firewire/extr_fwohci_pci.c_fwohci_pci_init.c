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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int DEF_CACHE_LINE ; 
 int DEF_LATENCY ; 
 int FW_DEVICE_PCIO2FW ; 
 int FW_VENDORID_SUN ; 
 int PCIM_CMD_BUSMASTEREN ; 
 int PCIM_CMD_MWRICEN ; 
 int /*<<< orphan*/  PCIR_CACHELNSZ ; 
 int /*<<< orphan*/  PCIR_COMMAND ; 
 int /*<<< orphan*/  PCIR_LATTIMER ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int) ; 
 scalar_t__ firewire_debug ; 
 int pci_get_devid (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_intpin (int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_set_intpin (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
fwohci_pci_init(device_t self)
{
	int olatency, latency, ocache_line, cache_line;
	uint16_t cmd;

	cmd = pci_read_config(self, PCIR_COMMAND, 2);
	cmd |= PCIM_CMD_BUSMASTEREN | PCIM_CMD_MWRICEN;
#if 1  /* for broken hardware */
	cmd &= ~PCIM_CMD_MWRICEN;
#endif
	pci_write_config(self, PCIR_COMMAND, cmd, 2);

	/*
	 * Some Sun PCIO-2 FireWire controllers have their intpin register
	 * bogusly set to 0, although it should be 3. Correct that.
	 */
	if (pci_get_devid(self) == (FW_VENDORID_SUN | FW_DEVICE_PCIO2FW) &&
	    pci_get_intpin(self) == 0)
		pci_set_intpin(self, 3);

	latency = olatency = pci_read_config(self, PCIR_LATTIMER, 1);
#define DEF_LATENCY 0x20
	if (olatency < DEF_LATENCY) {
		latency = DEF_LATENCY;
		pci_write_config(self, PCIR_LATTIMER, latency, 1);
	}

	cache_line = ocache_line = pci_read_config(self, PCIR_CACHELNSZ, 1);
#define DEF_CACHE_LINE 8
	if (ocache_line < DEF_CACHE_LINE) {
		cache_line = DEF_CACHE_LINE;
		pci_write_config(self, PCIR_CACHELNSZ, cache_line, 1);
	}

	if (firewire_debug) {
		device_printf(self, "latency timer %d -> %d.\n",
			olatency, latency);
		device_printf(self, "cache size %d -> %d.\n",
			ocache_line, cache_line);
	}

	return 0;
}