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
struct ata_pci_controller {int /*<<< orphan*/  r_res2; } ;
struct ata_channel {int unit; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_IDX_INL (struct ata_channel*,int /*<<< orphan*/ ) ; 
 int ATA_INL (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ATA_STATUS ; 
 int ata_pci_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ata_serverworks_status(device_t dev)
{
    struct ata_channel *ch = device_get_softc(dev);
    struct ata_pci_controller *ctlr = device_get_softc(device_get_parent(dev));

    /*
     * Check if this interrupt belongs to our channel.
     */
    if (!(ATA_INL(ctlr->r_res2, 0x1f80) & (1 << ch->unit)))
	return (0);

    /*
     * We need to do a 4-byte read on the status reg before the values
     * will report correctly
     */

    ATA_IDX_INL(ch,ATA_STATUS);

    return ata_pci_status(dev);
}