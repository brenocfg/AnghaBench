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
typedef  int /*<<< orphan*/  cpu_tick_f ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_tick_frequency ; 
 unsigned int cpu_tick_variable ; 
 int /*<<< orphan*/ * cpu_ticks ; 
 int /*<<< orphan*/ * tc_cpu_ticks ; 

void
set_cputicker(cpu_tick_f *func, uint64_t freq, unsigned var)
{

	if (func == NULL) {
		cpu_ticks = tc_cpu_ticks;
	} else {
		cpu_tick_frequency = freq;
		cpu_tick_variable = var;
		cpu_ticks = func;
	}
}