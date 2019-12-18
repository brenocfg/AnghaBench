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

/* Variables and functions */
 int cc_get_imsk () ; 
 int /*<<< orphan*/  cc_set_imsk (int) ; 
 int* cpu_leds ; 
 int hard_smp_processor_id () ; 
 int /*<<< orphan*/  show_leds (int) ; 

void sun4d_cpu_pre_starting(void *arg)
{
	int cpuid = hard_smp_processor_id();

	/* Show we are alive */
	cpu_leds[cpuid] = 0x6;
	show_leds(cpuid);

	/* Enable level15 interrupt, disable level14 interrupt for now */
	cc_set_imsk((cc_get_imsk() & ~0x8000) | 0x4000);
}