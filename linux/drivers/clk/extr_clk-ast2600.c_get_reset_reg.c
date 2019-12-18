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
typedef  int /*<<< orphan*/  u32 ;
struct aspeed_clk_gate {int reset_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASPEED_G6_RESET_CTRL ; 
 int /*<<< orphan*/  ASPEED_G6_RESET_CTRL2 ; 

__attribute__((used)) static u32 get_reset_reg(struct aspeed_clk_gate *gate)
{
	if (gate->reset_idx < 32)
		return ASPEED_G6_RESET_CTRL;

	return ASPEED_G6_RESET_CTRL2;
}