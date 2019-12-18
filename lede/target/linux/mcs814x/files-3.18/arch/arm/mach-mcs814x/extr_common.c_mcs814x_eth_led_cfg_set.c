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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  LED_CFG_MASK ; 
 scalar_t__ SYSDBG_BS2 ; 
 scalar_t__ mcs814x_sysdbg_base ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mcs814x_eth_led_cfg_set(u8 cfg)
{
	u32 reg;

	reg = readl_relaxed(mcs814x_sysdbg_base + SYSDBG_BS2);
	reg &= ~LED_CFG_MASK;
	reg |= cfg;
	writel_relaxed(reg, mcs814x_sysdbg_base + SYSDBG_BS2);
}