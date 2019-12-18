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
struct ub_event_base {int /*<<< orphan*/ * vmt; } ;
struct event_base {int dummy; } ;
struct TYPE_2__ {struct event_base* base; } ;

/* Variables and functions */
 TYPE_1__* AS_MY_EVENT_BASE (struct ub_event_base*) ; 
 int /*<<< orphan*/  default_event_base_vmt ; 

struct event_base*
ub_libevent_get_event_base(struct ub_event_base* base)
{
#ifndef USE_MINI_EVENT
	if (base->vmt == &default_event_base_vmt)
		return AS_MY_EVENT_BASE(base)->base;
#else
	(void)base;
#endif
	return NULL;
}