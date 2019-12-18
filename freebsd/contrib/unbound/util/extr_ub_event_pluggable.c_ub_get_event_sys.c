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
struct ev_loop {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct event_base*) ; 
 int /*<<< orphan*/  ev_backend (struct ev_loop*) ; 
 char* event_base_get_method (struct event_base*) ; 
 char* event_get_version () ; 
 char* ub_ev_backend2str_pluggable (int /*<<< orphan*/ ) ; 
 struct event_base* ub_libevent_get_event_base (struct ub_event_base*) ; 

void
ub_get_event_sys(struct ub_event_base* ub_base, const char** n, const char** s,
	const char** m)
{
#ifdef USE_WINSOCK
	(void)ub_base;
	*n = "pluggable-event";
	*s = "winsock";
	*m = "WSAWaitForMultipleEvents";
#elif defined(USE_MINI_EVENT)
	(void)ub_base;
	*n = "pluggable-event";
	*s = "internal";
	*m = "select";
#else
	struct event_base* b = ub_libevent_get_event_base(ub_base);
	/* This function is only called from comm_base_create, so
	 * ub_base is guaranteed to exist and to be the default
	 * event base.
	 */
	assert(b);
	*n = "pluggable-event";
	*s = event_get_version();
#  if defined(HAVE_EV_LOOP) || defined(HAVE_EV_DEFAULT_LOOP)
	*n = "pluggable-libev";
#    ifdef EVBACKEND_SELECT
	*m = ub_ev_backend2str_pluggable(ev_backend((struct ev_loop*)b));
#    else
	*m = "not obtainable";
#    endif
#  elif defined(HAVE_EVENT_BASE_GET_METHOD)
	*n = "pluggable-libevent";
	*m = event_base_get_method(b);
#  else
	*m = "not obtainable";
#  endif
#endif
}