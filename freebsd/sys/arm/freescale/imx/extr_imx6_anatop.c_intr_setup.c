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
struct imx6_anatop_softc {int /*<<< orphan*/  intr_setup_hook; int /*<<< orphan*/  dev; int /*<<< orphan*/  temp_intrhand; int /*<<< orphan*/ ** res; } ;

/* Variables and functions */
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 size_t IRQRES ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct imx6_anatop_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  config_intrhook_disestablish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tempmon_intr ; 

__attribute__((used)) static void
intr_setup(void *arg)
{
	int rid;
	struct imx6_anatop_softc *sc;

	sc = arg;
	rid = 0;
	sc->res[IRQRES] = bus_alloc_resource_any(sc->dev, SYS_RES_IRQ, &rid,
	    RF_ACTIVE);
	if (sc->res[IRQRES] != NULL) {
		bus_setup_intr(sc->dev, sc->res[IRQRES],
		    INTR_TYPE_MISC | INTR_MPSAFE, tempmon_intr, NULL, sc,
		    &sc->temp_intrhand);
	} else {
		device_printf(sc->dev, "Cannot allocate IRQ resource\n");
	}
	config_intrhook_disestablish(&sc->intr_setup_hook);
}