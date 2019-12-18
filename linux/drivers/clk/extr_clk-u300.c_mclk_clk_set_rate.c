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
typedef  int u16 ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ U300_SYSCON_MMF0R ; 
 int U300_SYSCON_MMF0R_MASK ; 
 int readw (scalar_t__) ; 
 scalar_t__ syscon_vbase ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static int mclk_clk_set_rate(struct clk_hw *hw, unsigned long rate,
			     unsigned long parent_rate)
{
	u16 val;
	u16 reg;

	switch (rate) {
	case 18900000:
		val = 0x0054;
		break;
	case 20800000:
		val = 0x0044;
		break;
	case 23100000:
		val = 0x0043;
		break;
	case 26000000:
		val = 0x0033;
		break;
	case 29700000:
		val = 0x0032;
		break;
	case 34700000:
		val = 0x0022;
		break;
	case 41600000:
		val = 0x0021;
		break;
	case 52000000:
		val = 0x0011;
		break;
	case 104000000:
		val = 0x0000;
		break;
	default:
		return -EINVAL;
	}

	reg = readw(syscon_vbase + U300_SYSCON_MMF0R) &
		~U300_SYSCON_MMF0R_MASK;
	writew(reg | val, syscon_vbase + U300_SYSCON_MMF0R);
	return 0;
}