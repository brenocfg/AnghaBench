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
struct wait_timer {int /*<<< orphan*/  f; } ;
struct timer_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_fence_signal (int /*<<< orphan*/ ) ; 
 struct wait_timer* from_timer (int /*<<< orphan*/ ,struct timer_list*,struct timer_list*) ; 
 struct wait_timer* wt ; 

__attribute__((used)) static void wait_timer(struct timer_list *timer)
{
	struct wait_timer *wt = from_timer(wt, timer, timer);

	dma_fence_signal(wt->f);
}