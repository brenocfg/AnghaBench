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
struct pl310_softc {int /*<<< orphan*/ * sc_ich; int /*<<< orphan*/  sc_irq_h; int /*<<< orphan*/  sc_irq_res; int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int EVENT_COUNTER_CONF_CO ; 
 int EVENT_COUNTER_CONF_DRREQ ; 
 int EVENT_COUNTER_CONF_INCR ; 
 int EVENT_COUNTER_CTRL_C0_RESET ; 
 int EVENT_COUNTER_CTRL_C1_RESET ; 
 int EVENT_COUNTER_CTRL_ENABLED ; 
 int INTR_MASK_ALL ; 
 int INTR_MASK_ECNTR ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  PL310_EVENT_COUNTER0_CONF ; 
 int /*<<< orphan*/  PL310_EVENT_COUNTER1_CONF ; 
 int /*<<< orphan*/  PL310_EVENT_COUNTER_CTRL ; 
 int /*<<< orphan*/  PL310_INTR_CLEAR ; 
 int /*<<< orphan*/  PL310_INTR_MASK ; 
 int /*<<< orphan*/  bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct pl310_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  config_intrhook_disestablish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pl310_filter ; 
 int /*<<< orphan*/  pl310_write4 (struct pl310_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
pl310_config_intr(void *arg)
{
	struct pl310_softc * sc;

	sc = arg;

	/* activate the interrupt */
	bus_setup_intr(sc->sc_dev, sc->sc_irq_res, INTR_TYPE_MISC | INTR_MPSAFE,
	    pl310_filter, NULL, sc, &sc->sc_irq_h);

	/* Cache Line Eviction for Counter 0 */
	pl310_write4(sc, PL310_EVENT_COUNTER0_CONF,
	    EVENT_COUNTER_CONF_INCR | EVENT_COUNTER_CONF_CO);
	/* Data Read Request for Counter 1 */
	pl310_write4(sc, PL310_EVENT_COUNTER1_CONF,
	    EVENT_COUNTER_CONF_INCR | EVENT_COUNTER_CONF_DRREQ);

	/* Enable and clear pending interrupts */
	pl310_write4(sc, PL310_INTR_CLEAR, INTR_MASK_ECNTR);
	pl310_write4(sc, PL310_INTR_MASK, INTR_MASK_ALL);

	/* Enable counters and reset C0 and C1 */
	pl310_write4(sc, PL310_EVENT_COUNTER_CTRL,
	    EVENT_COUNTER_CTRL_ENABLED |
	    EVENT_COUNTER_CTRL_C0_RESET |
	    EVENT_COUNTER_CTRL_C1_RESET);

	config_intrhook_disestablish(sc->sc_ich);
	free(sc->sc_ich, M_DEVBUF);
	sc->sc_ich = NULL;
}