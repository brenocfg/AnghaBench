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
 int cpu_number_map (int) ; 
 int smp_processor_id () ; 

__attribute__((used)) static int octeon_cpu_for_coreid(int coreid)
{
#ifdef CONFIG_SMP
	return cpu_number_map(coreid);
#else
	return smp_processor_id();
#endif
}