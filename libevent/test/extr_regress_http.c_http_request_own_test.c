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
struct evhttp_connection {int dummy; } ;
struct evhttp {int dummy; } ;
struct basic_test_data {int /*<<< orphan*/  base; } ;
typedef  int /*<<< orphan*/  ev_uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVHTTP_REQ_GET ; 
 int /*<<< orphan*/  event_base_dispatch (int /*<<< orphan*/ ) ; 
 struct evhttp_connection* evhttp_connection_base_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evhttp_connection_free (struct evhttp_connection*) ; 
 int /*<<< orphan*/  evhttp_free (struct evhttp*) ; 
 int evhttp_make_request (struct evhttp_connection*,struct evhttp_request*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  evhttp_request_free (struct evhttp_request*) ; 
 struct evhttp_request* evhttp_request_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evhttp_request_own (struct evhttp_request*) ; 
 int /*<<< orphan*/  exit_base ; 
 int /*<<< orphan*/  http_request_no_action_done ; 
 struct evhttp* http_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int test_ok ; 
 int /*<<< orphan*/  tt_abort_msg (char*) ; 
 int /*<<< orphan*/  tt_assert (struct evhttp_connection*) ; 

__attribute__((used)) static void
http_request_own_test(void *arg)
{
	struct basic_test_data *data = arg;
	ev_uint16_t port = 0;
	struct evhttp_connection *evcon = NULL;
	struct evhttp_request *req = NULL;
	struct evhttp *http = http_setup(&port, data->base, 0);

	test_ok = 0;
	exit_base = data->base;

	evhttp_free(http);

	evcon = evhttp_connection_base_new(data->base, NULL, "127.0.0.1", port);
	tt_assert(evcon);

	req = evhttp_request_new(http_request_no_action_done, NULL);

	if (evhttp_make_request(evcon, req, EVHTTP_REQ_GET, "/test") == -1) {
		tt_abort_msg("Couldn't make request");
	}
	evhttp_request_own(req);

	event_base_dispatch(data->base);

 end:
	if (evcon)
		evhttp_connection_free(evcon);
	if (req)
		evhttp_request_free(req);

	test_ok = 1;
}