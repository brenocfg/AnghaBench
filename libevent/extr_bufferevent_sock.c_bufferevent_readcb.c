#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct evbuffer {int dummy; } ;
struct bufferevent_private {int connection_refused; scalar_t__ read_suspended; } ;
struct TYPE_2__ {scalar_t__ high; } ;
struct bufferevent {TYPE_1__ wm_read; struct evbuffer* input; } ;
typedef  int /*<<< orphan*/  evutil_socket_t ;
typedef  scalar_t__ ev_ssize_t ;

/* Variables and functions */
 short BEV_EVENT_EOF ; 
 short BEV_EVENT_ERROR ; 
 short BEV_EVENT_READING ; 
 short BEV_EVENT_TIMEOUT ; 
 struct bufferevent_private* BEV_UPCAST (struct bufferevent*) ; 
 scalar_t__ EVUTIL_ERR_CONNECT_REFUSED (int) ; 
 scalar_t__ EVUTIL_ERR_RW_RETRIABLE (int) ; 
 int /*<<< orphan*/  EV_READ ; 
 short EV_TIMEOUT ; 
 int /*<<< orphan*/  bufferevent_decref_and_unlock_ (struct bufferevent*) ; 
 int /*<<< orphan*/  bufferevent_decrement_read_buckets_ (struct bufferevent_private*,int) ; 
 int /*<<< orphan*/  bufferevent_disable (struct bufferevent*,int /*<<< orphan*/ ) ; 
 scalar_t__ bufferevent_get_read_max_ (struct bufferevent_private*) ; 
 int /*<<< orphan*/  bufferevent_incref_and_lock_ (struct bufferevent*) ; 
 int /*<<< orphan*/  bufferevent_run_eventcb_ (struct bufferevent*,short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bufferevent_trigger_nolock_ (struct bufferevent*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bufferevent_wm_suspend_read (struct bufferevent*) ; 
 int /*<<< orphan*/  evbuffer_freeze (struct evbuffer*,int /*<<< orphan*/ ) ; 
 scalar_t__ evbuffer_get_length (struct evbuffer*) ; 
 int evbuffer_read (struct evbuffer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  evbuffer_unfreeze (struct evbuffer*,int /*<<< orphan*/ ) ; 
 int evutil_socket_geterror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bufferevent_readcb(evutil_socket_t fd, short event, void *arg)
{
	struct bufferevent *bufev = arg;
	struct bufferevent_private *bufev_p = BEV_UPCAST(bufev);
	struct evbuffer *input;
	int res = 0;
	short what = BEV_EVENT_READING;
	ev_ssize_t howmuch = -1, readmax=-1;

	bufferevent_incref_and_lock_(bufev);

	if (event == EV_TIMEOUT) {
		/* Note that we only check for event==EV_TIMEOUT. If
		 * event==EV_TIMEOUT|EV_READ, we can safely ignore the
		 * timeout, since a read has occurred */
		what |= BEV_EVENT_TIMEOUT;
		goto error;
	}

	input = bufev->input;

	/*
	 * If we have a high watermark configured then we don't want to
	 * read more data than would make us reach the watermark.
	 */
	if (bufev->wm_read.high != 0) {
		howmuch = bufev->wm_read.high - evbuffer_get_length(input);
		/* we somehow lowered the watermark, stop reading */
		if (howmuch <= 0) {
			bufferevent_wm_suspend_read(bufev);
			goto done;
		}
	}
	readmax = bufferevent_get_read_max_(bufev_p);
	if (howmuch < 0 || howmuch > readmax) /* The use of -1 for "unlimited"
					       * uglifies this code. XXXX */
		howmuch = readmax;
	if (bufev_p->read_suspended)
		goto done;

	evbuffer_unfreeze(input, 0);
	res = evbuffer_read(input, fd, (int)howmuch); /* XXXX evbuffer_read would do better to take and return ev_ssize_t */
	evbuffer_freeze(input, 0);

	if (res == -1) {
		int err = evutil_socket_geterror(fd);
		if (EVUTIL_ERR_RW_RETRIABLE(err))
			goto reschedule;
		if (EVUTIL_ERR_CONNECT_REFUSED(err)) {
			bufev_p->connection_refused = 1;
			goto done;
		}
		/* error case */
		what |= BEV_EVENT_ERROR;
	} else if (res == 0) {
		/* eof case */
		what |= BEV_EVENT_EOF;
	}

	if (res <= 0)
		goto error;

	bufferevent_decrement_read_buckets_(bufev_p, res);

	/* Invoke the user callback - must always be called last */
	bufferevent_trigger_nolock_(bufev, EV_READ, 0);

	goto done;

 reschedule:
	goto done;

 error:
	bufferevent_disable(bufev, EV_READ);
	bufferevent_run_eventcb_(bufev, what, 0);

 done:
	bufferevent_decref_and_unlock_(bufev);
}