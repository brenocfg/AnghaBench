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
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ HIP01_PERI9 ; 
 unsigned int PERI9_CPU1_RESET ; 
 scalar_t__ ctrl_base ; 
 struct device_node* of_find_compatible_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ of_iomap (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 unsigned int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel_relaxed (unsigned int,scalar_t__) ; 

void hip01_set_cpu(int cpu, bool enable)
{
	unsigned int temp;
	struct device_node *np;

	if (!ctrl_base) {
		np = of_find_compatible_node(NULL, NULL, "hisilicon,hip01-sysctrl");
		BUG_ON(!np);
		ctrl_base = of_iomap(np, 0);
		of_node_put(np);
		BUG_ON(!ctrl_base);
	}

	if (enable) {
		/* reset on CPU1  */
		temp = readl_relaxed(ctrl_base + HIP01_PERI9);
		temp |= PERI9_CPU1_RESET;
		writel_relaxed(temp, ctrl_base + HIP01_PERI9);

		udelay(50);

		/* unreset on CPU1 */
		temp = readl_relaxed(ctrl_base + HIP01_PERI9);
		temp &= ~PERI9_CPU1_RESET;
		writel_relaxed(temp, ctrl_base + HIP01_PERI9);
	}
}