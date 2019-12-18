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
struct rk_timer {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ TIMER_LOAD_COUNT0 ; 
 scalar_t__ TIMER_LOAD_COUNT1 ; 
 int /*<<< orphan*/  writel_relaxed (unsigned long,scalar_t__) ; 

__attribute__((used)) static void rk_timer_update_counter(unsigned long cycles,
				    struct rk_timer *timer)
{
	writel_relaxed(cycles, timer->base + TIMER_LOAD_COUNT0);
	writel_relaxed(0, timer->base + TIMER_LOAD_COUNT1);
}