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
 scalar_t__ SRC_GPR1 ; 
 int /*<<< orphan*/  __pa_symbol (void*) ; 
 int cpu_logical_map (int) ; 
 scalar_t__ src_base ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

void imx_set_cpu_jump(int cpu, void *jump_addr)
{
	cpu = cpu_logical_map(cpu);
	writel_relaxed(__pa_symbol(jump_addr),
		       src_base + SRC_GPR1 + cpu * 8);
}