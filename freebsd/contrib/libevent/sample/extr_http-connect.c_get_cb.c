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
typedef  int /*<<< orphan*/  ev_ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  VERIFY (struct evhttp_request*) ; 
 int /*<<< orphan*/  evbuffer_drain (struct evbuffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evbuffer_get_length (struct evbuffer*) ; 
 int /*<<< orphan*/  evbuffer_pullup (struct evbuffer*,int /*<<< orphan*/ ) ; 
 struct evbuffer* evhttp_request_get_input_buffer (struct evhttp_request*) ; 
 int /*<<< orphan*/  fwrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void get_cb(struct evhttp_request *req, void *arg)
{
	ev_ssize_t len;
	struct evbuffer *evbuf;

	VERIFY(req);

	evbuf = evhttp_request_get_input_buffer(req);
	len = evbuffer_get_length(evbuf);
	fwrite(evbuffer_pullup(evbuf, len), len, 1, stdout);
	evbuffer_drain(evbuf, len);
}