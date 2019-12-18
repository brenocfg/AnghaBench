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
struct ata_channel {TYPE_1__* r_io; scalar_t__ attached; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  res; } ;

/* Variables and functions */
 size_t ATA_CONTROL ; 
 int /*<<< orphan*/  ATA_CTLADDR_RID ; 
 size_t ATA_IDX_ADDR ; 
 int /*<<< orphan*/  ATA_IOADDR_RID ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int ata_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ata_channel* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ata_isa_detach(device_t dev)
{
    struct ata_channel *ch = device_get_softc(dev);
    int error;

    if (!ch->attached)
	return (0);
    ch->attached = 0;

    error = ata_detach(dev);

    bus_release_resource(dev, SYS_RES_IOPORT, ATA_CTLADDR_RID,
	ch->r_io[ATA_CONTROL].res);
    bus_release_resource(dev, SYS_RES_IOPORT, ATA_IOADDR_RID,
	ch->r_io[ATA_IDX_ADDR].res);
    return (error);
}