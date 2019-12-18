#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ function; } ;
struct wakeup_source {TYPE_1__ timer; } ;

/* Variables and functions */
 scalar_t__ pm_wakeup_timer_fn ; 

__attribute__((used)) static bool wakeup_source_not_registered(struct wakeup_source *ws)
{
	/*
	 * Use timer struct to check if the given source is initialized
	 * by wakeup_source_add.
	 */
	return ws->timer.function != pm_wakeup_timer_fn;
}