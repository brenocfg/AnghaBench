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
struct tegra210_domain_mbist_war {int lvl2_mask; scalar_t__ lvl2_offset; } ;

/* Variables and functions */
 scalar_t__ clk_base ; 
 int /*<<< orphan*/  fence_udelay (int,scalar_t__) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void tegra210_generic_mbist_war(struct tegra210_domain_mbist_war *mbist)
{
	u32 val;

	val = readl_relaxed(clk_base + mbist->lvl2_offset);
	writel_relaxed(val | mbist->lvl2_mask, clk_base + mbist->lvl2_offset);
	fence_udelay(1, clk_base);
	writel_relaxed(val, clk_base + mbist->lvl2_offset);
	fence_udelay(1, clk_base);
}