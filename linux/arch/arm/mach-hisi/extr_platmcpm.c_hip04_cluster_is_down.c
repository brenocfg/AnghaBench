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
 int HIP04_MAX_CPUS_PER_CLUSTER ; 
 scalar_t__** hip04_cpu_table ; 

__attribute__((used)) static bool hip04_cluster_is_down(unsigned int cluster)
{
	int i;

	for (i = 0; i < HIP04_MAX_CPUS_PER_CLUSTER; i++)
		if (hip04_cpu_table[cluster][i])
			return false;
	return true;
}