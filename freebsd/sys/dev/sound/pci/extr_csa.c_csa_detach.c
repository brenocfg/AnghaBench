#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sndcard_func {int dummy; } ;
typedef  TYPE_1__* sc_p ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_5__ {int /*<<< orphan*/  io; int /*<<< orphan*/  io_rid; int /*<<< orphan*/  mem; int /*<<< orphan*/  mem_rid; int /*<<< orphan*/  irq; int /*<<< orphan*/  irq_rid; } ;
typedef  TYPE_2__ csa_res ;
struct TYPE_4__ {int /*<<< orphan*/  ih; int /*<<< orphan*/ * pcm; int /*<<< orphan*/ * midi; TYPE_2__ res; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct sndcard_func* device_get_ivars (int /*<<< orphan*/ *) ; 
 TYPE_1__* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct sndcard_func*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
csa_detach(device_t dev)
{
	csa_res *resp;
	sc_p scp;
	struct sndcard_func *func;
	int err;

	scp = device_get_softc(dev);
	resp = &scp->res;

	if (scp->midi != NULL) {
		func = device_get_ivars(scp->midi);
		err = device_delete_child(dev, scp->midi);
		if (err != 0)
			return err;
		if (func != NULL)
			free(func, M_DEVBUF);
		scp->midi = NULL;
	}

	if (scp->pcm != NULL) {
		func = device_get_ivars(scp->pcm);
		err = device_delete_child(dev, scp->pcm);
		if (err != 0)
			return err;
		if (func != NULL)
			free(func, M_DEVBUF);
		scp->pcm = NULL;
	}

	bus_teardown_intr(dev, resp->irq, scp->ih);
	bus_release_resource(dev, SYS_RES_IRQ, resp->irq_rid, resp->irq);
	bus_release_resource(dev, SYS_RES_MEMORY, resp->mem_rid, resp->mem);
	bus_release_resource(dev, SYS_RES_MEMORY, resp->io_rid, resp->io);

	return bus_generic_detach(dev);
}