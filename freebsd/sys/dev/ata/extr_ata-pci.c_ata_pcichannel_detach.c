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
struct ata_pci_controller {int (* ch_detach ) (int /*<<< orphan*/ ) ;} ;
struct ata_channel {scalar_t__ attached; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ata_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ata_pcichannel_detach(device_t dev)
{
    struct ata_pci_controller *ctlr = device_get_softc(device_get_parent(dev));
    struct ata_channel *ch = device_get_softc(dev);
    int error;

    if (!ch->attached)
	return (0);
    ch->attached = 0;

    if ((error = ata_detach(dev)))
	return error;

    if (ctlr->ch_detach)
	return (ctlr->ch_detach(dev));

    return (0);
}