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
typedef  int u32 ;
struct clk_pll14xx {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int LOCK_TIMEOUT_US ; 
 int readl_poll_timeout (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int clk_pll14xx_wait_lock(struct clk_pll14xx *pll)
{
	u32 val;

	return readl_poll_timeout(pll->base, val, val & LOCK_TIMEOUT_US, 0,
			LOCK_TIMEOUT_US);
}