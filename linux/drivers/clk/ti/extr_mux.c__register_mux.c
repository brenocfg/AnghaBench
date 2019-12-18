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
typedef  void* u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct device {int dummy; } ;
struct clk_omap_reg {int dummy; } ;
struct TYPE_2__ {struct clk_init_data* init; } ;
struct clk_omap_mux {TYPE_1__ hw; int /*<<< orphan*/ * table; void* flags; int /*<<< orphan*/  latch; int /*<<< orphan*/  mask; void* shift; int /*<<< orphan*/  reg; } ;
struct clk_init_data {char const* name; unsigned long flags; char const* const* parent_names; void* num_parents; int /*<<< orphan*/ * ops; } ;
struct clk {int dummy; } ;
typedef  int /*<<< orphan*/  s8 ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct clk* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int /*<<< orphan*/  kfree (struct clk_omap_mux*) ; 
 struct clk_omap_mux* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct clk_omap_reg*,int) ; 
 int /*<<< orphan*/  ti_clk_mux_ops ; 
 struct clk* ti_clk_register (struct device*,TYPE_1__*,char const*) ; 

__attribute__((used)) static struct clk *_register_mux(struct device *dev, const char *name,
				 const char * const *parent_names,
				 u8 num_parents, unsigned long flags,
				 struct clk_omap_reg *reg, u8 shift, u32 mask,
				 s8 latch, u8 clk_mux_flags, u32 *table)
{
	struct clk_omap_mux *mux;
	struct clk *clk;
	struct clk_init_data init;

	/* allocate the mux */
	mux = kzalloc(sizeof(*mux), GFP_KERNEL);
	if (!mux)
		return ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &ti_clk_mux_ops;
	init.flags = flags;
	init.parent_names = parent_names;
	init.num_parents = num_parents;

	/* struct clk_mux assignments */
	memcpy(&mux->reg, reg, sizeof(*reg));
	mux->shift = shift;
	mux->mask = mask;
	mux->latch = latch;
	mux->flags = clk_mux_flags;
	mux->table = table;
	mux->hw.init = &init;

	clk = ti_clk_register(dev, &mux->hw, name);

	if (IS_ERR(clk))
		kfree(mux);

	return clk;
}