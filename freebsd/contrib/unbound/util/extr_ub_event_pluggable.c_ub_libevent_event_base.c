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
struct ub_event_base {int /*<<< orphan*/ * vmt; int /*<<< orphan*/  magic; } ;
struct my_event_base {struct ub_event_base super; struct event_base* base; } ;
struct event_base {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UB_EVENT_MAGIC ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  default_event_base_vmt ; 

struct ub_event_base*
ub_libevent_event_base(struct event_base* base)
{
#ifdef USE_MINI_EVENT
	(void)base;
	return NULL;
#else
	struct my_event_base* my_base = (struct my_event_base*)calloc(1,
		sizeof(struct my_event_base));

	if (!my_base)
		return NULL;
	my_base->super.magic = UB_EVENT_MAGIC;
	my_base->super.vmt = &default_event_base_vmt;
	my_base->base = base;
	return &my_base->super;
#endif
}