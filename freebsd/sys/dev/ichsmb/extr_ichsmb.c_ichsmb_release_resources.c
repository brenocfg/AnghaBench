#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* sc_p ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_3__ {int /*<<< orphan*/ * io_res; int /*<<< orphan*/  io_rid; int /*<<< orphan*/ * irq_res; int /*<<< orphan*/  irq_rid; int /*<<< orphan*/ * irq_handle; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/  const,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
ichsmb_release_resources(sc_p sc)
{
	const device_t dev = sc->dev;

	if (sc->irq_handle != NULL) {
		bus_teardown_intr(dev, sc->irq_res, sc->irq_handle);
		sc->irq_handle = NULL;
	}
	if (sc->irq_res != NULL) {
		bus_release_resource(dev,
		    SYS_RES_IRQ, sc->irq_rid, sc->irq_res);
		sc->irq_res = NULL;
	}
	if (sc->io_res != NULL) {
		bus_release_resource(dev,
		    SYS_RES_IOPORT, sc->io_rid, sc->io_res);
		sc->io_res = NULL;
	}
}