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
struct cbb_softc {int /*<<< orphan*/ * base_res; int /*<<< orphan*/ * irq_res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct cbb_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cbb_isa_deactivate(device_t dev)
{
	struct cbb_softc *sc = device_get_softc(dev);

	if (sc->irq_res)
		bus_release_resource(dev, SYS_RES_IRQ, 0, sc->irq_res);
	sc->irq_res = NULL;
	if (sc->base_res)
		bus_release_resource(dev, SYS_RES_IOPORT, 0, sc->base_res);
	sc->base_res = NULL;
}