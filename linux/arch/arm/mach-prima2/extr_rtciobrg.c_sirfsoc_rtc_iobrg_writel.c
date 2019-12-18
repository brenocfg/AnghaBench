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
 scalar_t__ SIRFSOC_CPUIOBRG_CTRL ; 
 int /*<<< orphan*/  rtciobrg_lock ; 
 int /*<<< orphan*/  sirfsoc_rtc_iobrg_pre_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sirfsoc_rtc_iobrg_wait_sync () ; 
 scalar_t__ sirfsoc_rtciobrg_base ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

void sirfsoc_rtc_iobrg_writel(u32 val, u32 addr)
{
	unsigned long flags;

	 /* TODO: add hwspinlock to sync with M3 */
	spin_lock_irqsave(&rtciobrg_lock, flags);

	sirfsoc_rtc_iobrg_pre_writel(val, addr);

	writel_relaxed(0x01, sirfsoc_rtciobrg_base + SIRFSOC_CPUIOBRG_CTRL);

	sirfsoc_rtc_iobrg_wait_sync();

	spin_unlock_irqrestore(&rtciobrg_lock, flags);
}