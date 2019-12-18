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
struct arm_tmr_softc {int dummy; } ;
typedef  int int32_t ;
struct TYPE_4__ {struct arm_tmr_softc* tc_priv; } ;
struct TYPE_3__ {scalar_t__ tc_frequency; } ;

/* Variables and functions */
 int /*<<< orphan*/  TSENTER () ; 
 int /*<<< orphan*/  TSEXIT () ; 
 int /*<<< orphan*/  arm_tmr_delay (int,struct arm_tmr_softc*) ; 
 TYPE_2__* arm_tmr_tc ; 
 TYPE_1__ arm_tmr_timecount ; 
 int /*<<< orphan*/  cpufunc_nullop () ; 

void
DELAY(int usec)
{
	struct arm_tmr_softc *sc;
	int32_t counts;

	TSENTER();
	/* Check the timers are setup, if not just use a for loop for the meantime */
	if (arm_tmr_tc == NULL || arm_tmr_timecount.tc_frequency == 0) {
		for (; usec > 0; usec--)
			for (counts = 200; counts > 0; counts--)
				cpufunc_nullop();	/* Prevent gcc from optimizing
							 * out the loop
							 */
	} else {
		sc = arm_tmr_tc->tc_priv;
		arm_tmr_delay(usec, sc);
	}
	TSEXIT();
}