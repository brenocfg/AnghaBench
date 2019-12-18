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
struct ccu_data {int /*<<< orphan*/ * base; int /*<<< orphan*/ * node; } ;

/* Variables and functions */
 int /*<<< orphan*/  ccu_clks_teardown (struct ccu_data*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_clk_del_provider (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kona_ccu_teardown(struct ccu_data *ccu)
{
	if (!ccu->base)
		return;

	of_clk_del_provider(ccu->node);	/* safe if never added */
	ccu_clks_teardown(ccu);
	of_node_put(ccu->node);
	ccu->node = NULL;
	iounmap(ccu->base);
	ccu->base = NULL;
}