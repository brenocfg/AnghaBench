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
struct tegra_gmi {scalar_t__ base; int /*<<< orphan*/  snor_config; int /*<<< orphan*/  snor_timing1; int /*<<< orphan*/  snor_timing0; int /*<<< orphan*/  rst; int /*<<< orphan*/  dev; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 scalar_t__ TEGRA_GMI_CONFIG ; 
 int /*<<< orphan*/  TEGRA_GMI_CONFIG_GO ; 
 scalar_t__ TEGRA_GMI_TIMING0 ; 
 scalar_t__ TEGRA_GMI_TIMING1 ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_deassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int tegra_gmi_enable(struct tegra_gmi *gmi)
{
	int err;

	err = clk_prepare_enable(gmi->clk);
	if (err < 0) {
		dev_err(gmi->dev, "failed to enable clock: %d\n", err);
		return err;
	}

	reset_control_assert(gmi->rst);
	usleep_range(2000, 4000);
	reset_control_deassert(gmi->rst);

	writel(gmi->snor_timing0, gmi->base + TEGRA_GMI_TIMING0);
	writel(gmi->snor_timing1, gmi->base + TEGRA_GMI_TIMING1);

	gmi->snor_config |= TEGRA_GMI_CONFIG_GO;
	writel(gmi->snor_config, gmi->base + TEGRA_GMI_CONFIG);

	return 0;
}