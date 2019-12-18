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
typedef  int /*<<< orphan*/  device_t ;
typedef  TYPE_1__* bt3c_softc_p ;
struct TYPE_4__ {int /*<<< orphan*/  ifq_mtx; } ;
struct TYPE_3__ {TYPE_2__ outq; TYPE_2__ inq; int /*<<< orphan*/  m; int /*<<< orphan*/ * node; scalar_t__ iobase_rid; int /*<<< orphan*/ * iobase; scalar_t__ irq_rid; int /*<<< orphan*/ * irq; int /*<<< orphan*/ * irq_cookie; int /*<<< orphan*/ * ith; } ;

/* Variables and functions */
 int /*<<< orphan*/  IF_DRAIN (TYPE_2__*) ; 
 int /*<<< orphan*/  NG_FREE_M (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_NODE_SET_PRIVATE (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ng_rmnode_self (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swi_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
bt3c_pccard_detach(device_t dev)
{
	bt3c_softc_p	sc = (bt3c_softc_p) device_get_softc(dev);

	if (sc == NULL)
		return (0);

	swi_remove(sc->ith);
	sc->ith = NULL;

	bus_teardown_intr(dev, sc->irq, sc->irq_cookie);
	bus_release_resource(dev, SYS_RES_IRQ, sc->irq_rid, sc->irq);
	sc->irq_cookie = NULL;
	sc->irq = NULL;
	sc->irq_rid = 0;

	bus_release_resource(dev, SYS_RES_IOPORT, sc->iobase_rid, sc->iobase);
	sc->iobase = NULL;
	sc->iobase_rid = 0;

	if (sc->node != NULL) {
		NG_NODE_SET_PRIVATE(sc->node, NULL);
		ng_rmnode_self(sc->node);
		sc->node = NULL;
	}

	NG_FREE_M(sc->m);
	IF_DRAIN(&sc->inq);
	IF_DRAIN(&sc->outq);

	mtx_destroy(&sc->inq.ifq_mtx);
	mtx_destroy(&sc->outq.ifq_mtx);

	return (0);
}