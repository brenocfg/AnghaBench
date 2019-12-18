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
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ mxge_softc_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCIY_VENDOR ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ pci_find_cap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ pci_read_config (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,scalar_t__,int,int) ; 

__attribute__((used)) static uint32_t
mxge_read_reboot(mxge_softc_t *sc)
{
	device_t dev = sc->dev;
	uint32_t vs;

	/* find the vendor specific offset */
	if (pci_find_cap(dev, PCIY_VENDOR, &vs) != 0) {
		device_printf(sc->dev,
			      "could not find vendor specific offset\n");
		return (uint32_t)-1;
	}
	/* enable read32 mode */
	pci_write_config(dev, vs + 0x10, 0x3, 1);
	/* tell NIC which register to read */
	pci_write_config(dev, vs + 0x18, 0xfffffff0, 4);
	return (pci_read_config(dev, vs + 0x14, 4));
}