#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ida_softc {int /*<<< orphan*/  free_qcbs; TYPE_2__* hwqcbs; int /*<<< orphan*/  buffer_dmat; struct ida_qcb* qcbs; } ;
struct ida_qcb {TYPE_2__* hwqcb; int /*<<< orphan*/  hwqcb_busaddr; int /*<<< orphan*/  flags; struct ida_softc* ida; int /*<<< orphan*/  dmamap; } ;
struct TYPE_4__ {struct ida_qcb* qcb; } ;
struct TYPE_3__ {int /*<<< orphan*/  sle; } ;

/* Variables and functions */
 int IDA_QCB_MAX ; 
 int /*<<< orphan*/  QCB_FREE ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct ida_qcb*,int /*<<< orphan*/ ) ; 
 int bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idahwqcbvtop (struct ida_softc*,TYPE_2__*) ; 
 TYPE_1__ link ; 

__attribute__((used)) static int
ida_alloc_qcbs(struct ida_softc *ida)
{
	struct ida_qcb *qcb;
	int error, i;

	for (i = 0; i < IDA_QCB_MAX; i++) {
		qcb = &ida->qcbs[i];

		error = bus_dmamap_create(ida->buffer_dmat, /*flags*/0, &qcb->dmamap);
		if (error != 0)
			return (error);

		qcb->ida = ida;
		qcb->flags = QCB_FREE;
		qcb->hwqcb = &ida->hwqcbs[i];
		qcb->hwqcb->qcb = qcb;
		qcb->hwqcb_busaddr = idahwqcbvtop(ida, qcb->hwqcb);
		SLIST_INSERT_HEAD(&ida->free_qcbs, qcb, link.sle);
	}
	return (0);
}