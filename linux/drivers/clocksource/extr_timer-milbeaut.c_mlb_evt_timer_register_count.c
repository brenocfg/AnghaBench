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
 scalar_t__ MLB_TMR_EVT_TMRLR1_OFS ; 
 scalar_t__ timer_of_base (struct timer_of*) ; 
 int /*<<< orphan*/  writel_relaxed (unsigned long,scalar_t__) ; 

__attribute__((used)) static void mlb_evt_timer_register_count(struct timer_of *to, unsigned long cnt)
{
	writel_relaxed(cnt, timer_of_base(to) + MLB_TMR_EVT_TMRLR1_OFS);
}