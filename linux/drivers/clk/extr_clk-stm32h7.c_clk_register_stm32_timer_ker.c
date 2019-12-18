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
struct clk_hw {struct clk_init_data* init; } ;
struct timer_ker {struct clk_hw hw; int /*<<< orphan*/  dppre_shift; int /*<<< orphan*/ * lock; } ;
struct device {int dummy; } ;
struct clk_init_data {char const* name; unsigned long flags; char const** parent_names; int num_parents; int /*<<< orphan*/ * ops; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 int ENOMEM ; 
 struct clk_hw* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int clk_hw_register (struct device*,struct clk_hw*) ; 
 int /*<<< orphan*/  kfree (struct timer_ker*) ; 
 struct timer_ker* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_ker_ops ; 

__attribute__((used)) static struct clk_hw *clk_register_stm32_timer_ker(struct device *dev,
		const char *name, const char *parent_name,
		unsigned long flags,
		u8 dppre_shift,
		spinlock_t *lock)
{
	struct timer_ker *element;
	struct clk_init_data init;
	struct clk_hw *hw;
	int err;

	element = kzalloc(sizeof(*element), GFP_KERNEL);
	if (!element)
		return ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &timer_ker_ops;
	init.flags = flags;
	init.parent_names = &parent_name;
	init.num_parents = 1;

	element->hw.init = &init;
	element->lock = lock;
	element->dppre_shift = dppre_shift;

	hw = &element->hw;
	err = clk_hw_register(dev, hw);

	if (err) {
		kfree(element);
		return ERR_PTR(err);
	}

	return hw;
}