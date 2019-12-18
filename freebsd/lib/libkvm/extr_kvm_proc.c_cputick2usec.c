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
 int cpu_tick_frequency ; 

__attribute__((used)) static uint64_t
cputick2usec(uint64_t tick)
{

	if (cpu_tick_frequency == 0)
		return (0);
	if (tick > 18446744073709551)		/* floor(2^64 / 1000) */
		return (tick / (cpu_tick_frequency / 1000000));
	else if (tick > 18446744073709)	/* floor(2^64 / 1000000) */
		return ((tick * 1000) / (cpu_tick_frequency / 1000));
	else
		return ((tick * 1000000) / cpu_tick_frequency);
}