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
struct TYPE_2__ {int num; int /*<<< orphan*/  den; } ;
struct meson_sclk_div_data {int cached_div; int /*<<< orphan*/  hi; TYPE_1__ cached_duty; } ;
struct clk_regmap {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_CLOSEST (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  meson_parm_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void sclk_apply_ratio(struct clk_regmap *clk,
			     struct meson_sclk_div_data *sclk)
{
	unsigned int hi = DIV_ROUND_CLOSEST(sclk->cached_div *
					    sclk->cached_duty.num,
					    sclk->cached_duty.den);

	if (hi)
		hi -= 1;

	meson_parm_write(clk->map, &sclk->hi, hi);
}