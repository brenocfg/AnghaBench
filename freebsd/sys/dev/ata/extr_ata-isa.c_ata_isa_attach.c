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
struct resource {int dummy; } ;
struct ata_channel {int attached; int /*<<< orphan*/  flags; scalar_t__ unit; TYPE_1__* r_io; } ;
typedef  int /*<<< orphan*/  rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int offset; struct resource* res; } ;

/* Variables and functions */
 int ATA_COMMAND ; 
 size_t ATA_CONTROL ; 
 int ATA_CTLADDR_RID ; 
 int /*<<< orphan*/  ATA_CTLIOSIZE ; 
 scalar_t__ ATA_CTLOFFSET ; 
 int ATA_DATA ; 
 size_t ATA_IDX_ADDR ; 
 int ATA_IOADDR_RID ; 
 int /*<<< orphan*/  ATA_IOSIZE ; 
 int /*<<< orphan*/  ATA_USE_16BIT ; 
 int ENXIO ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int ata_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_default_registers (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_generic_hw (int /*<<< orphan*/ ) ; 
 struct resource* bus_alloc_resource_anywhere (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_get_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct resource*) ; 
 int /*<<< orphan*/  bus_set_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ) ; 
 struct ata_channel* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ rman_get_start (struct resource*) ; 

__attribute__((used)) static int
ata_isa_attach(device_t dev)
{
    struct ata_channel *ch = device_get_softc(dev);
    struct resource *io = NULL, *ctlio = NULL;
    rman_res_t tmp;
    int i, rid;

    if (ch->attached)
	return (0);
    ch->attached = 1;

    /* allocate the io port range */
    rid = ATA_IOADDR_RID;
    if (!(io = bus_alloc_resource_anywhere(dev, SYS_RES_IOPORT, &rid,
					   ATA_IOSIZE, RF_ACTIVE)))
	return ENXIO;

    /* set the altport range */
    if (bus_get_resource(dev, SYS_RES_IOPORT, ATA_CTLADDR_RID, &tmp, &tmp)) {
	bus_set_resource(dev, SYS_RES_IOPORT, ATA_CTLADDR_RID,
			 rman_get_start(io) + ATA_CTLOFFSET, ATA_CTLIOSIZE);
    }

    /* allocate the altport range */
    rid = ATA_CTLADDR_RID; 
    if (!(ctlio = bus_alloc_resource_anywhere(dev, SYS_RES_IOPORT, &rid,
					      ATA_CTLIOSIZE, RF_ACTIVE))) {
	bus_release_resource(dev, SYS_RES_IOPORT, ATA_IOADDR_RID, io);
	return ENXIO;
    }

    /* setup the resource vectors */
    for (i = ATA_DATA; i <= ATA_COMMAND; i++) {
	ch->r_io[i].res = io;
	ch->r_io[i].offset = i;
    }
    ch->r_io[ATA_CONTROL].res = ctlio;
    ch->r_io[ATA_CONTROL].offset = 0;
    ch->r_io[ATA_IDX_ADDR].res = io;
    ata_default_registers(dev);
 
    /* initialize softc for this channel */
    ch->unit = 0;
    ch->flags |= ATA_USE_16BIT;
    ata_generic_hw(dev);
    return ata_attach(dev);
}