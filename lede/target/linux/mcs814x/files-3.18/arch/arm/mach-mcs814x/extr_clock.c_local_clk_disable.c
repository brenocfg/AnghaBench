#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct clk {scalar_t__ usecount; struct clk* parent; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* enable ) (struct clk*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  stub1 (struct clk*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void local_clk_disable(struct clk *clk)
{
	WARN_ON(!clk->usecount);

	if (clk->usecount > 0) {
		clk->usecount--;

		if ((clk->usecount == 0) && (clk->ops->enable))
			clk->ops->enable(clk, 0);

		if (clk->parent)
			local_clk_disable(clk->parent);
	}
}