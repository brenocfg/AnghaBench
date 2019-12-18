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
typedef  int /*<<< orphan*/  u8 ;
struct gpio_desc {int dummy; } ;
struct device {int dummy; } ;
struct clk_ops {int dummy; } ;
struct clk_init_data {char const* name; unsigned long flags; char const* const* parent_names; int /*<<< orphan*/  num_parents; struct clk_ops const* ops; } ;
struct clk_hw {struct clk_init_data* init; } ;
struct clk_gpio {struct clk_hw hw; struct gpio_desc* gpiod; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct clk_hw* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int clk_hw_register (int /*<<< orphan*/ *,struct clk_hw*) ; 
 int devm_clk_hw_register (struct device*,struct clk_hw*) ; 
 struct clk_gpio* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct clk_gpio*) ; 
 struct clk_gpio* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct clk_hw *clk_register_gpio(struct device *dev, const char *name,
		const char * const *parent_names, u8 num_parents, struct gpio_desc *gpiod,
		unsigned long flags, const struct clk_ops *clk_gpio_ops)
{
	struct clk_gpio *clk_gpio;
	struct clk_hw *hw;
	struct clk_init_data init = {};
	int err;

	if (dev)
		clk_gpio = devm_kzalloc(dev, sizeof(*clk_gpio),	GFP_KERNEL);
	else
		clk_gpio = kzalloc(sizeof(*clk_gpio), GFP_KERNEL);

	if (!clk_gpio)
		return ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = clk_gpio_ops;
	init.flags = flags;
	init.parent_names = parent_names;
	init.num_parents = num_parents;

	clk_gpio->gpiod = gpiod;
	clk_gpio->hw.init = &init;

	hw = &clk_gpio->hw;
	if (dev)
		err = devm_clk_hw_register(dev, hw);
	else
		err = clk_hw_register(NULL, hw);

	if (!err)
		return hw;

	if (!dev) {
		kfree(clk_gpio);
	}

	return ERR_PTR(err);
}