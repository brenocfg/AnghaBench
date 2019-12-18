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
 int /*<<< orphan*/  NATIVE_BITS_CB (void (*) (int,short,void*)) ; 
 scalar_t__ calloc (int,int) ; 
 scalar_t__ event_base_set (int /*<<< orphan*/ ,struct event*) ; 
 scalar_t__ evsignal_assign (struct event*,int /*<<< orphan*/ ,int,void (*) (int,short,void*),void*) ; 
 int /*<<< orphan*/  free (struct event*) ; 
 int /*<<< orphan*/  signal_set (struct event*,int,int /*<<< orphan*/ ,void*) ; 

struct ub_event*
ub_signal_new(struct ub_event_base* base, int fd,
	void (*cb)(int, short, void*), void* arg)
{
	struct event *ev = (struct event*)calloc(1, sizeof(struct event));

	if (!ev)
		return NULL;

#if !HAVE_DECL_EVSIGNAL_ASSIGN
	signal_set(ev, fd, NATIVE_BITS_CB(cb), arg);
	if (event_base_set(AS_EVENT_BASE(base), ev) != 0) {
		free(ev);
		return NULL;
	}
#else
	if (evsignal_assign(ev, AS_EVENT_BASE(base), fd, cb, arg) != 0) {
		free(ev);
		return NULL;
	}
#endif
	return AS_UB_EVENT(ev);
}