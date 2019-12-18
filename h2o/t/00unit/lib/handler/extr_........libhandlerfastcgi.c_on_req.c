#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_12__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  receiving; int /*<<< orphan*/  sending; } ;
struct TYPE_15__ {int /*<<< orphan*/  stop; int /*<<< orphan*/  proceed; } ;
struct st_fcgi_generator_t {int /*<<< orphan*/  connect_req; int /*<<< orphan*/  timeout; TYPE_10__* handler; TYPE_2__ resp; scalar_t__ sent_headers; int /*<<< orphan*/ * sock; TYPE_9__* req; TYPE_1__ super; } ;
struct TYPE_23__ {TYPE_8__* conn; int /*<<< orphan*/  pool; } ;
typedef  TYPE_9__ h2o_req_t ;
typedef  int /*<<< orphan*/  h2o_handler_t ;
struct TYPE_19__ {TYPE_4__** entries; } ;
struct TYPE_14__ {TYPE_5__ targets; } ;
struct TYPE_17__ {int /*<<< orphan*/  io_timeout; } ;
struct TYPE_13__ {TYPE_12__ sockpool; TYPE_3__ config; } ;
typedef  TYPE_10__ h2o_fastcgi_handler_t ;
struct TYPE_22__ {TYPE_7__* ctx; } ;
struct TYPE_20__ {int /*<<< orphan*/  hostinfo_getaddr; } ;
struct TYPE_21__ {TYPE_6__ receivers; int /*<<< orphan*/  loop; } ;
struct TYPE_18__ {int /*<<< orphan*/  url; } ;

/* Variables and functions */
 scalar_t__ close_generator ; 
 int /*<<< orphan*/  do_proceed ; 
 int /*<<< orphan*/  do_stop ; 
 int /*<<< orphan*/  h2o_buffer_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_doublebuffer_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_iovec_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct st_fcgi_generator_t* h2o_mem_alloc_shared (int /*<<< orphan*/ *,int,void (*) (void*)) ; 
 int /*<<< orphan*/  h2o_socket_buffer_prototype ; 
 int /*<<< orphan*/  h2o_socketpool_connect (int /*<<< orphan*/ *,TYPE_12__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct st_fcgi_generator_t*) ; 
 int /*<<< orphan*/  h2o_timer_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_timer_link (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  on_connect ; 
 int /*<<< orphan*/  on_connect_timeout ; 

__attribute__((used)) static int on_req(h2o_handler_t *_handler, h2o_req_t *req)
{
    h2o_fastcgi_handler_t *handler = (void *)_handler;
    struct st_fcgi_generator_t *generator;

    generator = h2o_mem_alloc_shared(&req->pool, sizeof(*generator), (void (*)(void *))close_generator);
    generator->super.proceed = do_proceed;
    generator->super.stop = do_stop;
    generator->handler = handler;
    generator->req = req;
    generator->sock = NULL;
    generator->sent_headers = 0;
    h2o_doublebuffer_init(&generator->resp.sending, &h2o_socket_buffer_prototype);
    h2o_buffer_init(&generator->resp.receiving, &h2o_socket_buffer_prototype);
    h2o_timer_init(&generator->timeout, on_connect_timeout);
    h2o_timer_link(req->conn->ctx->loop, generator->handler->config.io_timeout, &generator->timeout);

    h2o_socketpool_connect(&generator->connect_req, &handler->sockpool, &handler->sockpool.targets.entries[0]->url,
                           req->conn->ctx->loop, &req->conn->ctx->receivers.hostinfo_getaddr, h2o_iovec_init(NULL, 0), on_connect,
                           generator);

    return 0;
}