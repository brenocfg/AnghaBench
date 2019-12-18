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
 scalar_t__ HTTP_OK ; 
 int /*<<< orphan*/  evbuffer_add_buffer (struct evbuffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evhttp_request_get_input_buffer (struct evhttp_request*) ; 
 scalar_t__ evhttp_request_get_response_code (struct evhttp_request*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
http_stream_in_chunk(struct evhttp_request *req, void *arg)
{
	struct evbuffer *reply = arg;

	if (evhttp_request_get_response_code(req) != HTTP_OK) {
		fprintf(stderr, "FAILED\n");
		exit(1);
	}

	evbuffer_add_buffer(reply, evhttp_request_get_input_buffer(req));
}