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
struct evhttp {int dummy; } ;
struct evbuffer {int dummy; } ;
struct bufferevent {int dummy; } ;
struct basic_test_data {int /*<<< orphan*/  base; } ;
typedef  int /*<<< orphan*/  ev_uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  bufferevent_free (struct bufferevent*) ; 
 int /*<<< orphan*/  evbuffer_add_printf (struct evbuffer*,char*) ; 
 int /*<<< orphan*/  evbuffer_free (struct evbuffer*) ; 
 scalar_t__ evbuffer_get_length (struct evbuffer*) ; 
 struct evbuffer* evbuffer_new () ; 
 int /*<<< orphan*/  evbuffer_pullup (struct evbuffer*,int) ; 
 int /*<<< orphan*/  evhttp_free (struct evhttp*) ; 
 int /*<<< orphan*/  exit_base ; 
 int /*<<< orphan*/  http_run_bev_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 struct evhttp* http_setup_gencb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  http_timeout_cb ; 
 int test_ok ; 
 int /*<<< orphan*/  tt_assert (int) ; 

__attribute__((used)) static void
http_request_extra_body_test(void *arg)
{
	struct basic_test_data *data = arg;
	struct bufferevent *bev = NULL;
	ev_uint16_t port = 0;
	int i;
	struct evhttp *http =
		http_setup_gencb(&port, data->base, 0, http_timeout_cb, NULL);
	struct evbuffer *body = NULL;

	exit_base = data->base;
	test_ok = 0;

	body = evbuffer_new();
	for (i = 0; i < 10000; ++i)
		evbuffer_add_printf(body, "this is the body that HEAD should not have");

	http_run_bev_request(data->base, port,
		"HEAD /timeout HTTP/1.1\r\n"
		"Host: somehost\r\n"
		"Connection: close\r\n"
		"Content-Length: %i\r\n"
		"\r\n%s",
		(int)evbuffer_get_length(body),
		evbuffer_pullup(body, -1)
	);
	tt_assert(test_ok == -2);

	http_run_bev_request(data->base, port,
		"HEAD /__gencb__ HTTP/1.1\r\n"
		"Host: somehost\r\n"
		"Connection: close\r\n"
		"Content-Length: %i\r\n"
		"\r\n%s",
		(int)evbuffer_get_length(body),
		evbuffer_pullup(body, -1)
	);
	tt_assert(test_ok == -2);

 end:
	evhttp_free(http);
	if (bev)
		bufferevent_free(bev);
	if (body)
		evbuffer_free(body);
}