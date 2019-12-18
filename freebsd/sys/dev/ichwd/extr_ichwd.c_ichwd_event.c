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
typedef  unsigned int uint64_t ;
struct ichwd_softc {int tco_version; unsigned int timeout; scalar_t__ active; } ;

/* Variables and functions */
 unsigned int ICHWD_TCO_V3_TICK ; 
 unsigned int ICHWD_TICK ; 
 unsigned int WD_INTERVAL ; 
 int /*<<< orphan*/  ichwd_tmr_disable (struct ichwd_softc*) ; 
 int /*<<< orphan*/  ichwd_tmr_enable (struct ichwd_softc*) ; 
 int /*<<< orphan*/  ichwd_tmr_reload (struct ichwd_softc*) ; 
 int /*<<< orphan*/  ichwd_tmr_set (struct ichwd_softc*,unsigned int) ; 

__attribute__((used)) static void
ichwd_event(void *arg, unsigned int cmd, int *error)
{
	struct ichwd_softc *sc = arg;
	unsigned int timeout;

	/* convert from power-of-two-ns to WDT ticks */
	cmd &= WD_INTERVAL;
	
	if (sc->tco_version == 3) {
		timeout = ((uint64_t)1 << cmd) / ICHWD_TCO_V3_TICK;
	} else {
		timeout = ((uint64_t)1 << cmd) / ICHWD_TICK;
	}
	
	if (cmd) {
		if (!sc->active)
			ichwd_tmr_enable(sc);
		if (timeout != sc->timeout)
			ichwd_tmr_set(sc, timeout);
		ichwd_tmr_reload(sc);
		*error = 0;
	} else {
		if (sc->active)
			ichwd_tmr_disable(sc);
	}
}