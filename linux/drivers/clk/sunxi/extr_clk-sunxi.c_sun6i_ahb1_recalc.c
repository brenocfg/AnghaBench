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
struct factors_request {int rate; int parent_rate; scalar_t__ parent_index; int m; int p; } ;

/* Variables and functions */
 scalar_t__ SUN6I_AHB1_PARENT_PLL6 ; 

__attribute__((used)) static void sun6i_ahb1_recalc(struct factors_request *req)
{
	req->rate = req->parent_rate;

	/* apply pre-divider first if parent is pll6 */
	if (req->parent_index == SUN6I_AHB1_PARENT_PLL6)
		req->rate /= req->m + 1;

	/* clk divider */
	req->rate >>= req->p;
}