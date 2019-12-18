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
struct timer_of {int dummy; } ;

/* Variables and functions */
 scalar_t__ MLB_TMR_EVT_TMCSR_OFS ; 
 scalar_t__ timer_of_base (struct timer_of*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int mlb_config_clock_event(struct timer_of *to)
{
	writel_relaxed(0, timer_of_base(to) + MLB_TMR_EVT_TMCSR_OFS);
	return 0;
}