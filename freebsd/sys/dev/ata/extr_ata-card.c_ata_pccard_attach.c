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
typedef  int uint16_t ;
struct resource {int dummy; } ;
struct ata_channel {int attached; int /*<<< orphan*/  flags; scalar_t__ unit; TYPE_1__* r_io; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int offset; struct resource* res; } ;

/* Variables and functions */
 int ATA_COMMAND ; 
 size_t ATA_CONTROL ; 
 int ATA_CTLADDR_RID ; 
 scalar_t__ ATA_CTLIOSIZE ; 
 int ATA_DATA ; 
 size_t ATA_IDX_ADDR ; 
 int ATA_IOADDR_RID ; 
 scalar_t__ ATA_IOSIZE ; 
 int ATA_MAX_RES ; 
 int /*<<< orphan*/  ATA_NO_SLAVE ; 
 int /*<<< orphan*/  ATA_USE_16BIT ; 
 int ENXIO ; 
 int PFD_I_D ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int ata_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_default_registers (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_generic_hw (int /*<<< orphan*/ ) ; 
 int ata_probe (int /*<<< orphan*/ ) ; 
 struct resource* bus_alloc_resource_anywhere (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct resource*) ; 
 struct ata_channel* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pccard_get_funce_disk (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ rman_get_size (struct resource*) ; 

__attribute__((used)) static int
ata_pccard_attach(device_t dev)
{
    struct ata_channel *ch = device_get_softc(dev);
    struct resource *io, *ctlio;
    int i, rid, err;
    uint16_t funce;

    if (ch->attached)
	return (0);
    ch->attached = 1;

    /* allocate the io range to get start and length */
    rid = ATA_IOADDR_RID;
    if (!(io = bus_alloc_resource_anywhere(dev, SYS_RES_IOPORT, &rid,
					   ATA_IOSIZE, RF_ACTIVE)))
	return (ENXIO);

    /* setup the resource vectors */
    for (i = ATA_DATA; i <= ATA_COMMAND; i++) {
	ch->r_io[i].res = io;
	ch->r_io[i].offset = i;
    }
    ch->r_io[ATA_IDX_ADDR].res = io;

    /*
     * if we got more than the default ATA_IOSIZE ports, this is a device
     * where ctlio is located at offset 14 into "normal" io space.
     */
    if (rman_get_size(io) > ATA_IOSIZE) {
	ch->r_io[ATA_CONTROL].res = io;
	ch->r_io[ATA_CONTROL].offset = 14;
    }
    else {
	rid = ATA_CTLADDR_RID;
	if (!(ctlio = bus_alloc_resource_anywhere(dev, SYS_RES_IOPORT, &rid,
						  ATA_CTLIOSIZE, RF_ACTIVE))) {
	    bus_release_resource(dev, SYS_RES_IOPORT, ATA_IOADDR_RID, io);
	    for (i = ATA_DATA; i < ATA_MAX_RES; i++)
		ch->r_io[i].res = NULL;
	    return (ENXIO);
	}
	ch->r_io[ATA_CONTROL].res = ctlio;
	ch->r_io[ATA_CONTROL].offset = 0;
    }
    ata_default_registers(dev);

    /* initialize softc for this channel */
    ch->unit = 0;
    ch->flags |= ATA_USE_16BIT;
    funce = 0;		/* Default to sane setting of FUNCE */
    pccard_get_funce_disk(dev, &funce); 
    if (!(funce & PFD_I_D))
        ch-> flags |= ATA_NO_SLAVE;
    ata_generic_hw(dev);
    err = ata_probe(dev);
    if (err > 0)
	return (err);
    return (ata_attach(dev));
}