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
struct evbuffer_overlapped {scalar_t__ write_in_progress; int /*<<< orphan*/  read_in_progress; } ;
struct evbuffer {int dummy; } ;
typedef  int /*<<< orphan*/  ev_ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVBUFFER_LOCK (struct evbuffer*) ; 
 int /*<<< orphan*/  EVBUFFER_MEM_PINNED_W ; 
 int /*<<< orphan*/  EVUTIL_ASSERT (int) ; 
 int /*<<< orphan*/  evbuffer_decref_and_unlock_ (struct evbuffer*) ; 
 int /*<<< orphan*/  evbuffer_drain (struct evbuffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evbuffer_unfreeze (struct evbuffer*,int) ; 
 int /*<<< orphan*/  pin_release (struct evbuffer_overlapped*,int /*<<< orphan*/ ) ; 
 struct evbuffer_overlapped* upcast_evbuffer (struct evbuffer*) ; 

void
evbuffer_commit_write_(struct evbuffer *evbuf, ev_ssize_t nBytes)
{
	struct evbuffer_overlapped *buf = upcast_evbuffer(evbuf);

	EVBUFFER_LOCK(evbuf);
	EVUTIL_ASSERT(buf->write_in_progress && !buf->read_in_progress);
	evbuffer_unfreeze(evbuf, 1);
	evbuffer_drain(evbuf, nBytes);
	pin_release(buf,EVBUFFER_MEM_PINNED_W);
	buf->write_in_progress = 0;
	evbuffer_decref_and_unlock_(evbuf);
}