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
typedef  int u8 ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 long EINVAL ; 
 int ingenic_tcu_get_prescale (unsigned long,unsigned long) ; 

__attribute__((used)) static long ingenic_tcu_round_rate(struct clk_hw *hw, unsigned long req_rate,
		unsigned long *parent_rate)
{
	unsigned long rate = *parent_rate;
	u8 prescale;

	if (req_rate > rate)
		return -EINVAL;

	prescale = ingenic_tcu_get_prescale(rate, req_rate);

	return rate >> (prescale * 2);
}