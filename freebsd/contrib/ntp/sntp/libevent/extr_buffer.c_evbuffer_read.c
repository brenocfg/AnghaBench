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
struct evbuffer_iovec {int dummy; } ;
struct evbuffer_chain {unsigned char* buffer; int misalign; int off; struct evbuffer_chain* next; } ;
struct evbuffer {int total_len; int n_add_for_cb; struct evbuffer_chain** last_with_datap; scalar_t__ freeze_end; } ;
typedef  int /*<<< orphan*/  evutil_socket_t ;
typedef  int ev_ssize_t ;
typedef  struct evbuffer_iovec IOV_TYPE ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CHAIN_SPACE_LEN (struct evbuffer_chain*) ; 
 size_t EVBUFFER_CHAIN_MAX ; 
 int /*<<< orphan*/  EVBUFFER_LOCK (struct evbuffer*) ; 
 int EVBUFFER_MAX_READ ; 
 int /*<<< orphan*/  EVBUFFER_UNLOCK (struct evbuffer*) ; 
 int NUM_READ_IOVEC ; 
 int /*<<< orphan*/  WSABUF_FROM_EVBUFFER_IOV (struct evbuffer_iovec*,struct evbuffer_iovec*) ; 
 scalar_t__ WSAECONNABORTED ; 
 scalar_t__ WSAGetLastError () ; 
 scalar_t__ WSARecv (int /*<<< orphan*/ ,struct evbuffer_iovec*,int,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  advance_last_with_data (struct evbuffer*) ; 
 int evbuffer_expand_fast_ (struct evbuffer*,int,int) ; 
 struct evbuffer_chain* evbuffer_expand_singlechain (struct evbuffer*,int) ; 
 int /*<<< orphan*/  evbuffer_invoke_callbacks_ (struct evbuffer*) ; 
 int evbuffer_read_setup_vecs_ (struct evbuffer*,int,struct evbuffer_iovec*,int,struct evbuffer_chain***,int) ; 
 int get_n_bytes_readable_on_socket (int /*<<< orphan*/ ) ; 
 int read (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int readv (int /*<<< orphan*/ ,struct evbuffer_iovec*,int) ; 
 int recv (int /*<<< orphan*/ ,unsigned char*,int,int /*<<< orphan*/ ) ; 

int
evbuffer_read(struct evbuffer *buf, evutil_socket_t fd, int howmuch)
{
	struct evbuffer_chain **chainp;
	int n;
	int result;

#ifdef USE_IOVEC_IMPL
	int nvecs, i, remaining;
#else
	struct evbuffer_chain *chain;
	unsigned char *p;
#endif

	EVBUFFER_LOCK(buf);

	if (buf->freeze_end) {
		result = -1;
		goto done;
	}

	n = get_n_bytes_readable_on_socket(fd);
	if (n <= 0 || n > EVBUFFER_MAX_READ)
		n = EVBUFFER_MAX_READ;
	if (howmuch < 0 || howmuch > n)
		howmuch = n;

#ifdef USE_IOVEC_IMPL
	/* Since we can use iovecs, we're willing to use the last
	 * NUM_READ_IOVEC chains. */
	if (evbuffer_expand_fast_(buf, howmuch, NUM_READ_IOVEC) == -1) {
		result = -1;
		goto done;
	} else {
		IOV_TYPE vecs[NUM_READ_IOVEC];
#ifdef EVBUFFER_IOVEC_IS_NATIVE_
		nvecs = evbuffer_read_setup_vecs_(buf, howmuch, vecs,
		    NUM_READ_IOVEC, &chainp, 1);
#else
		/* We aren't using the native struct iovec.  Therefore,
		   we are on win32. */
		struct evbuffer_iovec ev_vecs[NUM_READ_IOVEC];
		nvecs = evbuffer_read_setup_vecs_(buf, howmuch, ev_vecs, 2,
		    &chainp, 1);

		for (i=0; i < nvecs; ++i)
			WSABUF_FROM_EVBUFFER_IOV(&vecs[i], &ev_vecs[i]);
#endif

#ifdef _WIN32
		{
			DWORD bytesRead;
			DWORD flags=0;
			if (WSARecv(fd, vecs, nvecs, &bytesRead, &flags, NULL, NULL)) {
				/* The read failed. It might be a close,
				 * or it might be an error. */
				if (WSAGetLastError() == WSAECONNABORTED)
					n = 0;
				else
					n = -1;
			} else
				n = bytesRead;
		}
#else
		n = readv(fd, vecs, nvecs);
#endif
	}

#else /*!USE_IOVEC_IMPL*/
	/* If we don't have FIONREAD, we might waste some space here */
	/* XXX we _will_ waste some space here if there is any space left
	 * over on buf->last. */
	if ((chain = evbuffer_expand_singlechain(buf, howmuch)) == NULL) {
		result = -1;
		goto done;
	}

	/* We can append new data at this point */
	p = chain->buffer + chain->misalign + chain->off;

#ifndef _WIN32
	n = read(fd, p, howmuch);
#else
	n = recv(fd, p, howmuch, 0);
#endif
#endif /* USE_IOVEC_IMPL */

	if (n == -1) {
		result = -1;
		goto done;
	}
	if (n == 0) {
		result = 0;
		goto done;
	}

#ifdef USE_IOVEC_IMPL
	remaining = n;
	for (i=0; i < nvecs; ++i) {
		/* can't overflow, since only mutable chains have
		 * huge misaligns. */
		size_t space = (size_t) CHAIN_SPACE_LEN(*chainp);
		/* XXXX This is a kludge that can waste space in perverse
		 * situations. */
		if (space > EVBUFFER_CHAIN_MAX)
			space = EVBUFFER_CHAIN_MAX;
		if ((ev_ssize_t)space < remaining) {
			(*chainp)->off += space;
			remaining -= (int)space;
		} else {
			(*chainp)->off += remaining;
			buf->last_with_datap = chainp;
			break;
		}
		chainp = &(*chainp)->next;
	}
#else
	chain->off += n;
	advance_last_with_data(buf);
#endif
	buf->total_len += n;
	buf->n_add_for_cb += n;

	/* Tell someone about changes in this buffer */
	evbuffer_invoke_callbacks_(buf);
	result = n;
done:
	EVBUFFER_UNLOCK(buf);
	return result;
}