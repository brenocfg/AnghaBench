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
struct TYPE_4__ {int /*<<< orphan*/ * irq; int /*<<< orphan*/  irq_rid; int /*<<< orphan*/ ** io; int /*<<< orphan*/ * io_rid; int /*<<< orphan*/  dev; int /*<<< orphan*/ ** drq; int /*<<< orphan*/ * drq_rid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_RELEASE_RESOURCE (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
#define  LOGICALID_MIDI 131 
#define  LOGICALID_NOPNP 130 
#define  LOGICALID_OPL 129 
#define  LOGICALID_PCM 128 
 int /*<<< orphan*/  SYS_RES_DRQ ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * find_masterdev (TYPE_1__*) ; 
 int isa_get_logicalid (int /*<<< orphan*/ ) ; 
 scalar_t__ isa_get_vendorid (int /*<<< orphan*/ ) ; 
 int nitems (int /*<<< orphan*/ **) ; 

__attribute__((used)) static int
release_resource(sc_p scp)
{
	int i, lid;
	device_t dev;

	if (isa_get_vendorid(scp->dev))
		lid = isa_get_logicalid(scp->dev);
	else
		lid = LOGICALID_NOPNP;

	switch(lid) {
	case LOGICALID_PCM:
	case LOGICALID_NOPNP:		/* XXX Non-PnP */
		for (i = 0 ; i < nitems(scp->io); i++) {
			if (scp->io[i] != NULL) {
				bus_release_resource(scp->dev, SYS_RES_IOPORT, scp->io_rid[i], scp->io[i]);
				scp->io[i] = NULL;
			}
		}
		if (scp->irq != NULL) {
			bus_release_resource(scp->dev, SYS_RES_IRQ, scp->irq_rid, scp->irq);
			scp->irq = NULL;
		}
		for (i = 0 ; i < nitems(scp->drq); i++) {
			if (scp->drq[i] != NULL) {
				bus_release_resource(scp->dev, SYS_RES_DRQ, scp->drq_rid[i], scp->drq[i]);
				scp->drq[i] = NULL;
			}
		}
		break;
	case LOGICALID_OPL:
		if (scp->io[0] != NULL) {
			bus_release_resource(scp->dev, SYS_RES_IOPORT, scp->io_rid[0], scp->io[0]);
			scp->io[0] = NULL;
		}
		break;
	case LOGICALID_MIDI:
		if (scp->io[0] != NULL) {
			bus_release_resource(scp->dev, SYS_RES_IOPORT, scp->io_rid[0], scp->io[0]);
			scp->io[0] = NULL;
		}
		if (scp->irq != NULL) {
			/* The irq is shared with pcm audio. */
			dev = find_masterdev(scp);
			if (dev == NULL)
				return (1);
			BUS_RELEASE_RESOURCE(dev, NULL, SYS_RES_IOPORT, scp->irq_rid, scp->irq);
			scp->irq = NULL;
		}
		break;
	}
	return (0);
}