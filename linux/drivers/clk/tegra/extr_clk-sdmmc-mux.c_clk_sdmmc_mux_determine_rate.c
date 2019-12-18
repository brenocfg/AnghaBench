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
struct tegra_sdmmc_mux {int div_flags; } ;
struct clk_rate_request {unsigned long best_parent_rate; unsigned long rate; int /*<<< orphan*/  max_rate; int /*<<< orphan*/  min_rate; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 unsigned long DIV_ROUND_UP (unsigned long,int) ; 
 unsigned long SDMMC_MUL ; 
 int TEGRA_DIVIDER_ROUND_UP ; 
 int div_frac_get (unsigned long,unsigned long,int,int,int) ; 
 unsigned long max (unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long min (unsigned long,int /*<<< orphan*/ ) ; 
 struct tegra_sdmmc_mux* to_clk_sdmmc_mux (struct clk_hw*) ; 

__attribute__((used)) static int clk_sdmmc_mux_determine_rate(struct clk_hw *hw,
					struct clk_rate_request *req)
{
	struct tegra_sdmmc_mux *sdmmc_mux = to_clk_sdmmc_mux(hw);
	int div;
	unsigned long output_rate = req->best_parent_rate;

	req->rate = max(req->rate, req->min_rate);
	req->rate = min(req->rate, req->max_rate);

	if (!req->rate)
		return output_rate;

	div = div_frac_get(req->rate, output_rate, 8, 1, sdmmc_mux->div_flags);
	if (div < 0)
		div = 0;

	if (sdmmc_mux->div_flags & TEGRA_DIVIDER_ROUND_UP)
		req->rate =  DIV_ROUND_UP(output_rate * SDMMC_MUL,
					  div + SDMMC_MUL);
	else
		req->rate =  output_rate * SDMMC_MUL / (div + SDMMC_MUL);

	return 0;
}