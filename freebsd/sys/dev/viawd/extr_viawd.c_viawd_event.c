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
struct viawd_softc {unsigned int timeout; } ;

/* Variables and functions */
 unsigned int WD_INTERVAL ; 
 int /*<<< orphan*/  viawd_tmr_set (struct viawd_softc*,unsigned int) ; 
 int /*<<< orphan*/  viawd_tmr_state (struct viawd_softc*,int) ; 

__attribute__((used)) static void
viawd_event(void *arg, unsigned int cmd, int *error)
{
	struct viawd_softc *sc = arg;
	unsigned int timeout;

	/* Convert from power-of-two-ns to second. */
	cmd &= WD_INTERVAL;
	timeout = ((uint64_t)1 << cmd) / 1000000000;
	if (cmd) {
		if (timeout != sc->timeout)
			viawd_tmr_set(sc, timeout);
		viawd_tmr_state(sc, 1);
		*error = 0;
	} else
		viawd_tmr_state(sc, 0);
}