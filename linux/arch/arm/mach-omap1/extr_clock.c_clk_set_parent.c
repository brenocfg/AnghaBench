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
struct clk {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 

int clk_set_parent(struct clk *clk, struct clk *parent)
{
	WARN_ONCE(1, "clk_set_parent() not implemented for OMAP1\n");

	return -EINVAL;
}