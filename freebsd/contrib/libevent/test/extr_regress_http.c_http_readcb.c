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
struct event_base {int dummy; } ;
struct bufferevent {int dummy; } ;
typedef  enum message_read_status { ____Placeholder_message_read_status } message_read_status ;

/* Variables and functions */
 int ALL_DATA_READ ; 
 char* BASIC_REQUEST_BODY ; 
 int /*<<< orphan*/  EV_READ ; 
 int /*<<< orphan*/  bufferevent_disable (struct bufferevent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bufferevent_get_input (struct bufferevent*) ; 
 scalar_t__ evbuffer_contains (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  event_base_loopexit (struct event_base*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * evhttp_find_header (int /*<<< orphan*/ ,char*) ; 
 int evhttp_parse_firstline_ (struct evhttp_request*,int /*<<< orphan*/ ) ; 
 int evhttp_parse_headers_ (struct evhttp_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evhttp_request_free (struct evhttp_request*) ; 
 int /*<<< orphan*/  evhttp_request_get_input_headers (struct evhttp_request*) ; 
 struct evhttp_request* evhttp_request_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int) ; 
 struct event_base* exit_base ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  test_ok ; 

__attribute__((used)) static void
http_readcb(struct bufferevent *bev, void *arg)
{
	const char *what = BASIC_REQUEST_BODY;
	struct event_base *my_base = arg;

	if (evbuffer_contains(bufferevent_get_input(bev), what)) {
		struct evhttp_request *req = evhttp_request_new(NULL, NULL);
		enum message_read_status done;

		/* req->kind = EVHTTP_RESPONSE; */
		done = evhttp_parse_firstline_(req, bufferevent_get_input(bev));
		if (done != ALL_DATA_READ)
			goto out;

		done = evhttp_parse_headers_(req, bufferevent_get_input(bev));
		if (done != ALL_DATA_READ)
			goto out;

		if (done == 1 &&
		    evhttp_find_header(evhttp_request_get_input_headers(req),
			"Content-Type") != NULL)
			test_ok++;

	 out:
		evhttp_request_free(req);
		bufferevent_disable(bev, EV_READ);
		if (exit_base)
			event_base_loopexit(exit_base, NULL);
		else if (my_base)
			event_base_loopexit(my_base, NULL);
		else {
			fprintf(stderr, "No way to exit loop!\n");
			exit(1);
		}
	}
}