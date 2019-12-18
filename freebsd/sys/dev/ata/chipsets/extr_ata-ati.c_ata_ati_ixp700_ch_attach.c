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
typedef  int uint8_t ;
struct ata_pci_controller {scalar_t__ chipset_data; } ;
struct ata_channel {int unit; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_SATA ; 
 int ENXIO ; 
 scalar_t__ ata_pci_ch_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ata_ati_ixp700_ch_attach(device_t dev)
{
	struct ata_pci_controller *ctlr = device_get_softc(device_get_parent(dev));
	struct ata_channel *ch = device_get_softc(dev);
	uint8_t satacfg = (uint8_t)(uintptr_t)ctlr->chipset_data;

	/* Setup the usual register normal pci style. */
	if (ata_pci_ch_attach(dev))
		return ENXIO;

	/* One of channels is PATA, another is SATA. */
	if (ch->unit == ((satacfg & 0x10) >> 4))
		ch->flags |= ATA_SATA;
	return (0);
}