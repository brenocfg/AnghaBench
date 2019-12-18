#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct tegra_dfll {unsigned long* lut_uv; int* lut; int lut_size; int lut_bottom; unsigned long dvco_rate_min; TYPE_2__* soc; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {TYPE_1__* cvb; } ;
struct TYPE_3__ {int min_millivolts; } ;

/* Variables and functions */
 int EINVAL ; 
 int MAX_DFLL_VOLTAGES ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 unsigned long get_dvco_rate_below (struct tegra_dfll*,int) ; 

__attribute__((used)) static int dfll_build_pwm_lut(struct tegra_dfll *td, unsigned long v_max)
{
	int i;
	unsigned long rate, reg_volt;
	u8 lut_bottom = MAX_DFLL_VOLTAGES;
	int v_min = td->soc->cvb->min_millivolts * 1000;

	for (i = 0; i < MAX_DFLL_VOLTAGES; i++) {
		reg_volt = td->lut_uv[i];

		/* since opp voltage is exact mv */
		reg_volt = (reg_volt / 1000) * 1000;
		if (reg_volt > v_max)
			break;

		td->lut[i] = i;
		if ((lut_bottom == MAX_DFLL_VOLTAGES) && (reg_volt >= v_min))
			lut_bottom = i;
	}

	/* determine voltage boundaries */
	td->lut_size = i;
	if ((lut_bottom == MAX_DFLL_VOLTAGES) ||
	    (lut_bottom + 1 >= td->lut_size)) {
		dev_err(td->dev, "no voltage above DFLL minimum %d mV\n",
			td->soc->cvb->min_millivolts);
		return -EINVAL;
	}
	td->lut_bottom = lut_bottom;

	/* determine rate boundaries */
	rate = get_dvco_rate_below(td, td->lut_bottom);
	if (!rate) {
		dev_err(td->dev, "no opp below DFLL minimum voltage %d mV\n",
			td->soc->cvb->min_millivolts);
		return -EINVAL;
	}
	td->dvco_rate_min = rate;

	return 0;
}