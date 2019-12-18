#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ (* int_pending ) (struct ida_softc*) ;int (* done ) (struct ida_softc*) ;} ;
struct ida_softc {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; TYPE_1__ cmd; } ;
struct ida_qcb {scalar_t__ state; TYPE_3__* hwqcb; } ;
typedef  int /*<<< orphan*/  intmax_t ;
typedef  int bus_addr_t ;
struct TYPE_5__ {scalar_t__ error; } ;
struct TYPE_6__ {TYPE_2__ req; } ;

/* Variables and functions */
 scalar_t__ CMD_REJECTED ; 
 scalar_t__ QCB_ACTIVE ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_done (struct ida_softc*,struct ida_qcb*) ; 
 int /*<<< orphan*/  ida_startio (struct ida_softc*) ; 
 struct ida_qcb* idahwqcbptov (struct ida_softc*,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct ida_softc*) ; 
 int stub2 (struct ida_softc*) ; 

void
ida_intr(void *data)
{
	struct ida_softc *ida;
	struct ida_qcb *qcb;
	bus_addr_t completed;

	ida = (struct ida_softc *)data;

	mtx_lock(&ida->lock);
	if (ida->cmd.int_pending(ida) == 0) {
		mtx_unlock(&ida->lock);
		return;				/* not our interrupt */
	}

	while ((completed = ida->cmd.done(ida)) != 0) {
		qcb = idahwqcbptov(ida, completed & ~3);

		if (qcb == NULL || qcb->state != QCB_ACTIVE) {
			device_printf(ida->dev,
			    "ignoring completion %jx\n", (intmax_t)completed);
			continue;
		}
		/* Handle "Bad Command List" errors. */
		if ((completed & 3) && (qcb->hwqcb->req.error == 0))
			qcb->hwqcb->req.error = CMD_REJECTED;
		ida_done(ida, qcb);
	}
	ida_startio(ida);
	mtx_unlock(&ida->lock);
}