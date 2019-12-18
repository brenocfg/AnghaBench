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
struct a10_timer_softc {int timer0_freq; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/ * res; int /*<<< orphan*/  sc_ih; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  clk_t ;
struct TYPE_5__ {int /*<<< orphan*/  ocd_data; } ;
struct TYPE_4__ {int tc_frequency; struct a10_timer_softc* tc_priv; } ;

/* Variables and functions */
 size_t A10_TIMER_IRQRES ; 
 int ENXIO ; 
 int /*<<< orphan*/  INTR_TYPE_CLK ; 
 int SYS_TIMER_CLKSRC ; 
 int /*<<< orphan*/  a10_timer_delay ; 
 int /*<<< orphan*/  a10_timer_eventtimer_setup (struct a10_timer_softc*) ; 
 int /*<<< orphan*/  a10_timer_irq ; 
 int /*<<< orphan*/  a10_timer_spec ; 
 TYPE_1__ a10_timer_timecounter ; 
 int /*<<< orphan*/  a23_timer_timecounter_setup (struct a10_timer_softc*) ; 
 int /*<<< orphan*/  arm_set_delay (int /*<<< orphan*/ ,struct a10_timer_softc*) ; 
 scalar_t__ bootverbose ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct a10_timer_softc*,int /*<<< orphan*/ *) ; 
 scalar_t__ clk_get_by_ofw_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ clk_get_freq (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  compat_data ; 
 struct a10_timer_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  hz ; 
 TYPE_2__* ofw_bus_search_compatible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stathz ; 
 int /*<<< orphan*/  tc_init (TYPE_1__*) ; 

__attribute__((used)) static int
a10_timer_attach(device_t dev)
{
	struct a10_timer_softc *sc;
	clk_t clk;
	int err;

	sc = device_get_softc(dev);
	sc->type = ofw_bus_search_compatible(dev, compat_data)->ocd_data;

	if (bus_alloc_resources(dev, a10_timer_spec, sc->res)) {
		device_printf(dev, "could not allocate resources\n");
		return (ENXIO);
	}

	sc->sc_dev = dev;

	/* Setup and enable the timer interrupt */
	err = bus_setup_intr(dev, sc->res[A10_TIMER_IRQRES], INTR_TYPE_CLK,
	    a10_timer_irq, NULL, sc, &sc->sc_ih);
	if (err != 0) {
		bus_release_resources(dev, a10_timer_spec, sc->res);
		device_printf(dev, "Unable to setup the clock irq handler, "
		    "err = %d\n", err);
		return (ENXIO);
	}

	if (clk_get_by_ofw_index(dev, 0, 0, &clk) != 0)
		sc->timer0_freq = SYS_TIMER_CLKSRC;
	else {
		if (clk_get_freq(clk, &sc->timer0_freq) != 0) {
			device_printf(dev, "Cannot get clock source frequency\n");
			return (ENXIO);
		}
	}

#if defined(__arm__)
	a10_timer_eventtimer_setup(sc);
	arm_set_delay(a10_timer_delay, sc);
	a10_timer_timecounter.tc_priv = sc;
	a10_timer_timecounter.tc_frequency = sc->timer0_freq;
	tc_init(&a10_timer_timecounter);
#elif defined(__aarch64__)
	a23_timer_timecounter_setup(sc);
#endif

	if (bootverbose) {
		device_printf(sc->sc_dev, "clock: hz=%d stathz = %d\n", hz, stathz);

		device_printf(sc->sc_dev, "event timer clock frequency %ju\n", 
		    sc->timer0_freq);
		device_printf(sc->sc_dev, "timecounter clock frequency %jd\n", 
		    a10_timer_timecounter.tc_frequency);
	}

	return (0);
}