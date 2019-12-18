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
struct mct_clock_event_device {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ MCT_L_INT_CSTAT_OFFSET ; 
 int /*<<< orphan*/  exynos4_mct_write (int,scalar_t__) ; 
 int readl_relaxed (scalar_t__) ; 
 scalar_t__ reg_base ; 

__attribute__((used)) static void exynos4_mct_tick_clear(struct mct_clock_event_device *mevt)
{
	/* Clear the MCT tick interrupt */
	if (readl_relaxed(reg_base + mevt->base + MCT_L_INT_CSTAT_OFFSET) & 1)
		exynos4_mct_write(0x1, mevt->base + MCT_L_INT_CSTAT_OFFSET);
}