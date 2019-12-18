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
struct sprd_clk_common {scalar_t__ reg; int /*<<< orphan*/  regmap; } ;
struct sprd_gate {int flags; int sc_offset; int /*<<< orphan*/  enable_mask; struct sprd_clk_common common; } ;

/* Variables and functions */
 int CLK_GATE_SET_TO_DISABLE ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void clk_sc_gate_toggle(const struct sprd_gate *sg, bool en)
{
	const struct sprd_clk_common *common = &sg->common;
	bool set = sg->flags & CLK_GATE_SET_TO_DISABLE ? 1 : 0;
	unsigned int offset;

	set ^= en;

	/*
	 * Each set/clear gate clock has three registers:
	 * common->reg			- base register
	 * common->reg + offset		- set register
	 * common->reg + 2 * offset	- clear register
	 */
	offset = set ? sg->sc_offset : sg->sc_offset * 2;

	regmap_write(common->regmap, common->reg + offset,
			  sg->enable_mask);
}