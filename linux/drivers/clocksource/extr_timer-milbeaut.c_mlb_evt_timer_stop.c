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
struct timer_of {int dummy; } ;

/* Variables and functions */
 scalar_t__ MLB_TMR_EVT_TMCSR_OFS ; 
 int /*<<< orphan*/  MLB_TMR_TMCSR_CNTE ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 scalar_t__ timer_of_base (struct timer_of*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mlb_evt_timer_stop(struct timer_of *to)
{
	u32 val = readl_relaxed(timer_of_base(to) + MLB_TMR_EVT_TMCSR_OFS);

	val &= ~MLB_TMR_TMCSR_CNTE;
	writel_relaxed(val, timer_of_base(to) + MLB_TMR_EVT_TMCSR_OFS);
}