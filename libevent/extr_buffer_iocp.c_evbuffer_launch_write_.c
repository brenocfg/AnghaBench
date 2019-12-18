#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct event_overlapped {int /*<<< orphan*/  overlapped; } ;
struct evbuffer_overlapped {int write_in_progress; int n_buffers; TYPE_1__* buffers; int /*<<< orphan*/  fd; struct evbuffer_chain* first_pinned; int /*<<< orphan*/  read_in_progress; } ;
struct evbuffer_chain {size_t off; scalar_t__ misalign; scalar_t__ buffer; struct evbuffer_chain* next; } ;
struct evbuffer {size_t total_len; struct evbuffer_chain* first; scalar_t__ freeze_start; } ;
typedef  size_t ev_ssize_t ;
struct TYPE_4__ {char* buf; unsigned long len; } ;
typedef  TYPE_1__ WSABUF ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  EVBUFFER_LOCK (struct evbuffer*) ; 
 int /*<<< orphan*/  EVBUFFER_MEM_PINNED_W ; 
 int /*<<< orphan*/  EVBUFFER_UNLOCK (struct evbuffer*) ; 
 int /*<<< orphan*/  EVUTIL_ASSERT (int) ; 
 int MAX_WSABUFS ; 
 int WSAGetLastError () ; 
 scalar_t__ WSASend (int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int WSA_IO_PENDING ; 
 int /*<<< orphan*/  evbuffer_chain_pin_ (struct evbuffer_chain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evbuffer_free (struct evbuffer*) ; 
 int /*<<< orphan*/  evbuffer_freeze (struct evbuffer*,int) ; 
 int /*<<< orphan*/  evbuffer_incref_ (struct evbuffer*) ; 
 int /*<<< orphan*/  evbuffer_unfreeze (struct evbuffer*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pin_release (struct evbuffer_overlapped*,int /*<<< orphan*/ ) ; 
 struct evbuffer_overlapped* upcast_evbuffer (struct evbuffer*) ; 

int
evbuffer_launch_write_(struct evbuffer *buf, ev_ssize_t at_most,
		struct event_overlapped *ol)
{
	struct evbuffer_overlapped *buf_o = upcast_evbuffer(buf);
	int r = -1;
	int i;
	struct evbuffer_chain *chain;
	DWORD bytesSent;

	if (!buf) {
		/* No buffer, or it isn't overlapped */
		return -1;
	}

	EVBUFFER_LOCK(buf);
	EVUTIL_ASSERT(!buf_o->read_in_progress);
	if (buf->freeze_start || buf_o->write_in_progress)
		goto done;
	if (!buf->total_len) {
		/* Nothing to write */
		r = 0;
		goto done;
	} else if (at_most < 0 || (size_t)at_most > buf->total_len) {
		at_most = buf->total_len;
	}
	evbuffer_freeze(buf, 1);

	buf_o->first_pinned = NULL;
	buf_o->n_buffers = 0;
	memset(buf_o->buffers, 0, sizeof(buf_o->buffers));

	chain = buf_o->first_pinned = buf->first;

	for (i=0; i < MAX_WSABUFS && chain; ++i, chain=chain->next) {
		WSABUF *b = &buf_o->buffers[i];
		b->buf = (char*)( chain->buffer + chain->misalign );
		evbuffer_chain_pin_(chain, EVBUFFER_MEM_PINNED_W);

		if ((size_t)at_most > chain->off) {
			/* XXXX Cast is safe for now, since win32 has no
			   mmaped chains.  But later, we need to have this
			   add more WSAbufs if chain->off is greater than
			   ULONG_MAX */
			b->len = (unsigned long)chain->off;
			at_most -= chain->off;
		} else {
			b->len = (unsigned long)at_most;
			++i;
			break;
		}
	}

	buf_o->n_buffers = i;
	evbuffer_incref_(buf);
	if (WSASend(buf_o->fd, buf_o->buffers, i, &bytesSent, 0,
		&ol->overlapped, NULL)) {
		int error = WSAGetLastError();
		if (error != WSA_IO_PENDING) {
			/* An actual error. */
			pin_release(buf_o, EVBUFFER_MEM_PINNED_W);
			evbuffer_unfreeze(buf, 1);
			evbuffer_free(buf); /* decref */
			goto done;
		}
	}

	buf_o->write_in_progress = 1;
	r = 0;
done:
	EVBUFFER_UNLOCK(buf);
	return r;
}