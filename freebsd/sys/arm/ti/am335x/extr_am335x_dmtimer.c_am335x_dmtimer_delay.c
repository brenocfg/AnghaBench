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
typedef  int uint32_t ;
struct am335x_dmtimer_softc {int sysclk_freq; } ;
typedef  int int32_t ;

/* Variables and functions */
 int DMTIMER_READ4 (struct am335x_dmtimer_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMT_TCRR ; 

__attribute__((used)) static void
am335x_dmtimer_delay(int usec, void *arg)
{
	struct am335x_dmtimer_softc *sc = arg;
	int32_t counts;
	uint32_t first, last;

	/* Get the number of times to count */
	counts = (usec + 1) * (sc->sysclk_freq / 1000000);

	first = DMTIMER_READ4(sc, DMT_TCRR);

	while (counts > 0) {
		last = DMTIMER_READ4(sc, DMT_TCRR);
		if (last > first) {
			counts -= (int32_t)(last - first);
		} else {
			counts -= (int32_t)((0xFFFFFFFF - first) + last);
		}
		first = last;
	}
}