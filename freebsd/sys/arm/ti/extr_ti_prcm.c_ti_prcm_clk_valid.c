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
typedef  int /*<<< orphan*/  clk_ident_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/ * ti_prcm_clk_dev (int /*<<< orphan*/ ) ; 

int
ti_prcm_clk_valid(clk_ident_t clk)
{
	int ret = 0;

	if (ti_prcm_clk_dev(clk) == NULL)
		ret = EINVAL;
	
	return (ret);
}