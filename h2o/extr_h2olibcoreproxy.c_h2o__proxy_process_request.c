#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct rp_generator_t {int /*<<< orphan*/  client; } ;
typedef  int /*<<< orphan*/  h2o_url_t ;
struct TYPE_12__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  authority; int /*<<< orphan*/  scheme; TYPE_3__* conn; TYPE_5__* overrides; } ;
typedef  TYPE_4__ h2o_req_t ;
struct TYPE_13__ {int /*<<< orphan*/  proxy_preserve_host; int /*<<< orphan*/ * connpool; } ;
typedef  TYPE_5__ h2o_req_overrides_t ;
typedef  int /*<<< orphan*/  h2o_httpclient_ctx_t ;
typedef  int /*<<< orphan*/  h2o_httpclient_connection_pool_t ;
struct TYPE_11__ {TYPE_2__* ctx; } ;
struct TYPE_9__ {int /*<<< orphan*/  connpool; } ;
struct TYPE_10__ {TYPE_1__ proxy; } ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 int /*<<< orphan*/ * get_client_ctx (TYPE_4__*) ; 
 int /*<<< orphan*/  h2o_httpclient_connect (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct rp_generator_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_iovec_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_url_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  on_connect ; 
 struct rp_generator_t* proxy_send_prepare (TYPE_4__*) ; 

void h2o__proxy_process_request(h2o_req_t *req)
{
    h2o_req_overrides_t *overrides = req->overrides;
    h2o_httpclient_ctx_t *client_ctx = get_client_ctx(req);
    h2o_url_t target_buf, *target = &target_buf;

    h2o_httpclient_connection_pool_t *connpool = &req->conn->ctx->proxy.connpool;
    if (overrides != NULL && overrides->connpool != NULL) {
        connpool = overrides->connpool;
        if (!overrides->proxy_preserve_host)
            target = NULL;
    }
    if (target == &target_buf)
        h2o_url_init(&target_buf, req->scheme, req->authority, h2o_iovec_init(H2O_STRLIT("/")));

    struct rp_generator_t *self = proxy_send_prepare(req);

    /*
      When the PROXY protocol is being used (i.e. when overrides->use_proxy_protocol is set), the client needs to establish a new
     connection even when there is a pooled connection to the peer, since the header (as defined in
     https://www.haproxy.org/download/1.8/doc/proxy-protocol.txt) needs to be sent at the beginning of the connection.

     However, currently h2o_http1client_connect doesn't provide an interface to enforce estabilishing a new connection. In other
     words, there is a chance that we would use a pool connection here.

     OTOH, the probability of seeing such issue is rare; it would only happen if the same destination identified by its host:port is
     accessed in both ways (i.e. in one path with use_proxy_protocol set and in the other path without).

     So I leave this as it is for the time being.
     */
    h2o_httpclient_connect(&self->client, &req->pool, self, client_ctx, connpool, target, on_connect);
}