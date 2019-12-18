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
typedef  int uint32_t ;
struct bcm_systimer_softc {int dummy; } ;
typedef  int int32_t ;
struct TYPE_2__ {int tc_frequency; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYSTIMER_CLO ; 
 TYPE_1__ bcm_systimer_tc ; 
 int bcm_systimer_tc_read_4 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bcm_systimer_delay(int usec, void *arg)
{
	struct bcm_systimer_softc *sc;
	int32_t counts;
	uint32_t first, last;

	sc = (struct bcm_systimer_softc *) arg;

	/* Get the number of times to count */
	counts = usec * (bcm_systimer_tc.tc_frequency / 1000000) + 1;

	first = bcm_systimer_tc_read_4(SYSTIMER_CLO);

	while (counts > 0) {
		last = bcm_systimer_tc_read_4(SYSTIMER_CLO);
		if (last == first)
			continue;
		if (last>first) {
			counts -= (int32_t)(last - first);
		} else {
			counts -= (int32_t)((0xFFFFFFFF - first) + last);
		}
		first = last;
	}
}