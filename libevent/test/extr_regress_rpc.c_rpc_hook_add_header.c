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
struct evhttp_request {int /*<<< orphan*/  output_headers; int /*<<< orphan*/  input_headers; } ;
struct evbuffer {int dummy; } ;

/* Variables and functions */
 int EVRPC_CONTINUE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evhttp_add_header (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/ * evrpc_hook_get_connection (void*) ; 
 scalar_t__ strcmp (char*,char const*) ; 

__attribute__((used)) static int
rpc_hook_add_header(void *ctx, struct evhttp_request *req,
    struct evbuffer *evbuf, void *arg)
{
	const char *hook_type = arg;
	if (strcmp("input", hook_type) == 0)
		evhttp_add_header(req->input_headers, "X-Hook", hook_type);
	else
		evhttp_add_header(req->output_headers, "X-Hook", hook_type);

	assert(evrpc_hook_get_connection(ctx) != NULL);

	return (EVRPC_CONTINUE);
}