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
struct clk_pfdv2 {int vld_bit; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK_TIMEOUT_US ; 
 int readl_poll_timeout (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int clk_pfdv2_wait(struct clk_pfdv2 *pfd)
{
	u32 val;

	return readl_poll_timeout(pfd->reg, val, val & (1 << pfd->vld_bit),
				  0, LOCK_TIMEOUT_US);
}