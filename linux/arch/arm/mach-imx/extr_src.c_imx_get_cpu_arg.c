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
 scalar_t__ SRC_GPR1 ; 
 int cpu_logical_map (int) ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 scalar_t__ src_base ; 

u32 imx_get_cpu_arg(int cpu)
{
	cpu = cpu_logical_map(cpu);
	return readl_relaxed(src_base + SRC_GPR1 + cpu * 8 + 4);
}