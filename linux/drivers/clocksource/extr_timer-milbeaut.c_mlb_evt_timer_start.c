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
typedef  int u32 ;
struct timer_of {int dummy; } ;

/* Variables and functions */
 scalar_t__ MLB_TMR_EVT_TMCSR_OFS ; 
 int MLB_TMR_TMCSR_CNTE ; 
 int MLB_TMR_TMCSR_CSL_DIV2 ; 
 int MLB_TMR_TMCSR_INTE ; 
 int MLB_TMR_TMCSR_RELD ; 
 int MLB_TMR_TMCSR_TRG ; 
 scalar_t__ timer_of_base (struct timer_of*) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void mlb_evt_timer_start(struct timer_of *to, bool periodic)
{
	u32 val = MLB_TMR_TMCSR_CSL_DIV2;

	val |= MLB_TMR_TMCSR_CNTE | MLB_TMR_TMCSR_TRG | MLB_TMR_TMCSR_INTE;
	if (periodic)
		val |= MLB_TMR_TMCSR_RELD;
	writel_relaxed(val, timer_of_base(to) + MLB_TMR_EVT_TMCSR_OFS);
}