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

/* Variables and functions */
 int counter_freq ; 
 int cycles_per_usec ; 
 int /*<<< orphan*/  set_cputicker (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  tick_ticker ; 

void
mips_timer_init_params(uint64_t platform_counter_freq, int double_count)
{

	/*
	 * XXX: Do not use printf here: uart code 8250 may use DELAY so this
	 * function should  be called before cninit.
	 */
	counter_freq = platform_counter_freq;
	/*
	 * XXX: Some MIPS32 cores update the Count register only every two
	 * pipeline cycles.
	 * We know this because of status registers in CP0, make it automatic.
	 */
	if (double_count != 0)
		counter_freq /= 2;

	cycles_per_usec = counter_freq / (1 * 1000 * 1000);
	set_cputicker(tick_ticker, counter_freq, 1);
}