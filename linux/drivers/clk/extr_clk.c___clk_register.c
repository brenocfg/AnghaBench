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
struct device_node {int dummy; } ;
struct device {TYPE_1__* driver; } ;
struct clk_init_data {int /*<<< orphan*/  num_parents; int /*<<< orphan*/  flags; scalar_t__ ops; int /*<<< orphan*/  name; } ;
struct clk_hw {struct clk* clk; struct clk_core* core; struct clk_init_data* init; } ;
struct clk_core {int rpm_enabled; int /*<<< orphan*/  name; int /*<<< orphan*/  clks; int /*<<< orphan*/  max_rate; scalar_t__ min_rate; int /*<<< orphan*/  num_parents; int /*<<< orphan*/  flags; struct clk_hw* hw; int /*<<< orphan*/  owner; struct device_node* of_node; struct device* dev; scalar_t__ ops; } ;
struct clk {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct clk* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 int /*<<< orphan*/  ULONG_MAX ; 
 scalar_t__ WARN_ON (int) ; 
 int __clk_core_init (struct clk_core*) ; 
 struct clk* alloc_clk (struct clk_core*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_core_free_parent_map (struct clk_core*) ; 
 int /*<<< orphan*/  clk_core_link_consumer (struct clk_core*,struct clk*) ; 
 int clk_core_populate_parent_map (struct clk_core*,struct clk_init_data const*) ; 
 int /*<<< orphan*/  clk_core_unlink_consumer (struct clk*) ; 
 int /*<<< orphan*/  clk_prepare_lock () ; 
 int /*<<< orphan*/  clk_prepare_unlock () ; 
 int /*<<< orphan*/  free_clk (struct clk*) ; 
 int /*<<< orphan*/  kfree (struct clk_core*) ; 
 int /*<<< orphan*/  kfree_const (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kstrdup_const (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct clk_core* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ pm_runtime_enabled (struct device*) ; 

__attribute__((used)) static struct clk *
__clk_register(struct device *dev, struct device_node *np, struct clk_hw *hw)
{
	int ret;
	struct clk_core *core;
	const struct clk_init_data *init = hw->init;

	/*
	 * The init data is not supposed to be used outside of registration path.
	 * Set it to NULL so that provider drivers can't use it either and so that
	 * we catch use of hw->init early on in the core.
	 */
	hw->init = NULL;

	core = kzalloc(sizeof(*core), GFP_KERNEL);
	if (!core) {
		ret = -ENOMEM;
		goto fail_out;
	}

	core->name = kstrdup_const(init->name, GFP_KERNEL);
	if (!core->name) {
		ret = -ENOMEM;
		goto fail_name;
	}

	if (WARN_ON(!init->ops)) {
		ret = -EINVAL;
		goto fail_ops;
	}
	core->ops = init->ops;

	if (dev && pm_runtime_enabled(dev))
		core->rpm_enabled = true;
	core->dev = dev;
	core->of_node = np;
	if (dev && dev->driver)
		core->owner = dev->driver->owner;
	core->hw = hw;
	core->flags = init->flags;
	core->num_parents = init->num_parents;
	core->min_rate = 0;
	core->max_rate = ULONG_MAX;
	hw->core = core;

	ret = clk_core_populate_parent_map(core, init);
	if (ret)
		goto fail_parents;

	INIT_HLIST_HEAD(&core->clks);

	/*
	 * Don't call clk_hw_create_clk() here because that would pin the
	 * provider module to itself and prevent it from ever being removed.
	 */
	hw->clk = alloc_clk(core, NULL, NULL);
	if (IS_ERR(hw->clk)) {
		ret = PTR_ERR(hw->clk);
		goto fail_create_clk;
	}

	clk_core_link_consumer(hw->core, hw->clk);

	ret = __clk_core_init(core);
	if (!ret)
		return hw->clk;

	clk_prepare_lock();
	clk_core_unlink_consumer(hw->clk);
	clk_prepare_unlock();

	free_clk(hw->clk);
	hw->clk = NULL;

fail_create_clk:
	clk_core_free_parent_map(core);
fail_parents:
fail_ops:
	kfree_const(core->name);
fail_name:
	kfree(core);
fail_out:
	return ERR_PTR(ret);
}