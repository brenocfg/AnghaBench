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
typedef  int uint64_t ;
struct epit_softc {int clkfreq; } ;

/* Variables and functions */
 int epit_read_counter (struct epit_softc*) ; 

__attribute__((used)) static void
epit_do_delay(int usec, void *arg)
{
	struct epit_softc *sc = arg;
	uint64_t curcnt, endcnt, startcnt, ticks;

	/*
	 * Calculate the tick count with 64-bit values so that it works for any
	 * clock frequency.  Loop until the hardware count reaches start+ticks.
	 * If the 32-bit hardware count rolls over while we're looping, just
	 * manually do a carry into the high bits after each read; don't worry
	 * that doing this on each loop iteration is inefficient -- we're trying
	 * to waste time here.
	 */
	ticks = 1 + ((uint64_t)usec * sc->clkfreq) / 1000000;
	curcnt = startcnt = epit_read_counter(sc);
	endcnt = startcnt + ticks;
	while (curcnt < endcnt) {
		curcnt = epit_read_counter(sc);
		if (curcnt < startcnt)
			curcnt += 1ULL << 32;
	}
}