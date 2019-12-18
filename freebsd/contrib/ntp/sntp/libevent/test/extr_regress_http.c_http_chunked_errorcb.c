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
struct bufferevent {int dummy; } ;
typedef  enum message_read_status { ____Placeholder_message_read_status } message_read_status ;

/* Variables and functions */
 int ALL_DATA_READ ; 
 short BEV_EVENT_EOF ; 
 int /*<<< orphan*/  EVBUFFER_EOL_CRLF ; 
 int /*<<< orphan*/  bufferevent_get_input (struct bufferevent*) ; 
 int /*<<< orphan*/  evbuffer_drain (int /*<<< orphan*/ ,int) ; 
 scalar_t__ evbuffer_pullup (int /*<<< orphan*/ ,int) ; 
 char* evbuffer_readln (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_base_loopexit (void*,int /*<<< orphan*/ *) ; 
 char* evhttp_find_header (int /*<<< orphan*/ ,char*) ; 
 int evhttp_parse_firstline_ (struct evhttp_request*,int /*<<< orphan*/ ) ; 
 int evhttp_parse_headers_ (struct evhttp_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evhttp_request_free (struct evhttp_request*) ; 
 int /*<<< orphan*/  evhttp_request_get_input_headers (struct evhttp_request*) ; 
 struct evhttp_request* evhttp_request_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (void*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int test_ok ; 

__attribute__((used)) static void
http_chunked_errorcb(struct bufferevent *bev, short what, void *arg)
{
	struct evhttp_request *req = NULL;

	if (!test_ok)
		goto out;

	test_ok = -1;

	if ((what & BEV_EVENT_EOF) != 0) {
		const char *header;
		enum message_read_status done;
		req = evhttp_request_new(NULL, NULL);

		/* req->kind = EVHTTP_RESPONSE; */
		done = evhttp_parse_firstline_(req, bufferevent_get_input(bev));
		if (done != ALL_DATA_READ)
			goto out;

		done = evhttp_parse_headers_(req, bufferevent_get_input(bev));
		if (done != ALL_DATA_READ)
			goto out;

		header = evhttp_find_header(evhttp_request_get_input_headers(req), "Transfer-Encoding");
		if (header == NULL || strcmp(header, "chunked"))
			goto out;

		header = evhttp_find_header(evhttp_request_get_input_headers(req), "Connection");
		if (header == NULL || strcmp(header, "close"))
			goto out;

		header = evbuffer_readln(bufferevent_get_input(bev), NULL, EVBUFFER_EOL_CRLF);
		if (header == NULL)
			goto out;
		/* 13 chars */
		if (strcmp(header, "d")) {
			free((void*)header);
			goto out;
		}
		free((void*)header);

		if (strncmp((char *)evbuffer_pullup(bufferevent_get_input(bev), 13),
			"This is funny", 13))
			goto out;

		evbuffer_drain(bufferevent_get_input(bev), 13 + 2);

		header = evbuffer_readln(bufferevent_get_input(bev), NULL, EVBUFFER_EOL_CRLF);
		if (header == NULL)
			goto out;
		/* 18 chars */
		if (strcmp(header, "12"))
			goto out;
		free((char *)header);

		if (strncmp((char *)evbuffer_pullup(bufferevent_get_input(bev), 18),
			"but not hilarious.", 18))
			goto out;

		evbuffer_drain(bufferevent_get_input(bev), 18 + 2);

		header = evbuffer_readln(bufferevent_get_input(bev), NULL, EVBUFFER_EOL_CRLF);
		if (header == NULL)
			goto out;
		/* 8 chars */
		if (strcmp(header, "8")) {
			free((void*)header);
			goto out;
		}
		free((char *)header);

		if (strncmp((char *)evbuffer_pullup(bufferevent_get_input(bev), 8),
			"bwv 1052.", 8))
			goto out;

		evbuffer_drain(bufferevent_get_input(bev), 8 + 2);

		header = evbuffer_readln(bufferevent_get_input(bev), NULL, EVBUFFER_EOL_CRLF);
		if (header == NULL)
			goto out;
		/* 0 chars */
		if (strcmp(header, "0")) {
			free((void*)header);
			goto out;
		}
		free((void *)header);

		test_ok = 2;
	}

out:
	if (req)
		evhttp_request_free(req);

	event_base_loopexit(arg, NULL);
}