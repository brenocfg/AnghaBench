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
 int /*<<< orphan*/  api_ck_p ; 
 int /*<<< orphan*/  omap1_clk_disable (int /*<<< orphan*/ ) ; 
 int omap1_clk_enable (int /*<<< orphan*/ ) ; 
 int omap1_clk_enable_generic (struct clk*) ; 

__attribute__((used)) static int omap1_clk_enable_dsp_domain(struct clk *clk)
{
	int retval;

	retval = omap1_clk_enable(api_ck_p);
	if (!retval) {
		retval = omap1_clk_enable_generic(clk);
		omap1_clk_disable(api_ck_p);
	}

	return retval;
}