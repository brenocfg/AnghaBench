#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct arm_tmr_softc {int memrid; int /*<<< orphan*/  clkfreq; int /*<<< orphan*/  dev; int /*<<< orphan*/ * gbl_mem; } ;
struct TYPE_4__ {struct arm_tmr_softc* tc_priv; int /*<<< orphan*/  tc_frequency; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENXIO ; 
 int /*<<< orphan*/  GBL_TIMER_CTRL ; 
 int GBL_TIMER_CTRL_TIMER_ENABLE ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 TYPE_1__* arm_tmr_tc ; 
 TYPE_1__ arm_tmr_timecount ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tc_init (TYPE_1__*) ; 
 int /*<<< orphan*/  tmr_gbl_write_4 (struct arm_tmr_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
attach_tc(struct arm_tmr_softc *sc)
{
	int rid;

	if (arm_tmr_tc != NULL)
		return (EBUSY);

	rid = sc->memrid;
	sc->gbl_mem = bus_alloc_resource_any(sc->dev, SYS_RES_MEMORY, &rid,
	    RF_ACTIVE);
	if (sc->gbl_mem == NULL) {
		device_printf(sc->dev, "could not allocate gbl mem resources\n");
		return (ENXIO);
	}
	tmr_gbl_write_4(sc, GBL_TIMER_CTRL, 0x00000000);

	arm_tmr_timecount.tc_frequency = sc->clkfreq;
	arm_tmr_timecount.tc_priv = sc;
	tc_init(&arm_tmr_timecount);
	arm_tmr_tc = &arm_tmr_timecount;

	tmr_gbl_write_4(sc, GBL_TIMER_CTRL, GBL_TIMER_CTRL_TIMER_ENABLE);

	return (0);
}