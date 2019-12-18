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
struct evrpc_base {int /*<<< orphan*/  http_server; int /*<<< orphan*/  registered_rpcs; } ;
struct evrpc {void (* cb ) (struct evrpc_req_generic*,void*) ;void* cb_arg; struct evrpc_base* base; int /*<<< orphan*/  uri; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct evrpc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evhttp_set_cb (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct evrpc*) ; 
 char* evrpc_construct_uri (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evrpc_request_cb ; 
 int /*<<< orphan*/  mm_free (char*) ; 
 int /*<<< orphan*/  next ; 

int
evrpc_register_rpc(struct evrpc_base *base, struct evrpc *rpc,
    void (*cb)(struct evrpc_req_generic *, void *), void *cb_arg)
{
	char *constructed_uri = evrpc_construct_uri(rpc->uri);

	rpc->base = base;
	rpc->cb = cb;
	rpc->cb_arg = cb_arg;

	TAILQ_INSERT_TAIL(&base->registered_rpcs, rpc, next);

	evhttp_set_cb(base->http_server,
	    constructed_uri,
	    evrpc_request_cb,
	    rpc);

	mm_free(constructed_uri);

	return (0);
}