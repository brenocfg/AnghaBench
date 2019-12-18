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
struct comm_timer {TYPE_1__* ev_timer; } ;
struct TYPE_2__ {scalar_t__ enabled; } ;

/* Variables and functions */

int 
comm_timer_is_set(struct comm_timer* timer)
{
	return (int)timer->ev_timer->enabled;
}