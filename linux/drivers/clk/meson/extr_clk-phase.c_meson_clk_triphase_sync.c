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
struct meson_clk_triphase_data {int /*<<< orphan*/  ph2; int /*<<< orphan*/  ph1; int /*<<< orphan*/  ph0; } ;
struct clk_regmap {int /*<<< orphan*/  map; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 struct meson_clk_triphase_data* meson_clk_triphase_data (struct clk_regmap*) ; 
 unsigned int meson_parm_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  meson_parm_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 
 struct clk_regmap* to_clk_regmap (struct clk_hw*) ; 

__attribute__((used)) static void meson_clk_triphase_sync(struct clk_hw *hw)
{
	struct clk_regmap *clk = to_clk_regmap(hw);
	struct meson_clk_triphase_data *tph = meson_clk_triphase_data(clk);
	unsigned int val;

	/* Get phase 0 and sync it to phase 1 and 2 */
	val = meson_parm_read(clk->map, &tph->ph0);
	meson_parm_write(clk->map, &tph->ph1, val);
	meson_parm_write(clk->map, &tph->ph2, val);
}