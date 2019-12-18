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
struct ata_pci_controller {int (* ch_attach ) (int /*<<< orphan*/ ) ;} ;
struct ata_channel {int attached; intptr_t unit; int /*<<< orphan*/  pm_level; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ata_attach (int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_int_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ata_pcichannel_attach(device_t dev)
{
    struct ata_pci_controller *ctlr = device_get_softc(device_get_parent(dev));
    struct ata_channel *ch = device_get_softc(dev);
    int error;

    if (ch->attached)
	return (0);
    ch->attached = 1;

    ch->dev = dev;
    ch->unit = (intptr_t)device_get_ivars(dev);

    resource_int_value(device_get_name(dev),
	device_get_unit(dev), "pm_level", &ch->pm_level);

    if ((error = ctlr->ch_attach(dev)))
	return error;

    return ata_attach(dev);
}