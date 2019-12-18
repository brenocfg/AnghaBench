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
 int MAX_CPUS_PER_CLUSTER ; 
 int** mcpm_cpu_use_count ; 

__attribute__((used)) static inline bool mcpm_cluster_unused(unsigned int cluster)
{
	int i, cnt;
	for (i = 0, cnt = 0; i < MAX_CPUS_PER_CLUSTER; i++)
		cnt |= mcpm_cpu_use_count[cluster][i];
	return !cnt;
}