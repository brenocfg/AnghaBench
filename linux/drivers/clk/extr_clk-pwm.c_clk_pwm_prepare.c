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
struct clk_pwm {int /*<<< orphan*/  pwm; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int pwm_enable (int /*<<< orphan*/ ) ; 
 struct clk_pwm* to_clk_pwm (struct clk_hw*) ; 

__attribute__((used)) static int clk_pwm_prepare(struct clk_hw *hw)
{
	struct clk_pwm *clk_pwm = to_clk_pwm(hw);

	return pwm_enable(clk_pwm->pwm);
}