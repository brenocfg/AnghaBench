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
struct event_base {int dummy; } ;

/* Variables and functions */
 struct ub_event_base* AS_UB_EVENT_BASE (struct event_base*) ; 

struct ub_event_base *
ub_libevent_event_base(struct event_base* libevent_base)
{
#ifdef USE_MINI_EVENT
	(void)libevent_base;
	return NULL;
#else
	return AS_UB_EVENT_BASE(libevent_base);
#endif
}