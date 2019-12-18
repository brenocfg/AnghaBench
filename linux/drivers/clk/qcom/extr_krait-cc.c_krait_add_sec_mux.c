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
struct krait_mux_clk {unsigned int offset; int lpl; int mask; int shift; TYPE_1__ hw; scalar_t__ safe_sel; int /*<<< orphan*/  parent_map; } ;
struct device {int dummy; } ;
struct clk_init_data {char const** parent_names; char const* name; int /*<<< orphan*/  flags; int /*<<< orphan*/ * ops; int /*<<< orphan*/  num_parents; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (char const**) ; 
 int /*<<< orphan*/  CLK_SET_RATE_PARENT ; 
 int ENOMEM ; 
 struct clk* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PTR_ERR_OR_ZERO (struct clk*) ; 
 struct clk* devm_clk_register (struct device*,TYPE_1__*) ; 
 struct krait_mux_clk* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 void* kasprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  kfree (char const*) ; 
 int /*<<< orphan*/  krait_mux_clk_ops ; 
 int krait_notifier_register (struct device*,struct clk*,struct krait_mux_clk*) ; 
 int /*<<< orphan*/  sec_mux_map ; 

__attribute__((used)) static int
krait_add_sec_mux(struct device *dev, int id, const char *s,
		  unsigned int offset, bool unique_aux)
{
	int ret;
	struct krait_mux_clk *mux;
	static const char *sec_mux_list[] = {
		"acpu_aux",
		"qsb",
	};
	struct clk_init_data init = {
		.parent_names = sec_mux_list,
		.num_parents = ARRAY_SIZE(sec_mux_list),
		.ops = &krait_mux_clk_ops,
		.flags = CLK_SET_RATE_PARENT,
	};
	struct clk *clk;

	mux = devm_kzalloc(dev, sizeof(*mux), GFP_KERNEL);
	if (!mux)
		return -ENOMEM;

	mux->offset = offset;
	mux->lpl = id >= 0;
	mux->mask = 0x3;
	mux->shift = 2;
	mux->parent_map = sec_mux_map;
	mux->hw.init = &init;
	mux->safe_sel = 0;

	init.name = kasprintf(GFP_KERNEL, "krait%s_sec_mux", s);
	if (!init.name)
		return -ENOMEM;

	if (unique_aux) {
		sec_mux_list[0] = kasprintf(GFP_KERNEL, "acpu%s_aux", s);
		if (!sec_mux_list[0]) {
			clk = ERR_PTR(-ENOMEM);
			goto err_aux;
		}
	}

	clk = devm_clk_register(dev, &mux->hw);

	ret = krait_notifier_register(dev, clk, mux);
	if (ret)
		goto unique_aux;

unique_aux:
	if (unique_aux)
		kfree(sec_mux_list[0]);
err_aux:
	kfree(init.name);
	return PTR_ERR_OR_ZERO(clk);
}