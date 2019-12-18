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
struct clk_rate_request {unsigned int rate; unsigned int best_parent_rate; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_CLOSEST (unsigned int,unsigned int) ; 
 int EINVAL ; 

__attribute__((used)) static int iproc_clk_determine_rate(struct clk_hw *hw,
		struct clk_rate_request *req)
{
	unsigned int bestdiv;

	if (req->rate == 0)
		return -EINVAL;
	if (req->rate == req->best_parent_rate)
		return 0;

	bestdiv = DIV_ROUND_CLOSEST(req->best_parent_rate, req->rate);
	if (bestdiv < 2)
		req->rate = req->best_parent_rate;

	if (bestdiv > 256)
		bestdiv = 256;

	req->rate = req->best_parent_rate / bestdiv;

	return 0;
}