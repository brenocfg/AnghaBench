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
struct evbuffer_overlapped {int /*<<< orphan*/  fd; } ;
struct evbuffer {int dummy; } ;
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVBUFFER_LOCK (struct evbuffer*) ; 
 int /*<<< orphan*/  EVBUFFER_UNLOCK (struct evbuffer*) ; 
 struct evbuffer_overlapped* upcast_evbuffer (struct evbuffer*) ; 

void
evbuffer_overlapped_set_fd_(struct evbuffer *buf, evutil_socket_t fd)
{
	struct evbuffer_overlapped *buf_o = upcast_evbuffer(buf);
	EVBUFFER_LOCK(buf);
	/* XXX is this right?, should it cancel current I/O operations? */
	if (buf_o)
		buf_o->fd = fd;
	EVBUFFER_UNLOCK(buf);
}