#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct timeval {int dummy; } ;
struct comm_timer {TYPE_3__* ev_timer; } ;
struct TYPE_6__ {int enabled; TYPE_2__* base; int /*<<< orphan*/  ev; } ;
struct TYPE_5__ {TYPE_1__* eb; } ;
struct TYPE_4__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  comm_timer_callback ; 
 int /*<<< orphan*/  comm_timer_disable (struct comm_timer*) ; 
 int /*<<< orphan*/  log_assert (struct timeval*) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 scalar_t__ ub_timer_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct comm_timer*,struct timeval*) ; 

void 
comm_timer_set(struct comm_timer* timer, struct timeval* tv)
{
	log_assert(tv);
	if(timer->ev_timer->enabled)
		comm_timer_disable(timer);
	if(ub_timer_add(timer->ev_timer->ev, timer->ev_timer->base->eb->base,
		comm_timer_callback, timer, tv) != 0)
		log_err("comm_timer_set: evtimer_add failed.");
	timer->ev_timer->enabled = 1;
}