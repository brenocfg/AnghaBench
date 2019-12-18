#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ata_pci_controller {TYPE_1__* chip; } ;
struct ata_channel {int unit; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int chiprev; } ;

/* Variables and functions */
 scalar_t__ ATA_ALI_1533 ; 
 int /*<<< orphan*/  GRANDPARENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  ata_generic_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_children (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_devid (int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void
ata_ali_reset(device_t dev)
{
    struct ata_pci_controller *ctlr = device_get_softc(device_get_parent(dev));
    struct ata_channel *ch = device_get_softc(dev);
    device_t *children;
    int nchildren, i;

    ata_generic_reset(dev);

    /*
     * workaround for datacorruption bug found on at least SUN Blade-100
     * find the ISA function on the southbridge and disable then enable
     * the ATA channel tristate buffer
     */
    if (ctlr->chip->chiprev == 0xc3 || ctlr->chip->chiprev == 0xc2) {
	if (!device_get_children(GRANDPARENT(dev), &children, &nchildren)) {
	    for (i = 0; i < nchildren; i++) {
		if (pci_get_devid(children[i]) == ATA_ALI_1533) {
		    pci_write_config(children[i], 0x58, 
				     pci_read_config(children[i], 0x58, 1) &
				     ~(0x04 << ch->unit), 1);
		    pci_write_config(children[i], 0x58, 
				     pci_read_config(children[i], 0x58, 1) |
				     (0x04 << ch->unit), 1);
		    break;
		}
	    }
	    free(children, M_TEMP);
	}
    }
}