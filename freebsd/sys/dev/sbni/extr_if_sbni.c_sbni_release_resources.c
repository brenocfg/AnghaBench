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
struct sbni_softc {scalar_t__ io_off; scalar_t__ io_res; int /*<<< orphan*/  io_rid; int /*<<< orphan*/  dev; scalar_t__ irq_res; int /*<<< orphan*/  irq_rid; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

void
sbni_release_resources(struct sbni_softc *sc)
{

	if (sc->irq_res)
		bus_release_resource(sc->dev, SYS_RES_IRQ, sc->irq_rid,
		    sc->irq_res);
	if (sc->io_res && sc->io_off == 0)
		bus_release_resource(sc->dev, SYS_RES_IOPORT, sc->io_rid,
		    sc->io_res);
}