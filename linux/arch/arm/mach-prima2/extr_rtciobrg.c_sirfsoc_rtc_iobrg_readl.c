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
typedef  unsigned long u32 ;

/* Variables and functions */
 unsigned long __sirfsoc_rtc_iobrg_readl (unsigned long) ; 
 int /*<<< orphan*/  rtciobrg_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

u32 sirfsoc_rtc_iobrg_readl(u32 addr)
{
	unsigned long flags, val;

	/* TODO: add hwspinlock to sync with M3 */
	spin_lock_irqsave(&rtciobrg_lock, flags);

	val = __sirfsoc_rtc_iobrg_readl(addr);

	spin_unlock_irqrestore(&rtciobrg_lock, flags);

	return val;
}