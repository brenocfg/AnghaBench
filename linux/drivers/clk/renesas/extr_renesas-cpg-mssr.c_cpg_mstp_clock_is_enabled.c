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
typedef  int u32 ;
struct mstp_clock {int index; struct cpg_mssr_priv* priv; } ;
struct cpg_mssr_priv {scalar_t__ base; scalar_t__ stbyctrl; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 scalar_t__ MSTPSR (int) ; 
 scalar_t__ STBCR (int) ; 
 int readb (scalar_t__) ; 
 int readl (scalar_t__) ; 
 struct mstp_clock* to_mstp_clock (struct clk_hw*) ; 

__attribute__((used)) static int cpg_mstp_clock_is_enabled(struct clk_hw *hw)
{
	struct mstp_clock *clock = to_mstp_clock(hw);
	struct cpg_mssr_priv *priv = clock->priv;
	u32 value;

	if (priv->stbyctrl)
		value = readb(priv->base + STBCR(clock->index / 32));
	else
		value = readl(priv->base + MSTPSR(clock->index / 32));

	return !(value & BIT(clock->index % 32));
}