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

/* Variables and functions */
 int /*<<< orphan*/  TSENTER () ; 
 int /*<<< orphan*/  TSEXIT () ; 
 int /*<<< orphan*/  mv_delay (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timers_initialized ; 

void
DELAY(int usec)
{
	uint32_t	val;

	if (!timers_initialized) {
		for (; usec > 0; usec--)
			for (val = 100; val > 0; val--)
				__asm __volatile("nop" ::: "memory");
	} else {
		TSENTER();
		mv_delay(usec, NULL);
		TSEXIT();
	}
}