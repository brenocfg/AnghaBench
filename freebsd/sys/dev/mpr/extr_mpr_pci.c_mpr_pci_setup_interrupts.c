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
struct mpr_softc {int mpr_flags; int msi_msgs; struct mpr_queue* queues; int /*<<< orphan*/  mpr_dev; } ;
struct mpr_queue {int irq_rid; int /*<<< orphan*/  intrhand; int /*<<< orphan*/ * irq; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_BIO ; 
 int MPR_ERROR ; 
 int MPR_FLAGS_INTX ; 
 int MPR_FLAGS_MSI ; 
 int MPR_INIT ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,void*,struct mpr_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpr_dprint (struct mpr_softc*,int,char*,...) ; 
 void* mpr_intr ; 
 void* mpr_intr_msi ; 

int
mpr_pci_setup_interrupts(struct mpr_softc *sc)
{
	device_t dev;
	struct mpr_queue *q;
	void *ihandler;
	int i, error, rid, initial_rid;

	dev = sc->mpr_dev;
	error = ENXIO;

	if (sc->mpr_flags & MPR_FLAGS_INTX) {
		initial_rid = 0;
		ihandler = mpr_intr;
	} else if (sc->mpr_flags & MPR_FLAGS_MSI) {
		initial_rid = 1;
		ihandler = mpr_intr_msi;
	} else {
		mpr_dprint(sc, MPR_ERROR|MPR_INIT,
		    "Unable to set up interrupts\n");
		return (EINVAL);
	}

	for (i = 0; i < sc->msi_msgs; i++) {
		q = &sc->queues[i];
		rid = i + initial_rid;
		q->irq_rid = rid;
		q->irq = bus_alloc_resource_any(dev, SYS_RES_IRQ,
		    &q->irq_rid, RF_ACTIVE);
		if (q->irq == NULL) {
			mpr_dprint(sc, MPR_ERROR|MPR_INIT,
			    "Cannot allocate interrupt RID %d\n", rid);
			sc->msi_msgs = i;
			break;
		}
		error = bus_setup_intr(dev, q->irq,
		    INTR_TYPE_BIO | INTR_MPSAFE, NULL, ihandler,
		    sc, &q->intrhand);
		if (error) {
			mpr_dprint(sc, MPR_ERROR|MPR_INIT,
			    "Cannot setup interrupt RID %d\n", rid);
			sc->msi_msgs = i;
			break;
		}
	}

        mpr_dprint(sc, MPR_INIT, "Set up %d interrupts\n", sc->msi_msgs);
	return (error);
}