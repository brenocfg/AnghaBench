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
typedef  scalar_t__ u8 ;
typedef  int u32 ;

/* Variables and functions */
 scalar_t__ MCS814X_DBGLED ; 
 scalar_t__ MCS814X_VIRT_BASE ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void mcs814x_eth_hardware_filter_set(u8 value)
{
	u32 reg;

	reg = readl_relaxed(MCS814X_VIRT_BASE + MCS814X_DBGLED);
	if (value)
		reg |= 0x80;
	else
		reg &= ~0x80;
	writel_relaxed(reg, MCS814X_VIRT_BASE + MCS814X_DBGLED);
}