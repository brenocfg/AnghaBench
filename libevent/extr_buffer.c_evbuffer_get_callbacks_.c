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
struct event_callback {int dummy; } ;
struct evbuffer {struct event_callback deferred; scalar_t__ deferred_cbs; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVBUFFER_LOCK (struct evbuffer*) ; 
 int /*<<< orphan*/  EVBUFFER_UNLOCK (struct evbuffer*) ; 

int
evbuffer_get_callbacks_(struct evbuffer *buffer, struct event_callback **cbs,
    int max_cbs)
{
	int r = 0;
	EVBUFFER_LOCK(buffer);
	if (buffer->deferred_cbs) {
		if (max_cbs < 1) {
			r = -1;
			goto done;
		}
		cbs[0] = &buffer->deferred;
		r = 1;
	}
done:
	EVBUFFER_UNLOCK(buffer);
	return r;
}