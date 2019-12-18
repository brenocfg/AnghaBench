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
struct evutil_addrinfo {int ai_flags; struct evutil_addrinfo* ai_canonname; struct evutil_addrinfo* ai_next; } ;

/* Variables and functions */
 int EVUTIL_AI_LIBEVENT_ALLOCATED ; 
 int /*<<< orphan*/  freeaddrinfo (struct evutil_addrinfo*) ; 
 int /*<<< orphan*/  mm_free (struct evutil_addrinfo*) ; 

void
evutil_freeaddrinfo(struct evutil_addrinfo *ai)
{
#ifdef EVENT__HAVE_GETADDRINFO
	if (!(ai->ai_flags & EVUTIL_AI_LIBEVENT_ALLOCATED)) {
		freeaddrinfo(ai);
		return;
	}
#endif
	while (ai) {
		struct evutil_addrinfo *next = ai->ai_next;
		if (ai->ai_canonname)
			mm_free(ai->ai_canonname);
		mm_free(ai);
		ai = next;
	}
}