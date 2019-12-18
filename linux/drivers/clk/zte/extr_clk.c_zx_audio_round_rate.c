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
typedef  int /*<<< orphan*/  u32 ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 long EINVAL ; 
 long calc_rate (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  calc_reg (unsigned long,unsigned long) ; 

__attribute__((used)) static long zx_audio_round_rate(struct clk_hw *hw, unsigned long rate,
				unsigned long *prate)
{
	u32 reg;

	if (rate * 2 > *prate)
		return -EINVAL;

	reg = calc_reg(*prate, rate);
	return calc_rate(reg, *prate);
}