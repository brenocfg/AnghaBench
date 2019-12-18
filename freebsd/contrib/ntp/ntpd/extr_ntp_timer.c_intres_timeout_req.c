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
typedef  scalar_t__ u_int ;

/* Variables and functions */
 scalar_t__ current_time ; 
 scalar_t__ droproot ; 
 scalar_t__ worker_idle_timer ; 

void
intres_timeout_req(
	u_int	seconds		/* 0 cancels */
	)
{
#if defined(HAVE_DROPROOT) && defined(NEED_EARLY_FORK)
	if (droproot) {
		worker_idle_timer = 0;
		return;
	}
#endif
	if (0 == seconds) {
		worker_idle_timer = 0;
		return;
	}
	worker_idle_timer = current_time + seconds;
}