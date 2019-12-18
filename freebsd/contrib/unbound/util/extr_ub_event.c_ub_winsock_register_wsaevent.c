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
struct event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AS_EVENT_BASE (struct ub_event_base*) ; 
 struct ub_event* AS_UB_EVENT (struct event*) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  free (struct event*) ; 
 scalar_t__ winsock_register_wsaevent (int /*<<< orphan*/ ,struct event*,void*,void (*) (int,short,void*),void*) ; 

struct ub_event*
ub_winsock_register_wsaevent(struct ub_event_base* base, void* wsaevent,
	void (*cb)(int, short, void*), void* arg)
{
#if defined(USE_MINI_EVENT) && defined(USE_WINSOCK)
	struct event *ev = (struct event*)calloc(1, sizeof(struct event));

	if (!ev)
		return NULL;

	if (winsock_register_wsaevent(AS_EVENT_BASE(base), ev, wsaevent, cb,
				arg))
		return AS_UB_EVENT(ev);
	free(ev);
	return NULL;
#else
	(void)base;
	(void)wsaevent;
	(void)cb;
	(void)arg;
	return NULL;
#endif
}