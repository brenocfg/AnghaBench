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
 scalar_t__ TIMER_INT_STATUS ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void rk_timer_interrupt_clear(struct rk_timer *timer)
{
	writel_relaxed(1, timer->base + TIMER_INT_STATUS);
}