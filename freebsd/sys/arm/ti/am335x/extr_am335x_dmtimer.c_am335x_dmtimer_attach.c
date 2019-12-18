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
struct am335x_dmtimer_softc {int tmr_num; int /*<<< orphan*/  tmr_name; int /*<<< orphan*/ * tmr_mem_res; int /*<<< orphan*/  tmr_mem_rid; int /*<<< orphan*/  sysclk_freq; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  clk_ident_t ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ ET_TMR_NUM ; 
 int /*<<< orphan*/  INVALID_CLK_IDENT ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYSCLK_CLK ; 
 int /*<<< orphan*/  SYS_CLK ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 scalar_t__ TC_TMR_NUM ; 
 int /*<<< orphan*/  am335x_dmtimer_et_init (struct am335x_dmtimer_softc*) ; 
 int /*<<< orphan*/  am335x_dmtimer_tc_init (struct am335x_dmtimer_softc*) ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct am335x_dmtimer_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,scalar_t__) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  ti_hwmods_get_clock (int /*<<< orphan*/ ) ; 
 int ti_hwmods_get_unit (int /*<<< orphan*/ ,char*) ; 
 int ti_prcm_clk_enable (int /*<<< orphan*/ ) ; 
 int ti_prcm_clk_get_source_freq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ti_prcm_clk_set_source (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
am335x_dmtimer_attach(device_t dev)
{
	struct am335x_dmtimer_softc *sc;
	clk_ident_t timer_id;
	int err;

	sc = device_get_softc(dev);
	sc->dev = dev;

	/* Get the base clock frequency. */
	if ((err = ti_prcm_clk_get_source_freq(SYS_CLK, &sc->sysclk_freq)) != 0)
		return (err);

	/* Enable clocks and power on the device. */
	if ((timer_id = ti_hwmods_get_clock(dev)) == INVALID_CLK_IDENT)
		return (ENXIO);
	if ((err = ti_prcm_clk_set_source(timer_id, SYSCLK_CLK)) != 0)
		return (err);
	if ((err = ti_prcm_clk_enable(timer_id)) != 0)
		return (err);

	/* Request the memory resources. */
	sc->tmr_mem_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
	    &sc->tmr_mem_rid, RF_ACTIVE);
	if (sc->tmr_mem_res == NULL) {
		return (ENXIO);
	}

	sc->tmr_num = ti_hwmods_get_unit(dev, "timer");
	snprintf(sc->tmr_name, sizeof(sc->tmr_name), "DMTimer%d", sc->tmr_num);

	/*
	 * Go set up either a timecounter or eventtimer.  We wouldn't have
	 * attached if we weren't one or the other.
	 */
	if (sc->tmr_num == ET_TMR_NUM)
		am335x_dmtimer_et_init(sc);
	else if (sc->tmr_num == TC_TMR_NUM)
		am335x_dmtimer_tc_init(sc);
	else
		panic("am335x_dmtimer: bad timer number %d", sc->tmr_num);

	return (0);
}