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
struct TYPE_2__ {int /*<<< orphan*/  ic_oerrors; } ;
struct bwn_softc {scalar_t__ sc_watchdog_timer; int /*<<< orphan*/  sc_watchdog_ch; TYPE_1__ sc_ic; int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  callout_schedule (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  counter_u64_add (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hz ; 

__attribute__((used)) static void
bwn_watchdog(void *arg)
{
	struct bwn_softc *sc = arg;

	if (sc->sc_watchdog_timer != 0 && --sc->sc_watchdog_timer == 0) {
		device_printf(sc->sc_dev, "device timeout\n");
		counter_u64_add(sc->sc_ic.ic_oerrors, 1);
	}
	callout_schedule(&sc->sc_watchdog_ch, hz);
}