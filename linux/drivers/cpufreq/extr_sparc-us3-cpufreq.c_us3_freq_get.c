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
 unsigned int get_current_freq (unsigned int,unsigned long) ; 
 int /*<<< orphan*/  read_safari_cfg ; 
 scalar_t__ smp_call_function_single (unsigned int,int /*<<< orphan*/ ,unsigned long*,int) ; 

__attribute__((used)) static unsigned int us3_freq_get(unsigned int cpu)
{
	unsigned long reg;

	if (smp_call_function_single(cpu, read_safari_cfg, &reg, 1))
		return 0;
	return get_current_freq(cpu, reg);
}