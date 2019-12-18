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
struct clk_rate_request {int /*<<< orphan*/  best_parent_rate; int /*<<< orphan*/ * best_parent_hw; } ;
struct clk_core {int /*<<< orphan*/  rate; int /*<<< orphan*/ * hw; struct clk_core* parent; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 

__attribute__((used)) static void clk_core_init_rate_req(struct clk_core * const core,
				   struct clk_rate_request *req)
{
	struct clk_core *parent;

	if (WARN_ON(!core || !req))
		return;

	parent = core->parent;
	if (parent) {
		req->best_parent_hw = parent->hw;
		req->best_parent_rate = parent->rate;
	} else {
		req->best_parent_hw = NULL;
		req->best_parent_rate = 0;
	}
}