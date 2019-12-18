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

/* Variables and functions */
 int /*<<< orphan*/  EVUTIL_ASSERT (void*) ; 
 scalar_t__ HTTP_OK ; 
 scalar_t__ evbuffer_get_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_base_loopexit (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * evhttp_find_header (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  evhttp_request_get_input_buffer (struct evhttp_request*) ; 
 int /*<<< orphan*/  evhttp_request_get_input_headers (struct evhttp_request*) ; 
 scalar_t__ evhttp_request_get_response_code (struct evhttp_request*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char*) ; 
 int test_ok ; 

__attribute__((used)) static void
http_request_empty_done(struct evhttp_request *req, void *arg)
{
	if (evhttp_request_get_response_code(req) != HTTP_OK) {
		fprintf(stderr, "FAILED\n");
		exit(1);
	}

	if (evhttp_find_header(evhttp_request_get_input_headers(req), "Date") == NULL) {
		fprintf(stderr, "FAILED\n");
		exit(1);
	}


	if (evhttp_find_header(evhttp_request_get_input_headers(req), "Content-Length") == NULL) {
		fprintf(stderr, "FAILED\n");
		exit(1);
	}

	if (strcmp(evhttp_find_header(evhttp_request_get_input_headers(req), "Content-Length"),
		"0")) {
		fprintf(stderr, "FAILED\n");
		exit(1);
	}

	if (evbuffer_get_length(evhttp_request_get_input_buffer(req)) != 0) {
		fprintf(stderr, "FAILED\n");
		exit(1);
	}

	test_ok = 1;
	EVUTIL_ASSERT(arg);
	event_base_loopexit(arg, NULL);
}