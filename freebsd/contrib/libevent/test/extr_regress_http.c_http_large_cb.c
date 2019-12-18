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
struct evbuffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BASIC_REQUEST_BODY ; 
 int /*<<< orphan*/  HTTP_OK ; 
 int /*<<< orphan*/  evbuffer_add_printf (struct evbuffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evbuffer_free (struct evbuffer*) ; 
 struct evbuffer* evbuffer_new () ; 
 int /*<<< orphan*/  evhttp_send_reply (struct evhttp_request*,int /*<<< orphan*/ ,char*,struct evbuffer*) ; 

__attribute__((used)) static void
http_large_cb(struct evhttp_request *req, void *arg)
{
	struct evbuffer *evb = evbuffer_new();
	int i;

	for (i = 0; i < 1<<20; ++i) {
		evbuffer_add_printf(evb, BASIC_REQUEST_BODY);
	}
	evhttp_send_reply(req, HTTP_OK, "Everything is fine", evb);
	evbuffer_free(evb);
}