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
typedef  int /*<<< orphan*/  u32 ;
struct clk_zx_audio {int /*<<< orphan*/  reg_base; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 unsigned long calc_rate (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  readl_relaxed (int /*<<< orphan*/ ) ; 
 struct clk_zx_audio* to_clk_zx_audio (struct clk_hw*) ; 

__attribute__((used)) static unsigned long zx_audio_recalc_rate(struct clk_hw *hw,
					  unsigned long parent_rate)
{
	struct clk_zx_audio *zx_audio = to_clk_zx_audio(hw);
	u32 reg;

	reg = readl_relaxed(zx_audio->reg_base);
	return calc_rate(reg, parent_rate);
}