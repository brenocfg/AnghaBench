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
 int MAX_CLUSTERS ; 
 scalar_t__ is_bL_switching_enabled () ; 
 int raw_cpu_to_cluster (int) ; 

__attribute__((used)) static inline int cpu_to_cluster(int cpu)
{
	return is_bL_switching_enabled() ?
		MAX_CLUSTERS : raw_cpu_to_cluster(cpu);
}