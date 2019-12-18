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
typedef  int u64 ;
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  PRD12 ; 
 int /*<<< orphan*/  PRD34 ; 
 int /*<<< orphan*/  TCR ; 
 int TCR_ENAMODE_MASK ; 
 int /*<<< orphan*/  TIM12 ; 
 int /*<<< orphan*/  TIM34 ; 
 int /*<<< orphan*/  keystone_timer_barrier () ; 
 int keystone_timer_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  keystone_timer_writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int keystone_timer_config(u64 period, int mask)
{
	u32 tcr;
	u32 off;

	tcr = keystone_timer_readl(TCR);
	off = tcr & ~(TCR_ENAMODE_MASK);

	/* set enable mode */
	tcr |= mask;

	/* disable timer */
	keystone_timer_writel(off, TCR);
	/* here we have to be sure the timer has been disabled */
	keystone_timer_barrier();

	/* reset counter to zero, set new period */
	keystone_timer_writel(0, TIM12);
	keystone_timer_writel(0, TIM34);
	keystone_timer_writel(period & 0xffffffff, PRD12);
	keystone_timer_writel(period >> 32, PRD34);

	/*
	 * enable timer
	 * here we have to be sure that CNTLO, CNTHI, PRDLO, PRDHI registers
	 * have been written.
	 */
	keystone_timer_barrier();
	keystone_timer_writel(tcr, TCR);
	return 0;
}