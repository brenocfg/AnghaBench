#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ub_event_base {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 TYPE_1__* AS_MY_EVENT_BASE (struct ub_event_base*) ; 
 int /*<<< orphan*/  event_base_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void
my_event_base_free(struct ub_event_base* base)
{
#ifdef USE_MINI_EVENT
	event_base_free(AS_MY_EVENT_BASE(base)->base);
#elif defined(HAVE_EVENT_BASE_FREE) && defined(HAVE_EVENT_BASE_ONCE)
	/* only libevent 1.2+ has it, but in 1.2 it is broken - 
	   assertion fails on signal handling ev that is not deleted
 	   in libevent 1.3c (event_base_once appears) this is fixed. */
	event_base_free(AS_MY_EVENT_BASE(base)->base);
#endif /* HAVE_EVENT_BASE_FREE and HAVE_EVENT_BASE_ONCE */
	free(AS_MY_EVENT_BASE(base));
}