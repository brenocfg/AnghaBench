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
struct clk_rate_request {int dummy; } ;
struct clk_hw {int dummy; } ;
struct ccu_mult {int /*<<< orphan*/  mux; int /*<<< orphan*/  common; } ;

/* Variables and functions */
 int /*<<< orphan*/  ccu_mult_round_rate ; 
 int ccu_mux_helper_determine_rate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct clk_rate_request*,int /*<<< orphan*/ ,struct ccu_mult*) ; 
 struct ccu_mult* hw_to_ccu_mult (struct clk_hw*) ; 

__attribute__((used)) static int ccu_mult_determine_rate(struct clk_hw *hw,
				struct clk_rate_request *req)
{
	struct ccu_mult *cm = hw_to_ccu_mult(hw);

	return ccu_mux_helper_determine_rate(&cm->common, &cm->mux,
					     req, ccu_mult_round_rate, cm);
}