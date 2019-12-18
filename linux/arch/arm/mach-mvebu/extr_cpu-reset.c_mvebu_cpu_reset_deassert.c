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
 int /*<<< orphan*/  CPU_RESET_ASSERT ; 
 scalar_t__ CPU_RESET_OFFSET (int) ; 
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ cpu_reset_base ; 
 scalar_t__ cpu_reset_size ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

int mvebu_cpu_reset_deassert(int cpu)
{
	u32 reg;

	if (!cpu_reset_base)
		return -ENODEV;

	if (CPU_RESET_OFFSET(cpu) >= cpu_reset_size)
		return -EINVAL;

	reg = readl(cpu_reset_base + CPU_RESET_OFFSET(cpu));
	reg &= ~CPU_RESET_ASSERT;
	writel(reg, cpu_reset_base + CPU_RESET_OFFSET(cpu));

	return 0;
}