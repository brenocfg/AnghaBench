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

void
mips_timer_early_init(uint64_t clock_hz)
{
	/* Initialize clock early so that we can use DELAY sooner */
	counter_freq = clock_hz;
	cycles_per_usec = (clock_hz / (1000 * 1000));
}