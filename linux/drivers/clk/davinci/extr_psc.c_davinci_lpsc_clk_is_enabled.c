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
struct davinci_lpsc_clk {int /*<<< orphan*/  md; int /*<<< orphan*/  regmap; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDSTAT (int /*<<< orphan*/ ) ; 
 int MDSTAT_MCKOUT ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 struct davinci_lpsc_clk* to_davinci_lpsc_clk (struct clk_hw*) ; 

__attribute__((used)) static int davinci_lpsc_clk_is_enabled(struct clk_hw *hw)
{
	struct davinci_lpsc_clk *lpsc = to_davinci_lpsc_clk(hw);
	u32 mdstat;

	regmap_read(lpsc->regmap, MDSTAT(lpsc->md), &mdstat);

	return (mdstat & MDSTAT_MCKOUT) ? 1 : 0;
}