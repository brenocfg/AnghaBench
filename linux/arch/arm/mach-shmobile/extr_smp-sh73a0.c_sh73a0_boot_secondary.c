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
struct task_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PSTR ; 
 int /*<<< orphan*/  SRESCR ; 
 int /*<<< orphan*/  WUPCR ; 
 int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ ) ; 
 unsigned int cpu_logical_map (unsigned int) ; 

__attribute__((used)) static int sh73a0_boot_secondary(unsigned int cpu, struct task_struct *idle)
{
	unsigned int lcpu = cpu_logical_map(cpu);

	if (((__raw_readl(PSTR) >> (4 * lcpu)) & 3) == 3)
		__raw_writel(1 << lcpu, WUPCR);	/* wake up */
	else
		__raw_writel(1 << lcpu, SRESCR);	/* reset */

	return 0;
}