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
struct ata_channel {int unit; scalar_t__ devices; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int cfg2; } ;

/* Variables and functions */
 int VIABAR ; 
 int /*<<< orphan*/  ata_generic_reset (int /*<<< orphan*/ ) ; 
 scalar_t__ ata_sata_phy_reset (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ata_via_reset(device_t dev)
{
    struct ata_pci_controller *ctlr = device_get_softc(device_get_parent(dev));
    struct ata_channel *ch = device_get_softc(dev);

    if ((ctlr->chip->cfg2 & VIABAR) && (ch->unit > 1))
        ata_generic_reset(dev);
    else {
	if (ata_sata_phy_reset(dev, -1, 1))
	    ata_generic_reset(dev);
	else
	    ch->devices = 0;
    }
}