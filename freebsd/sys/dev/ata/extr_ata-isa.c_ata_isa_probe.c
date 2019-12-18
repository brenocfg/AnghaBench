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
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ATA_CTLADDR_RID ; 
 int /*<<< orphan*/  ATA_CTLIOSIZE ; 
 scalar_t__ ATA_CTLOFFSET ; 
 int ATA_IOADDR_RID ; 
 int /*<<< orphan*/  ATA_IOSIZE ; 
 scalar_t__ ENXIO ; 
 scalar_t__ ISA_PNP_PROBE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  ata_ids ; 
 int ata_probe (int /*<<< orphan*/ ) ; 
 struct resource* bus_alloc_resource_anywhere (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_get_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct resource*) ; 
 int /*<<< orphan*/  bus_set_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ rman_get_start (struct resource*) ; 

__attribute__((used)) static int
ata_isa_probe(device_t dev)
{
    struct resource *io = NULL, *ctlio = NULL;
    rman_res_t tmp;
    int rid;

    /* check isapnp ids */
    if (ISA_PNP_PROBE(device_get_parent(dev), dev, ata_ids) == ENXIO)
	return ENXIO;

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

    /* Release resources to reallocate on attach. */
    bus_release_resource(dev, SYS_RES_IOPORT, ATA_CTLADDR_RID, ctlio);
    bus_release_resource(dev, SYS_RES_IOPORT, ATA_IOADDR_RID, io);

    device_set_desc(dev, "ATA channel");
    return (ata_probe(dev));
}