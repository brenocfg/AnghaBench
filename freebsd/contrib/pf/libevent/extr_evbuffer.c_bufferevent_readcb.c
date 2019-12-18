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
struct TYPE_2__ {int high; size_t low; } ;
struct bufferevent {int /*<<< orphan*/  cbarg; int /*<<< orphan*/  (* errorcb ) (struct bufferevent*,short,int /*<<< orphan*/ ) ;int /*<<< orphan*/  timeout_read; int /*<<< orphan*/  ev_read; int /*<<< orphan*/  (* readcb ) (struct bufferevent*,int /*<<< orphan*/ ) ;struct evbuffer* input; TYPE_1__ wm_read; } ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 short EVBUFFER_EOF ; 
 short EVBUFFER_ERROR ; 
 size_t EVBUFFER_LENGTH (struct evbuffer*) ; 
 short EVBUFFER_READ ; 
 short EVBUFFER_TIMEOUT ; 
 short EV_TIMEOUT ; 
 int /*<<< orphan*/  bufferevent_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bufferevent_read_pressure_cb ; 
 scalar_t__ errno ; 
 int evbuffer_read (struct evbuffer*,int,int) ; 
 int /*<<< orphan*/  evbuffer_setcb (struct evbuffer*,int /*<<< orphan*/ ,struct bufferevent*) ; 
 int /*<<< orphan*/  event_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct bufferevent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct bufferevent*,short,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bufferevent_readcb(int fd, short event, void *arg)
{
	struct bufferevent *bufev = arg;
	int res = 0;
	short what = EVBUFFER_READ;
	size_t len;
	int howmuch = -1;

	if (event == EV_TIMEOUT) {
		what |= EVBUFFER_TIMEOUT;
		goto error;
	}

	/*
	 * If we have a high watermark configured then we don't want to
	 * read more data than would make us reach the watermark.
	 */
	if (bufev->wm_read.high != 0)
		howmuch = bufev->wm_read.high;

	res = evbuffer_read(bufev->input, fd, howmuch);
	if (res == -1) {
		if (errno == EAGAIN || errno == EINTR)
			goto reschedule;
		/* error case */
		what |= EVBUFFER_ERROR;
	} else if (res == 0) {
		/* eof case */
		what |= EVBUFFER_EOF;
	}

	if (res <= 0)
		goto error;

	bufferevent_add(&bufev->ev_read, bufev->timeout_read);

	/* See if this callbacks meets the water marks */
	len = EVBUFFER_LENGTH(bufev->input);
	if (bufev->wm_read.low != 0 && len < bufev->wm_read.low)
		return;
	if (bufev->wm_read.high != 0 && len > bufev->wm_read.high) {
		struct evbuffer *buf = bufev->input;
		event_del(&bufev->ev_read);

		/* Now schedule a callback for us */
		evbuffer_setcb(buf, bufferevent_read_pressure_cb, bufev);
		return;
	}

	/* Invoke the user callback - must always be called last */
	if (bufev->readcb != NULL)
		(*bufev->readcb)(bufev, bufev->cbarg);
	return;

 reschedule:
	bufferevent_add(&bufev->ev_read, bufev->timeout_read);
	return;

 error:
	(*bufev->errorcb)(bufev, what, bufev->cbarg);
}