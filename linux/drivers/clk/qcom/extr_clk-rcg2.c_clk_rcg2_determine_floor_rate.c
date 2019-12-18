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
struct clk_rcg2 {int /*<<< orphan*/  freq_tbl; } ;
struct clk_rate_request {int dummy; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLOOR ; 
 int _freq_tbl_determine_rate (struct clk_hw*,int /*<<< orphan*/ ,struct clk_rate_request*,int /*<<< orphan*/ ) ; 
 struct clk_rcg2* to_clk_rcg2 (struct clk_hw*) ; 

__attribute__((used)) static int clk_rcg2_determine_floor_rate(struct clk_hw *hw,
					 struct clk_rate_request *req)
{
	struct clk_rcg2 *rcg = to_clk_rcg2(hw);

	return _freq_tbl_determine_rate(hw, rcg->freq_tbl, req, FLOOR);
}