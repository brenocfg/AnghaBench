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
struct ub_event_base {int dummy; } ;
struct ub_event {int dummy; } ;
struct timeval {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AS_EVENT (struct ub_event*) ; 
 int /*<<< orphan*/  AS_EVENT_BASE (struct ub_event_base*) ; 
 int /*<<< orphan*/  EV_TIMEOUT ; 
 int /*<<< orphan*/  NATIVE_BITS_CB (void (*) (int,short,void*)) ; 
 scalar_t__ event_base_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_set (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int evtimer_add (int /*<<< orphan*/ ,struct timeval*) ; 

int
ub_timer_add(struct ub_event* ev, struct ub_event_base* base,
	void (*cb)(int, short, void*), void* arg, struct timeval* tv)
{
	event_set(AS_EVENT(ev), -1, EV_TIMEOUT, NATIVE_BITS_CB(cb), arg);
	if (event_base_set(AS_EVENT_BASE(base), AS_EVENT(ev)) != 0)
		return -1;
	return evtimer_add(AS_EVENT(ev), tv);
}