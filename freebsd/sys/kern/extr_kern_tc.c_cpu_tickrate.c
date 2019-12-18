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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_tick_frequency ; 
 scalar_t__ cpu_ticks ; 
 scalar_t__ tc_cpu_ticks ; 
 int /*<<< orphan*/  tc_getfrequency () ; 

uint64_t
cpu_tickrate(void)
{

	if (cpu_ticks == tc_cpu_ticks) 
		return (tc_getfrequency());
	return (cpu_tick_frequency);
}