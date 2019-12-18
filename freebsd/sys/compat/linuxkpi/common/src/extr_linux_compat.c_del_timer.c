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
struct timer_list {int /*<<< orphan*/  callout; } ;

/* Variables and functions */
 int callout_stop (int /*<<< orphan*/ *) ; 

int
del_timer(struct timer_list *timer)
{

	if (callout_stop(&(timer)->callout) == -1)
		return (0);
	return (1);
}