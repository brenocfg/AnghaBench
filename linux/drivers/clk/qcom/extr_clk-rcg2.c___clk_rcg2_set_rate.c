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
struct freq_tbl {int dummy; } ;
struct clk_rcg2 {int /*<<< orphan*/  freq_tbl; } ;
struct clk_hw {int dummy; } ;
typedef  enum freq_policy { ____Placeholder_freq_policy } freq_policy ;

/* Variables and functions */
#define  CEIL 129 
 int EINVAL ; 
#define  FLOOR 128 
 int clk_rcg2_configure (struct clk_rcg2*,struct freq_tbl const*) ; 
 struct freq_tbl* qcom_find_freq (int /*<<< orphan*/ ,unsigned long) ; 
 struct freq_tbl* qcom_find_freq_floor (int /*<<< orphan*/ ,unsigned long) ; 
 struct clk_rcg2* to_clk_rcg2 (struct clk_hw*) ; 

__attribute__((used)) static int __clk_rcg2_set_rate(struct clk_hw *hw, unsigned long rate,
			       enum freq_policy policy)
{
	struct clk_rcg2 *rcg = to_clk_rcg2(hw);
	const struct freq_tbl *f;

	switch (policy) {
	case FLOOR:
		f = qcom_find_freq_floor(rcg->freq_tbl, rate);
		break;
	case CEIL:
		f = qcom_find_freq(rcg->freq_tbl, rate);
		break;
	default:
		return -EINVAL;
	};

	if (!f)
		return -EINVAL;

	return clk_rcg2_configure(rcg, f);
}