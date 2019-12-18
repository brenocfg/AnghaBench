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
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {char* text; int /*<<< orphan*/  max_dma; } ;

/* Variables and functions */
 char* ata_mode2str (int /*<<< orphan*/ ) ; 
 char* ata_pcivendor2str (int /*<<< orphan*/ ) ; 
 struct ata_pci_controller* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc_copy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*,char*) ; 

void
ata_set_desc(device_t dev)
{
    struct ata_pci_controller *ctlr = device_get_softc(dev);
    char buffer[128];

    sprintf(buffer, "%s %s %s controller",
            ata_pcivendor2str(dev), ctlr->chip->text, 
            ata_mode2str(ctlr->chip->max_dma));
    device_set_desc_copy(dev, buffer);
}