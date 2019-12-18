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
struct device_node {int dummy; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __clk_register (int /*<<< orphan*/ *,struct device_node*,struct clk_hw*) ; 

int of_clk_hw_register(struct device_node *node, struct clk_hw *hw)
{
	return PTR_ERR_OR_ZERO(__clk_register(NULL, node, hw));
}