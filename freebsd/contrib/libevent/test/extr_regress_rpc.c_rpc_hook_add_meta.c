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
 int EVRPC_CONTINUE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evrpc_hook_add_meta (void*,char*,char*,int) ; 
 int /*<<< orphan*/ * evrpc_hook_get_connection (void*) ; 

__attribute__((used)) static int
rpc_hook_add_meta(void *ctx, struct evhttp_request *req,
    struct evbuffer *evbuf, void *arg)
{
	evrpc_hook_add_meta(ctx, "meta", "test", 5);

	assert(evrpc_hook_get_connection(ctx) != NULL);

	return (EVRPC_CONTINUE);
}