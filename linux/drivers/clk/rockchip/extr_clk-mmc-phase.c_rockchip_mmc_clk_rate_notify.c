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
struct rockchip_mmc_clock {int /*<<< orphan*/  cached_phase; int /*<<< orphan*/  hw; } ;
struct notifier_block {int dummy; } ;
struct clk_notifier_data {scalar_t__ old_rate; scalar_t__ new_rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int NOTIFY_DONE ; 
 unsigned long POST_RATE_CHANGE ; 
 unsigned long PRE_RATE_CHANGE ; 
 int /*<<< orphan*/  rockchip_mmc_get_phase (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rockchip_mmc_set_phase (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct rockchip_mmc_clock* to_rockchip_mmc_clock (struct notifier_block*) ; 

__attribute__((used)) static int rockchip_mmc_clk_rate_notify(struct notifier_block *nb,
					unsigned long event, void *data)
{
	struct rockchip_mmc_clock *mmc_clock = to_rockchip_mmc_clock(nb);
	struct clk_notifier_data *ndata = data;

	/*
	 * rockchip_mmc_clk is mostly used by mmc controllers to sample
	 * the intput data, which expects the fixed phase after the tuning
	 * process. However if the clock rate is changed, the phase is stale
	 * and may break the data sampling. So here we try to restore the phase
	 * for that case, except that
	 * (1) cached_phase is invaild since we inevitably cached it when the
	 * clock provider be reparented from orphan to its real parent in the
	 * first place. Otherwise we may mess up the initialization of MMC cards
	 * since we only set the default sample phase and drive phase later on.
	 * (2) the new coming rate is higher than the older one since mmc driver
	 * set the max-frequency to match the boards' ability but we can't go
	 * over the heads of that, otherwise the tests smoke out the issue.
	 */
	if (ndata->old_rate <= ndata->new_rate)
		return NOTIFY_DONE;

	if (event == PRE_RATE_CHANGE)
		mmc_clock->cached_phase =
			rockchip_mmc_get_phase(&mmc_clock->hw);
	else if (mmc_clock->cached_phase != -EINVAL &&
		 event == POST_RATE_CHANGE)
		rockchip_mmc_set_phase(&mmc_clock->hw, mmc_clock->cached_phase);

	return NOTIFY_DONE;
}