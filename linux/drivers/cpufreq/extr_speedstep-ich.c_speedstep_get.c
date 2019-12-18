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
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_freq_data ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned int) ; 
 int /*<<< orphan*/  smp_call_function_single (unsigned int,int /*<<< orphan*/ ,unsigned int*,int) ; 

__attribute__((used)) static unsigned int speedstep_get(unsigned int cpu)
{
	unsigned int speed;

	/* You're supposed to ensure CPU is online. */
	BUG_ON(smp_call_function_single(cpu, get_freq_data, &speed, 1));

	pr_debug("detected %u kHz as current frequency\n", speed);
	return speed;
}