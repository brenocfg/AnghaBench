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
struct e1000_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_CTRL ; 
 int E1000_CTRL_MDC ; 
 int /*<<< orphan*/  E1000_WRITE_FLUSH (struct e1000_hw*) ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usec_delay (int) ; 

__attribute__((used)) static void e1000_lower_mdi_clk_82543(struct e1000_hw *hw, u32 *ctrl)
{
	/*
	 * Lower the clock input to the Management Data Clock (by clearing the
	 * MDC bit), and then delay a sufficient amount of time.
	 */
	E1000_WRITE_REG(hw, E1000_CTRL, (*ctrl & ~E1000_CTRL_MDC));
	E1000_WRITE_FLUSH(hw);
	usec_delay(10);
}