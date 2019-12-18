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
struct evhttp_request {int dummy; } ;
struct evhttp_connection {int /*<<< orphan*/  bufev; } ;
struct evbuffer {int dummy; } ;

/* Variables and functions */
#define  ALL_DATA_READ 132 
#define  DATA_CORRUPTED 131 
#define  DATA_TOO_LONG 130 
 int /*<<< orphan*/  EVREQ_HTTP_DATA_TOO_LONG ; 
 int /*<<< orphan*/  EV_READ ; 
#define  MORE_DATA_EXPECTED 129 
#define  REQUEST_CANCELED 128 
 int /*<<< orphan*/  bufferevent_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct evbuffer* bufferevent_get_input (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evhttp_connection_done (struct evhttp_connection*) ; 
 int /*<<< orphan*/  evhttp_connection_fail_ (struct evhttp_connection*,int /*<<< orphan*/ ) ; 
 int evhttp_parse_headers_ (struct evhttp_request*,struct evbuffer*) ; 

__attribute__((used)) static void
evhttp_read_trailer(struct evhttp_connection *evcon, struct evhttp_request *req)
{
	struct evbuffer *buf = bufferevent_get_input(evcon->bufev);

	switch (evhttp_parse_headers_(req, buf)) {
	case DATA_CORRUPTED:
	case DATA_TOO_LONG:
		evhttp_connection_fail_(evcon, EVREQ_HTTP_DATA_TOO_LONG);
		break;
	case ALL_DATA_READ:
		bufferevent_disable(evcon->bufev, EV_READ);
		evhttp_connection_done(evcon);
		break;
	case MORE_DATA_EXPECTED:
	case REQUEST_CANCELED: /* ??? */
	default:
		break;
	}
}