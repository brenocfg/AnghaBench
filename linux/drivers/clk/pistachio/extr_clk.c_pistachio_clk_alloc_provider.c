#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned int clk_num; struct pistachio_clk_provider* clks; } ;
struct pistachio_clk_provider {TYPE_1__ clk_data; int /*<<< orphan*/  base; struct device_node* node; } ;
struct device_node {int dummy; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct pistachio_clk_provider* kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct pistachio_clk_provider*) ; 
 struct pistachio_clk_provider* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_iomap (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

struct pistachio_clk_provider *
pistachio_clk_alloc_provider(struct device_node *node, unsigned int num_clks)
{
	struct pistachio_clk_provider *p;

	p = kzalloc(sizeof(*p), GFP_KERNEL);
	if (!p)
		return p;

	p->clk_data.clks = kcalloc(num_clks, sizeof(struct clk *), GFP_KERNEL);
	if (!p->clk_data.clks)
		goto free_provider;
	p->clk_data.clk_num = num_clks;
	p->node = node;
	p->base = of_iomap(node, 0);
	if (!p->base) {
		pr_err("Failed to map clock provider registers\n");
		goto free_clks;
	}

	return p;

free_clks:
	kfree(p->clk_data.clks);
free_provider:
	kfree(p);
	return NULL;
}