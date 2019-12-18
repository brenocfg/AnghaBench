#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* sc_p ;
typedef  int /*<<< orphan*/ * device_t ;
struct TYPE_4__ {int* io_rid; int irq_rid; int* drq_rid; int /*<<< orphan*/  irq_alloced; int /*<<< orphan*/ * irq; int /*<<< orphan*/ * io_alloced; int /*<<< orphan*/ ** io; int /*<<< orphan*/  dev; int /*<<< orphan*/ * drq_alloced; int /*<<< orphan*/ ** drq; } ;

/* Variables and functions */
 int /*<<< orphan*/ * BUS_ALLOC_RESOURCE (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int DV_F_DRQ_MASK ; 
 int DV_F_DUAL_DMA ; 
#define  LOGICALID_MIDI 131 
#define  LOGICALID_NOPNP 130 
#define  LOGICALID_OPL 129 
#define  LOGICALID_PCM 128 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_DRQ ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 void* bus_alloc_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int,int,int) ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 void* bus_alloc_resource_anywhere (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int) ; 
 int device_get_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * find_masterdev (TYPE_1__*) ; 
 int /*<<< orphan*/ * io_offset ; 
 int* io_range ; 
 int isa_get_logicalid (int /*<<< orphan*/ ) ; 
 int isa_get_port (int /*<<< orphan*/ ) ; 
 scalar_t__ isa_get_vendorid (int /*<<< orphan*/ ) ; 
 int nitems (int /*<<< orphan*/ **) ; 

__attribute__((used)) static int
alloc_resource(sc_p scp)
{
	int i, base, lid, flags;
	device_t dev;

	flags = 0;
	if (isa_get_vendorid(scp->dev))
		lid = isa_get_logicalid(scp->dev);
	else {
		lid = LOGICALID_NOPNP;
		flags = device_get_flags(scp->dev);
	}
	switch(lid) {
	case LOGICALID_PCM:
	case LOGICALID_NOPNP:		/* XXX Non-PnP */
		if (lid == LOGICALID_NOPNP)
			base = isa_get_port(scp->dev);
		else
			base = 0;
		for (i = 0 ; i < nitems(scp->io); i++) {
			if (scp->io[i] == NULL) {
				scp->io_rid[i] = i;
				if (base == 0)
					scp->io[i] =
					    bus_alloc_resource_anywhere(scp->dev,
					    	    			SYS_RES_IOPORT,
					    	    			&scp->io_rid[i],
									io_range[i],
									RF_ACTIVE);
				else
					scp->io[i] = bus_alloc_resource(scp->dev, SYS_RES_IOPORT, &scp->io_rid[i],
									base + io_offset[i],
									base + io_offset[i] + io_range[i] - 1
									, io_range[i], RF_ACTIVE);
				if (scp->io[i] == NULL)
					return (1);
				scp->io_alloced[i] = 0;
			}
		}
		if (scp->irq == NULL) {
			scp->irq_rid = 0;
			scp->irq = 
				bus_alloc_resource_any(scp->dev, SYS_RES_IRQ, 
						       &scp->irq_rid,
						       RF_ACTIVE|RF_SHAREABLE);
			if (scp->irq == NULL)
				return (1);
			scp->irq_alloced = 0;
		}
		for (i = 0 ; i < nitems(scp->drq); i++) {
			if (scp->drq[i] == NULL) {
				scp->drq_rid[i] = i;
				if (base == 0 || i == 0)
					scp->drq[i] = 
						bus_alloc_resource_any(
							scp->dev, SYS_RES_DRQ,
							&scp->drq_rid[i],
							RF_ACTIVE);
				else if ((flags & DV_F_DUAL_DMA) != 0)
					/* XXX The secondary drq is specified in the flag. */
					scp->drq[i] = bus_alloc_resource(scp->dev, SYS_RES_DRQ, &scp->drq_rid[i],
									 flags & DV_F_DRQ_MASK,
									 flags & DV_F_DRQ_MASK, 1, RF_ACTIVE);
				if (scp->drq[i] == NULL)
					return (1);
				scp->drq_alloced[i] = 0;
			}
		}
		break;
	case LOGICALID_OPL:
		if (scp->io[0] == NULL) {
			scp->io_rid[0] = 0;
			scp->io[0] = bus_alloc_resource_anywhere(scp->dev,
								 SYS_RES_IOPORT,
								 &scp->io_rid[0],
								 io_range[0],
								 RF_ACTIVE);
			if (scp->io[0] == NULL)
				return (1);
			scp->io_alloced[0] = 0;
		}
		break;
	case LOGICALID_MIDI:
		if (scp->io[0] == NULL) {
			scp->io_rid[0] = 0;
			scp->io[0] = bus_alloc_resource_anywhere(scp->dev,
								 SYS_RES_IOPORT,
								 &scp->io_rid[0],
								 io_range[0],
								 RF_ACTIVE);
			if (scp->io[0] == NULL)
				return (1);
			scp->io_alloced[0] = 0;
		}
		if (scp->irq == NULL) {
			/* The irq is shared with pcm audio. */
			dev = find_masterdev(scp);
			if (dev == NULL)
				return (1);
			scp->irq_rid = 0;
			scp->irq = BUS_ALLOC_RESOURCE(dev, NULL, SYS_RES_IRQ, &scp->irq_rid,
						      0, ~0, 1, RF_ACTIVE | RF_SHAREABLE);
			if (scp->irq == NULL)
				return (1);
			scp->irq_alloced = 0;
		}
		break;
	}
	return (0);
}