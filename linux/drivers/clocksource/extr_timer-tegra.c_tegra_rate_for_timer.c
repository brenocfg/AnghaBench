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
 unsigned long TIMER_1MHz ; 
 unsigned long timer_of_rate (struct timer_of*) ; 

__attribute__((used)) static inline unsigned long tegra_rate_for_timer(struct timer_of *to,
						 bool tegra20)
{
	/*
	 * TIMER1-9 are fixed to 1MHz, TIMER10-13 are running off the
	 * parent clock.
	 */
	if (tegra20)
		return TIMER_1MHz;

	return timer_of_rate(to);
}