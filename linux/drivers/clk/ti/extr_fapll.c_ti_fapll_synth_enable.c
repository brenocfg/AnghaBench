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
typedef  int u32 ;
struct fapll_synth {int index; TYPE_1__* fd; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ FAPLL_PWD_OFFSET ; 
 int readl_relaxed (scalar_t__) ; 
 struct fapll_synth* to_synth (struct clk_hw*) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int ti_fapll_synth_enable(struct clk_hw *hw)
{
	struct fapll_synth *synth = to_synth(hw);
	u32 v = readl_relaxed(synth->fd->base + FAPLL_PWD_OFFSET);

	v &= ~(1 << synth->index);
	writel_relaxed(v, synth->fd->base + FAPLL_PWD_OFFSET);

	return 0;
}