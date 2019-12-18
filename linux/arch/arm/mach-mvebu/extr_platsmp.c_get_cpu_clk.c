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
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct clk*) ; 
 scalar_t__ WARN (int,char*) ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 struct clk* of_clk_get (struct device_node*,int /*<<< orphan*/ ) ; 
 struct device_node* of_get_cpu_node (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct clk *get_cpu_clk(int cpu)
{
	struct clk *cpu_clk;
	struct device_node *np = of_get_cpu_node(cpu, NULL);

	if (WARN(!np, "missing cpu node\n"))
		return NULL;
	cpu_clk = of_clk_get(np, 0);
	if (WARN_ON(IS_ERR(cpu_clk)))
		return NULL;
	return cpu_clk;
}