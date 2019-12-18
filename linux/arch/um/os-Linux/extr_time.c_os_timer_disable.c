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
struct itimerspec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  event_high_res_timer ; 
 int /*<<< orphan*/  memset (struct itimerspec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  timer_settime (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct itimerspec*,int /*<<< orphan*/ *) ; 

void os_timer_disable(void)
{
	struct itimerspec its;

	memset(&its, 0, sizeof(struct itimerspec));
	timer_settime(event_high_res_timer, 0, &its, NULL);
}