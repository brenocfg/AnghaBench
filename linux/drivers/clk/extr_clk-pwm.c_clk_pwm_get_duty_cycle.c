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
struct pwm_state {int /*<<< orphan*/  period; int /*<<< orphan*/  duty_cycle; } ;
struct clk_pwm {int /*<<< orphan*/  pwm; } ;
struct clk_hw {int dummy; } ;
struct clk_duty {int /*<<< orphan*/  den; int /*<<< orphan*/  num; } ;

/* Variables and functions */
 int /*<<< orphan*/  pwm_get_state (int /*<<< orphan*/ ,struct pwm_state*) ; 
 struct clk_pwm* to_clk_pwm (struct clk_hw*) ; 

__attribute__((used)) static int clk_pwm_get_duty_cycle(struct clk_hw *hw, struct clk_duty *duty)
{
	struct clk_pwm *clk_pwm = to_clk_pwm(hw);
	struct pwm_state state;

	pwm_get_state(clk_pwm->pwm, &state);

	duty->num = state.duty_cycle;
	duty->den = state.period;

	return 0;
}