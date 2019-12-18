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
typedef  int u8 ;
typedef  int u32 ;
struct mtk_clk_mux {scalar_t__ lock; TYPE_1__* data; int /*<<< orphan*/  regmap; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {int mux_shift; scalar_t__ upd_shift; int /*<<< orphan*/  upd_ofs; int /*<<< orphan*/  set_ofs; int /*<<< orphan*/  clr_ofs; int /*<<< orphan*/  mux_ofs; scalar_t__ mux_width; } ;

/* Variables and functions */
 int BIT (scalar_t__) ; 
 int GENMASK (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __acquire (scalar_t__) ; 
 int /*<<< orphan*/  __release (scalar_t__) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (scalar_t__,unsigned long) ; 
 struct mtk_clk_mux* to_mtk_clk_mux (struct clk_hw*) ; 

__attribute__((used)) static int mtk_clk_mux_set_parent_setclr_lock(struct clk_hw *hw, u8 index)
{
	struct mtk_clk_mux *mux = to_mtk_clk_mux(hw);
	u32 mask = GENMASK(mux->data->mux_width - 1, 0);
	u32 val, orig;
	unsigned long flags = 0;

	if (mux->lock)
		spin_lock_irqsave(mux->lock, flags);
	else
		__acquire(mux->lock);

	regmap_read(mux->regmap, mux->data->mux_ofs, &orig);
	val = (orig & ~(mask << mux->data->mux_shift))
			| (index << mux->data->mux_shift);

	if (val != orig) {
		regmap_write(mux->regmap, mux->data->clr_ofs,
				mask << mux->data->mux_shift);
		regmap_write(mux->regmap, mux->data->set_ofs,
				index << mux->data->mux_shift);

		if (mux->data->upd_shift >= 0)
			regmap_write(mux->regmap, mux->data->upd_ofs,
					BIT(mux->data->upd_shift));
	}

	if (mux->lock)
		spin_unlock_irqrestore(mux->lock, flags);
	else
		__release(mux->lock);

	return 0;
}