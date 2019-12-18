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
struct evhttp_request {int /*<<< orphan*/  kind; } ;
struct evhttp_connection {int flags; int /*<<< orphan*/  bufev; } ;
struct evbuffer {int dummy; } ;

/* Variables and functions */
 int EVHTTP_CON_READING_ERROR ; 
 int /*<<< orphan*/  EVHTTP_RESPONSE ; 
 int /*<<< orphan*/  EVREQ_HTTP_EOF ; 
 struct evbuffer* bufferevent_get_output (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evbuffer_drain (struct evbuffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evbuffer_freeze (struct evbuffer*,int) ; 
 int /*<<< orphan*/  evbuffer_get_length (struct evbuffer*) ; 
 int /*<<< orphan*/  evbuffer_unfreeze (struct evbuffer*,int) ; 
 int /*<<< orphan*/  evhttp_connection_fail_ (struct evhttp_connection*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evhttp_start_read_ (struct evhttp_connection*) ; 

__attribute__((used)) static void
evhttp_connection_read_on_write_error(struct evhttp_connection *evcon,
    struct evhttp_request *req)
{
	struct evbuffer *buf;

	/** Second time, we can't read anything */
	if (evcon->flags & EVHTTP_CON_READING_ERROR) {
		evcon->flags &= ~EVHTTP_CON_READING_ERROR;
		evhttp_connection_fail_(evcon, EVREQ_HTTP_EOF);
		return;
	}

	req->kind = EVHTTP_RESPONSE;

	buf = bufferevent_get_output(evcon->bufev);
	evbuffer_unfreeze(buf, 1);
	evbuffer_drain(buf, evbuffer_get_length(buf));
	evbuffer_freeze(buf, 1);

	evhttp_start_read_(evcon);
	evcon->flags |= EVHTTP_CON_READING_ERROR;
}