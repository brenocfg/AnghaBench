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
struct ata_pci_controller {TYPE_1__* interrupt; } ;
struct ata_channel {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* function ) (struct ata_channel*) ;struct ata_channel* argument; } ;

/* Variables and functions */
 int ATA_PCI_MAX_CH ; 
 int /*<<< orphan*/  stub1 (struct ata_channel*) ; 

void
ata_generic_intr(void *data)
{
    struct ata_pci_controller *ctlr = data;
    struct ata_channel *ch;
    int unit;

    for (unit = 0; unit < ATA_PCI_MAX_CH; unit++) {
	if ((ch = ctlr->interrupt[unit].argument))
	    ctlr->interrupt[unit].function(ch);
    }
}