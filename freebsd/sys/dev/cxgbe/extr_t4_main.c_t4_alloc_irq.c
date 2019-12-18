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
struct irq {int rid; int /*<<< orphan*/  tag; int /*<<< orphan*/ * res; } ;
struct adapter {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  driver_intr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_NET ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  bus_describe_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,char*,...) ; 

__attribute__((used)) static int
t4_alloc_irq(struct adapter *sc, struct irq *irq, int rid,
    driver_intr_t *handler, void *arg, char *name)
{
	int rc;

	irq->rid = rid;
	irq->res = bus_alloc_resource_any(sc->dev, SYS_RES_IRQ, &irq->rid,
	    RF_SHAREABLE | RF_ACTIVE);
	if (irq->res == NULL) {
		device_printf(sc->dev,
		    "failed to allocate IRQ for rid %d, name %s.\n", rid, name);
		return (ENOMEM);
	}

	rc = bus_setup_intr(sc->dev, irq->res, INTR_MPSAFE | INTR_TYPE_NET,
	    NULL, handler, arg, &irq->tag);
	if (rc != 0) {
		device_printf(sc->dev,
		    "failed to setup interrupt for rid %d, name %s: %d\n",
		    rid, name, rc);
	} else if (name)
		bus_describe_intr(sc->dev, irq->res, irq->tag, "%s", name);

	return (rc);
}