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
struct event_overlapped {int /*<<< orphan*/  overlapped; } ;
struct evbuffer_overlapped {int read_in_progress; int n_buffers; int /*<<< orphan*/ * buffers; int /*<<< orphan*/  fd; struct evbuffer_chain* first_pinned; int /*<<< orphan*/  write_in_progress; } ;
struct evbuffer_iovec {int dummy; } ;
struct evbuffer_chain {struct evbuffer_chain* next; } ;
struct evbuffer {scalar_t__ freeze_end; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  EVBUFFER_LOCK (struct evbuffer*) ; 
 int /*<<< orphan*/  EVBUFFER_MEM_PINNED_R ; 
 int /*<<< orphan*/  EVBUFFER_UNLOCK (struct evbuffer*) ; 
 int /*<<< orphan*/  EVUTIL_ASSERT (int) ; 
 int MAX_WSABUFS ; 
 int /*<<< orphan*/  WSABUF_FROM_EVBUFFER_IOV (int /*<<< orphan*/ *,struct evbuffer_iovec*) ; 
 int WSAGetLastError () ; 
 scalar_t__ WSARecv (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int WSA_IO_PENDING ; 
 int /*<<< orphan*/  evbuffer_chain_pin_ (struct evbuffer_chain*,int /*<<< orphan*/ ) ; 
 int evbuffer_expand_fast_ (struct evbuffer*,size_t,int) ; 
 int /*<<< orphan*/  evbuffer_free (struct evbuffer*) ; 
 int /*<<< orphan*/  evbuffer_freeze (struct evbuffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evbuffer_incref_ (struct evbuffer*) ; 
 int evbuffer_read_setup_vecs_ (struct evbuffer*,size_t,struct evbuffer_iovec*,int,struct evbuffer_chain***,int) ; 
 int /*<<< orphan*/  evbuffer_unfreeze (struct evbuffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pin_release (struct evbuffer_overlapped*,int /*<<< orphan*/ ) ; 
 struct evbuffer_overlapped* upcast_evbuffer (struct evbuffer*) ; 

int
evbuffer_launch_read_(struct evbuffer *buf, size_t at_most,
		struct event_overlapped *ol)
{
	struct evbuffer_overlapped *buf_o = upcast_evbuffer(buf);
	int r = -1, i;
	int nvecs;
	int npin=0;
	struct evbuffer_chain *chain=NULL, **chainp;
	DWORD bytesRead;
	DWORD flags = 0;
	struct evbuffer_iovec vecs[MAX_WSABUFS];

	if (!buf_o)
		return -1;
	EVBUFFER_LOCK(buf);
	EVUTIL_ASSERT(!buf_o->write_in_progress);
	if (buf->freeze_end || buf_o->read_in_progress)
		goto done;

	buf_o->first_pinned = NULL;
	buf_o->n_buffers = 0;
	memset(buf_o->buffers, 0, sizeof(buf_o->buffers));

	if (evbuffer_expand_fast_(buf, at_most, MAX_WSABUFS) == -1)
		goto done;
	evbuffer_freeze(buf, 0);

	nvecs = evbuffer_read_setup_vecs_(buf, at_most,
	    vecs, MAX_WSABUFS, &chainp, 1);
	for (i=0;i<nvecs;++i) {
		WSABUF_FROM_EVBUFFER_IOV(
			&buf_o->buffers[i],
			&vecs[i]);
	}

	buf_o->n_buffers = nvecs;
	buf_o->first_pinned = chain = *chainp;

	npin=0;
	for ( ; chain; chain = chain->next) {
		evbuffer_chain_pin_(chain, EVBUFFER_MEM_PINNED_R);
		++npin;
	}
	EVUTIL_ASSERT(npin == nvecs);

	evbuffer_incref_(buf);
	if (WSARecv(buf_o->fd, buf_o->buffers, nvecs, &bytesRead, &flags,
		    &ol->overlapped, NULL)) {
		int error = WSAGetLastError();
		if (error != WSA_IO_PENDING) {
			/* An actual error. */
			pin_release(buf_o, EVBUFFER_MEM_PINNED_R);
			evbuffer_unfreeze(buf, 0);
			evbuffer_free(buf); /* decref */
			goto done;
		}
	}

	buf_o->read_in_progress = 1;
	r = 0;
done:
	EVBUFFER_UNLOCK(buf);
	return r;
}