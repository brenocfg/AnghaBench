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
 struct event_base* AS_EVENT_BASE (struct ub_event_base*) ; 
 int /*<<< orphan*/  EVFLAG_AUTO ; 
 int /*<<< orphan*/  ev_backend (struct ev_loop*) ; 
 scalar_t__ ev_default_loop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_base_free (struct event_base*) ; 
 char* event_base_get_method (struct event_base*) ; 
 struct event_base* event_base_new () ; 
 char* event_get_version () ; 
 char* ub_ev_backend2str (int /*<<< orphan*/ ) ; 

void
ub_get_event_sys(struct ub_event_base* base, const char** n, const char** s,
	const char** m)
{
#ifdef USE_WINSOCK
	(void)base;
	*n = "event";
	*s = "winsock";
	*m = "WSAWaitForMultipleEvents";
#elif defined(USE_MINI_EVENT)
	(void)base;
	*n = "mini-event";
	*s = "internal";
	*m = "select";
#else
	struct event_base* b = AS_EVENT_BASE(base);
	*s = event_get_version();
#  if defined(HAVE_EV_LOOP) || defined(HAVE_EV_DEFAULT_LOOP)
	*n = "libev";
	if (!b)
		b = (struct event_base*)ev_default_loop(EVFLAG_AUTO);
#    ifdef EVBACKEND_SELECT
	*m = ub_ev_backend2str(ev_backend((struct ev_loop*)b));
#    else
	*m = "not obtainable";
#    endif
#  elif defined(HAVE_EVENT_BASE_GET_METHOD)
	*n = "libevent";
	if (!b)
		b = event_base_new();
	*m = event_base_get_method(b);
#  else
	*n = "unknown";
	*m = "not obtainable";
	(void)b;
#  endif
#  ifdef HAVE_EVENT_BASE_FREE
	if (b && b != AS_EVENT_BASE(base))
		event_base_free(b);
#  endif
#endif
}