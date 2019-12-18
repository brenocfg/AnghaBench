#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ub_event_base {int dummy; } ;
struct ub_event {int dummy; } ;
struct timeval {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  ev; } ;
struct TYPE_3__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 TYPE_2__* AS_MY_EVENT (struct ub_event*) ; 
 TYPE_1__* AS_MY_EVENT_BASE (struct ub_event_base*) ; 
 int /*<<< orphan*/  EV_TIMEOUT ; 
 int /*<<< orphan*/  NATIVE_BITS_CB (void (*) (int,short,void*)) ; 
 scalar_t__ event_base_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_set (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int evtimer_add (int /*<<< orphan*/ *,struct timeval*) ; 

__attribute__((used)) static int
my_timer_add(struct ub_event* ev, struct ub_event_base* base,
	void (*cb)(int, short, void*), void* arg, struct timeval* tv)
{
	event_set(&AS_MY_EVENT(ev)->ev, -1, EV_TIMEOUT,NATIVE_BITS_CB(cb),arg);
	if (event_base_set(AS_MY_EVENT_BASE(base)->base, &AS_MY_EVENT(ev)->ev)
		!= 0)
		return -1;
	return evtimer_add(&AS_MY_EVENT(ev)->ev, tv);
}