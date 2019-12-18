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
struct TYPE_2__ {struct clk_init_data* init; } ;
struct krait_div2_clk {int width; int shift; int lpl; unsigned int offset; TYPE_1__ hw; } ;
struct device {int dummy; } ;
struct clk_init_data {int num_parents; char const* name; char const** parent_names; int /*<<< orphan*/  flags; int /*<<< orphan*/ * ops; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_SET_RATE_PARENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PTR_ERR_OR_ZERO (struct clk*) ; 
 struct clk* devm_clk_register (struct device*,TYPE_1__*) ; 
 struct krait_div2_clk* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 void* kasprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  kfree (char const*) ; 
 int /*<<< orphan*/  krait_div2_clk_ops ; 

__attribute__((used)) static int
krait_add_div(struct device *dev, int id, const char *s, unsigned int offset)
{
	struct krait_div2_clk *div;
	struct clk_init_data init = {
		.num_parents = 1,
		.ops = &krait_div2_clk_ops,
		.flags = CLK_SET_RATE_PARENT,
	};
	const char *p_names[1];
	struct clk *clk;

	div = devm_kzalloc(dev, sizeof(*div), GFP_KERNEL);
	if (!div)
		return -ENOMEM;

	div->width = 2;
	div->shift = 6;
	div->lpl = id >= 0;
	div->offset = offset;
	div->hw.init = &init;

	init.name = kasprintf(GFP_KERNEL, "hfpll%s_div", s);
	if (!init.name)
		return -ENOMEM;

	init.parent_names = p_names;
	p_names[0] = kasprintf(GFP_KERNEL, "hfpll%s", s);
	if (!p_names[0]) {
		kfree(init.name);
		return -ENOMEM;
	}

	clk = devm_clk_register(dev, &div->hw);
	kfree(p_names[0]);
	kfree(init.name);

	return PTR_ERR_OR_ZERO(clk);
}