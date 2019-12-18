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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  STANDBYWFI_STAT_A15_CPU_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STANDBYWFI_STAT_A7_CPU_MASK (int /*<<< orphan*/ ) ; 
 scalar_t__ cluster_is_a15 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 standbywfi_cpu_mask(u32 cpu, u32 cluster)
{
	return cluster_is_a15(cluster) ?
		  STANDBYWFI_STAT_A15_CPU_MASK(cpu)
		: STANDBYWFI_STAT_A7_CPU_MASK(cpu);
}