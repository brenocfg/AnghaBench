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
 scalar_t__ MLB_TMR_SRC_TMCSR_OFS ; 
 scalar_t__ MLB_TMR_SRC_TMRLR1_OFS ; 
 scalar_t__ MLB_TMR_SRC_TMRLR2_OFS ; 
 int MLB_TMR_TMCSR_CNTE ; 
 int MLB_TMR_TMCSR_CSL_DIV2 ; 
 int MLB_TMR_TMCSR_RELD ; 
 int MLB_TMR_TMCSR_TRG ; 
 scalar_t__ timer_of_base (struct timer_of*) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int mlb_config_clock_source(struct timer_of *to)
{
	u32 val = MLB_TMR_TMCSR_CSL_DIV2;

	writel_relaxed(val, timer_of_base(to) + MLB_TMR_SRC_TMCSR_OFS);
	writel_relaxed(~0, timer_of_base(to) + MLB_TMR_SRC_TMRLR1_OFS);
	writel_relaxed(~0, timer_of_base(to) + MLB_TMR_SRC_TMRLR2_OFS);
	val |= MLB_TMR_TMCSR_RELD | MLB_TMR_TMCSR_CNTE | MLB_TMR_TMCSR_TRG;
	writel_relaxed(val, timer_of_base(to) + MLB_TMR_SRC_TMCSR_OFS);
	return 0;
}