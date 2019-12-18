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

/* Variables and functions */
 int /*<<< orphan*/  TCR ; 
 int /*<<< orphan*/  TCR_ENAMODE_MASK ; 
 int /*<<< orphan*/  keystone_timer_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  keystone_timer_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void keystone_timer_disable(void)
{
	u32 tcr;

	tcr = keystone_timer_readl(TCR);

	/* disable timer */
	tcr &= ~(TCR_ENAMODE_MASK);
	keystone_timer_writel(tcr, TCR);
}