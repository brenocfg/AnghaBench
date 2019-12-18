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
 unsigned int busfreq ; 
 unsigned int powernow_k6_get_cpu_multiplier () ; 

__attribute__((used)) static unsigned int powernow_k6_get(unsigned int cpu)
{
	unsigned int ret;
	ret = (busfreq * powernow_k6_get_cpu_multiplier());
	return ret;
}