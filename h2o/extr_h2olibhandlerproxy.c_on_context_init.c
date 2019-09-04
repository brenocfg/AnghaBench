#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct TYPE_19__ {scalar_t__ ratio; } ;
struct TYPE_18__ {int /*<<< orphan*/  timeout; scalar_t__ enabled; } ;
struct TYPE_20__ {scalar_t__ io_timeout; scalar_t__ connect_timeout; scalar_t__ first_byte_timeout; scalar_t__ keepalive_timeout; scalar_t__ max_buffer_size; TYPE_6__ http2; TYPE_5__ websocket; } ;
struct rp_handler_t {TYPE_7__ config; int /*<<< orphan*/  super; int /*<<< orphan*/  sockpool; } ;
struct rp_handler_context_t {TYPE_9__* client_ctx; int /*<<< orphan*/  connpool; } ;
struct TYPE_21__ {scalar_t__ ratio; int counter; } ;
struct TYPE_22__ {scalar_t__ io_timeout; scalar_t__ connect_timeout; scalar_t__ first_byte_timeout; scalar_t__ keepalive_timeout; scalar_t__ max_buffer_size; TYPE_8__ http2; int /*<<< orphan*/ * websocket_timeout; int /*<<< orphan*/ * getaddr_receiver; int /*<<< orphan*/  loop; } ;
typedef  TYPE_9__ h2o_httpclient_ctx_t ;
typedef  int /*<<< orphan*/  h2o_handler_t ;
struct TYPE_17__ {int /*<<< orphan*/  hostinfo_getaddr; } ;
struct TYPE_13__ {TYPE_4__ receivers; int /*<<< orphan*/  loop; TYPE_3__* globalconf; } ;
typedef  TYPE_10__ h2o_context_t ;
struct TYPE_14__ {scalar_t__ ratio; } ;
struct TYPE_15__ {scalar_t__ io_timeout; scalar_t__ connect_timeout; scalar_t__ first_byte_timeout; scalar_t__ keepalive_timeout; scalar_t__ max_buffer_size; TYPE_1__ http2; } ;
struct TYPE_16__ {TYPE_2__ proxy; } ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_context_set_handler_context (TYPE_10__*,int /*<<< orphan*/ *,struct rp_handler_context_t*) ; 
 int /*<<< orphan*/  h2o_httpclient_connection_pool_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* h2o_mem_alloc (int) ; 
 int /*<<< orphan*/  h2o_socketpool_register_loop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct rp_handler_context_t*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void on_context_init(h2o_handler_t *_self, h2o_context_t *ctx)
{
    struct rp_handler_t *self = (void *)_self;

    /* use the loop of first context for handling socketpool timeouts */
    h2o_socketpool_register_loop(self->sockpool, ctx->loop);

    struct rp_handler_context_t *handler_ctx = h2o_mem_alloc(sizeof(*handler_ctx));
    memset(handler_ctx, 0, sizeof(*handler_ctx));
    h2o_httpclient_connection_pool_init(&handler_ctx->connpool, self->sockpool);
    h2o_context_set_handler_context(ctx, &self->super, handler_ctx);

    /* setup a specific client context only if we need to */
    if (ctx->globalconf->proxy.io_timeout == self->config.io_timeout &&
        ctx->globalconf->proxy.connect_timeout == self->config.connect_timeout &&
        ctx->globalconf->proxy.first_byte_timeout == self->config.first_byte_timeout &&
        ctx->globalconf->proxy.keepalive_timeout == self->config.keepalive_timeout &&
        ctx->globalconf->proxy.max_buffer_size == self->config.max_buffer_size &&
        ctx->globalconf->proxy.http2.ratio == self->config.http2.ratio && !self->config.websocket.enabled)
        return;

    h2o_httpclient_ctx_t *client_ctx = h2o_mem_alloc(sizeof(*ctx));
    client_ctx->loop = ctx->loop;
    client_ctx->getaddr_receiver = &ctx->receivers.hostinfo_getaddr;
    client_ctx->io_timeout = self->config.io_timeout;
    client_ctx->connect_timeout = self->config.connect_timeout;
    client_ctx->first_byte_timeout = self->config.first_byte_timeout;
    client_ctx->keepalive_timeout = self->config.keepalive_timeout;
    if (self->config.websocket.enabled) {
        client_ctx->websocket_timeout = &self->config.websocket.timeout;
    } else {
        client_ctx->websocket_timeout = NULL;
    }

    client_ctx->max_buffer_size = self->config.max_buffer_size;
    client_ctx->http2.ratio = self->config.http2.ratio;
    client_ctx->http2.counter = -1;

    handler_ctx->client_ctx = client_ctx;
}