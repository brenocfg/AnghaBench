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
struct evbuffer_chain {int flags; } ;
struct evbuffer {size_t total_len; struct evbuffer_chain* first; scalar_t__ freeze_start; } ;
typedef  int /*<<< orphan*/  evutil_socket_t ;
typedef  size_t ev_ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVBUFFER_LOCK (struct evbuffer*) ; 
 int EVBUFFER_SENDFILE ; 
 int /*<<< orphan*/  EVBUFFER_UNLOCK (struct evbuffer*) ; 
 int /*<<< orphan*/  EVUTIL_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evbuffer_drain (struct evbuffer*,int) ; 
 void* evbuffer_pullup (struct evbuffer*,size_t) ; 
 int evbuffer_write_iovec (struct evbuffer*,int /*<<< orphan*/ ,size_t) ; 
 int evbuffer_write_sendfile (struct evbuffer*,int /*<<< orphan*/ ,size_t) ; 
 int send (int /*<<< orphan*/ ,void*,size_t,int /*<<< orphan*/ ) ; 
 int write (int /*<<< orphan*/ ,void*,size_t) ; 

int
evbuffer_write_atmost(struct evbuffer *buffer, evutil_socket_t fd,
    ev_ssize_t howmuch)
{
	int n = -1;

	EVBUFFER_LOCK(buffer);

	if (buffer->freeze_start) {
		goto done;
	}

	if (howmuch < 0 || (size_t)howmuch > buffer->total_len)
		howmuch = buffer->total_len;

	if (howmuch > 0) {
#ifdef USE_SENDFILE
		struct evbuffer_chain *chain = buffer->first;
		if (chain != NULL && (chain->flags & EVBUFFER_SENDFILE))
			n = evbuffer_write_sendfile(buffer, fd, howmuch);
		else {
#endif
#ifdef USE_IOVEC_IMPL
		n = evbuffer_write_iovec(buffer, fd, howmuch);
#elif defined(_WIN32)
		/* XXX(nickm) Don't disable this code until we know if
		 * the WSARecv code above works. */
		void *p = evbuffer_pullup(buffer, howmuch);
		EVUTIL_ASSERT(p || !howmuch);
		n = send(fd, p, howmuch, 0);
#else
		void *p = evbuffer_pullup(buffer, howmuch);
		EVUTIL_ASSERT(p || !howmuch);
		n = write(fd, p, howmuch);
#endif
#ifdef USE_SENDFILE
		}
#endif
	}

	if (n > 0)
		evbuffer_drain(buffer, n);

done:
	EVBUFFER_UNLOCK(buffer);
	return (n);
}