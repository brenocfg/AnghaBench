#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* tc_name; int tc_quality; int tc_counter_mask; struct epit_softc* tc_priv; int /*<<< orphan*/  tc_get_timecount; int /*<<< orphan*/  tc_frequency; } ;
struct epit_softc {int ctlreg; TYPE_1__ tc; int /*<<< orphan*/  clkfreq; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPIT_CR ; 
 int EPIT_CR_EN ; 
 int /*<<< orphan*/  EPIT_LR ; 
 int /*<<< orphan*/  WR4 (struct epit_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  arm_set_delay (int /*<<< orphan*/ ,struct epit_softc*) ; 
 int /*<<< orphan*/  epit_do_delay ; 
 int /*<<< orphan*/  epit_tc_get_timecount ; 
 int /*<<< orphan*/  tc_init (TYPE_1__*) ; 

__attribute__((used)) static int
epit_tc_attach(struct epit_softc *sc)
{

	/* When the counter hits zero, reload with 0xffffffff.  Start it. */
	WR4(sc, EPIT_LR, 0xffffffff);
	WR4(sc, EPIT_CR, sc->ctlreg | EPIT_CR_EN);

	/* Register as a timecounter. */
	sc->tc.tc_name          = "EPIT";
	sc->tc.tc_quality       = 1000;
	sc->tc.tc_frequency     = sc->clkfreq;
	sc->tc.tc_counter_mask  = 0xffffffff;
	sc->tc.tc_get_timecount = epit_tc_get_timecount;
	sc->tc.tc_priv          = sc;
	tc_init(&sc->tc);

	/* We are the DELAY() implementation. */
	arm_set_delay(epit_do_delay, sc);

	return (0);
}