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
struct tegra210_domain_mbist_war {int /*<<< orphan*/  clks; scalar_t__ num_clks; int /*<<< orphan*/  (* handle_lvl2_ovr ) (struct tegra210_domain_mbist_war*) ;} ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct tegra210_domain_mbist_war*) ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  clk_bulk_disable_unprepare (scalar_t__,int /*<<< orphan*/ ) ; 
 int clk_bulk_prepare_enable (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lvl2_ovr_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct tegra210_domain_mbist_war*) ; 
 struct tegra210_domain_mbist_war* tegra210_pg_mbist_war ; 

int tegra210_clk_handle_mbist_war(unsigned int id)
{
	int err;
	struct tegra210_domain_mbist_war *mbist_war;

	if (id >= ARRAY_SIZE(tegra210_pg_mbist_war)) {
		WARN(1, "unknown domain id in MBIST WAR handler\n");
		return -EINVAL;
	}

	mbist_war = &tegra210_pg_mbist_war[id];
	if (!mbist_war->handle_lvl2_ovr)
		return 0;

	if (mbist_war->num_clks && !mbist_war->clks)
		return -ENODEV;

	err = clk_bulk_prepare_enable(mbist_war->num_clks, mbist_war->clks);
	if (err < 0)
		return err;

	mutex_lock(&lvl2_ovr_lock);

	mbist_war->handle_lvl2_ovr(mbist_war);

	mutex_unlock(&lvl2_ovr_lock);

	clk_bulk_disable_unprepare(mbist_war->num_clks, mbist_war->clks);

	return 0;
}