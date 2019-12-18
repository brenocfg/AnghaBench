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
typedef  size_t u8 ;
struct tegra_dfll {unsigned long* lut_uv; TYPE_1__* soc; } ;
struct dev_pm_opp {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dev_pm_opp*) ; 
 struct dev_pm_opp* dev_pm_opp_find_freq_ceil (int /*<<< orphan*/ ,unsigned long*) ; 
 unsigned long dev_pm_opp_get_voltage (struct dev_pm_opp*) ; 
 int /*<<< orphan*/  dev_pm_opp_put (struct dev_pm_opp*) ; 

__attribute__((used)) static unsigned long get_dvco_rate_below(struct tegra_dfll *td, u8 out_min)
{
	struct dev_pm_opp *opp;
	unsigned long rate, prev_rate;
	unsigned long uv, min_uv;

	min_uv = td->lut_uv[out_min];
	for (rate = 0, prev_rate = 0; ; rate++) {
		opp = dev_pm_opp_find_freq_ceil(td->soc->dev, &rate);
		if (IS_ERR(opp))
			break;

		uv = dev_pm_opp_get_voltage(opp);
		dev_pm_opp_put(opp);

		if (uv && uv > min_uv)
			return prev_rate;

		prev_rate = rate;
	}

	return prev_rate;
}