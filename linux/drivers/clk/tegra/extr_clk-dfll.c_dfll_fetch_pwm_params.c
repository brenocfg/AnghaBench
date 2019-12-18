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
typedef  int u32 ;
struct tegra_dfll {int reg_init_uV; int pwm_rate; void* pwm_disable_state; int /*<<< orphan*/  dev; void* pwm_pin; void* pwm_enable_state; TYPE_2__* soc; scalar_t__* lut_uv; } ;
struct TYPE_3__ {int step_uv; scalar_t__ offset_uv; } ;
struct TYPE_4__ {TYPE_1__ alignment; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (void*) ; 
 int MAX_DFLL_VOLTAGES ; 
 int NSEC_PER_SEC ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 void* devm_pinctrl_get (int /*<<< orphan*/ ) ; 
 void* pinctrl_lookup_state (void*,char*) ; 
 int read_dt_param (struct tegra_dfll*,char*,int*) ; 

__attribute__((used)) static int dfll_fetch_pwm_params(struct tegra_dfll *td)
{
	int ret, i;
	u32 pwm_period;

	if (!td->soc->alignment.step_uv || !td->soc->alignment.offset_uv) {
		dev_err(td->dev,
			"Missing step or alignment info for PWM regulator");
		return -EINVAL;
	}
	for (i = 0; i < MAX_DFLL_VOLTAGES; i++)
		td->lut_uv[i] = td->soc->alignment.offset_uv +
				i * td->soc->alignment.step_uv;

	ret = read_dt_param(td, "nvidia,pwm-tristate-microvolts",
			    &td->reg_init_uV);
	if (!ret) {
		dev_err(td->dev, "couldn't get initialized voltage\n");
		return ret;
	}

	ret = read_dt_param(td, "nvidia,pwm-period-nanoseconds", &pwm_period);
	if (!ret) {
		dev_err(td->dev, "couldn't get PWM period\n");
		return ret;
	}
	td->pwm_rate = (NSEC_PER_SEC / pwm_period) * (MAX_DFLL_VOLTAGES - 1);

	td->pwm_pin = devm_pinctrl_get(td->dev);
	if (IS_ERR(td->pwm_pin)) {
		dev_err(td->dev, "DT: missing pinctrl device\n");
		return PTR_ERR(td->pwm_pin);
	}

	td->pwm_enable_state = pinctrl_lookup_state(td->pwm_pin,
						    "dvfs_pwm_enable");
	if (IS_ERR(td->pwm_enable_state)) {
		dev_err(td->dev, "DT: missing pwm enabled state\n");
		return PTR_ERR(td->pwm_enable_state);
	}

	td->pwm_disable_state = pinctrl_lookup_state(td->pwm_pin,
						     "dvfs_pwm_disable");
	if (IS_ERR(td->pwm_disable_state)) {
		dev_err(td->dev, "DT: missing pwm disabled state\n");
		return PTR_ERR(td->pwm_disable_state);
	}

	return 0;
}