#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  mst_watchdog; } ;
struct TYPE_3__ {int /*<<< orphan*/  ic_oerrors; } ;
struct malo_softc {scalar_t__ malo_timer; TYPE_2__ malo_stats; TYPE_1__ malo_ic; int /*<<< orphan*/  malo_dev; int /*<<< orphan*/  malo_invalid; scalar_t__ malo_running; int /*<<< orphan*/  malo_watchdog_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct malo_softc*) ; 
 int /*<<< orphan*/  counter_u64_add (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hz ; 

__attribute__((used)) static void
malo_watchdog(void *arg)
{
	struct malo_softc *sc = arg;

	callout_reset(&sc->malo_watchdog_timer, hz, malo_watchdog, sc);
	if (sc->malo_timer == 0 || --sc->malo_timer > 0)
		return;

	if (sc->malo_running && !sc->malo_invalid) {
		device_printf(sc->malo_dev, "watchdog timeout\n");

		/* XXX no way to reset h/w. now  */

		counter_u64_add(sc->malo_ic.ic_oerrors, 1);
		sc->malo_stats.mst_watchdog++;
	}
}