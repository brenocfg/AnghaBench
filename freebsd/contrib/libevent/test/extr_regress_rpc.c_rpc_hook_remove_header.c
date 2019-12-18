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
struct evhttp_request {int /*<<< orphan*/  input_headers; } ;
struct evbuffer {int dummy; } ;

/* Variables and functions */
 int EVRPC_CONTINUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  evhttp_add_header (int /*<<< orphan*/ ,char*,char*) ; 
 char* evhttp_find_header (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  evhttp_remove_header (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ evrpc_hook_find_meta (void*,char*,void**,size_t*) ; 
 int /*<<< orphan*/ * evrpc_hook_get_connection (void*) ; 
 scalar_t__ strcmp (char const*,void*) ; 

__attribute__((used)) static int
rpc_hook_remove_header(void *ctx, struct evhttp_request *req,
    struct evbuffer *evbuf, void *arg)
{
	const char *header = evhttp_find_header(req->input_headers, "X-Hook");
	void *data = NULL;
	size_t data_len = 0;

	assert(header != NULL);
	assert(strcmp(header, arg) == 0);

	evhttp_remove_header(req->input_headers, "X-Hook");
	evhttp_add_header(req->input_headers, "X-Pool-Hook", "ran");

	assert(evrpc_hook_find_meta(ctx, "meta", &data, &data_len) == 0);
	assert(data != NULL);
	assert(data_len == 5);

	assert(evrpc_hook_get_connection(ctx) != NULL);

	return (EVRPC_CONTINUE);
}