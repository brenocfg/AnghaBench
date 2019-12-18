#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_14__ ;

/* Type definitions */
struct TYPE_25__ {scalar_t__ len; scalar_t__ base; } ;
struct st_requests_status_ctx_t {int /*<<< orphan*/  mutex; TYPE_8__ req_data; int /*<<< orphan*/ * logconf; } ;
struct st_collect_req_status_cbdata_t {TYPE_14__* buffer; int /*<<< orphan*/ * member_0; } ;
struct TYPE_26__ {TYPE_7__* globalconf; } ;
typedef  TYPE_9__ h2o_context_t ;
struct TYPE_22__ {scalar_t__ (* foreach_request ) (TYPE_9__*,int /*<<< orphan*/ ,struct st_collect_req_status_cbdata_t*) ;} ;
struct TYPE_23__ {TYPE_5__ callbacks; } ;
struct TYPE_20__ {scalar_t__ (* foreach_request ) (TYPE_9__*,int /*<<< orphan*/ ,struct st_collect_req_status_cbdata_t*) ;} ;
struct TYPE_21__ {TYPE_3__ callbacks; } ;
struct TYPE_18__ {scalar_t__ (* foreach_request ) (TYPE_9__*,int /*<<< orphan*/ ,struct st_collect_req_status_cbdata_t*) ;} ;
struct TYPE_19__ {TYPE_1__ callbacks; } ;
struct TYPE_24__ {TYPE_6__ http3; TYPE_4__ http2; TYPE_2__ http1; } ;
struct TYPE_17__ {scalar_t__ size; int /*<<< orphan*/  bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  collect_req_status ; 
 int /*<<< orphan*/  h2o_buffer_consume (TYPE_14__**,int) ; 
 int /*<<< orphan*/  h2o_buffer_dispose (TYPE_14__**) ; 
 int /*<<< orphan*/  h2o_buffer_init (TYPE_14__**,int /*<<< orphan*/ *) ; 
 scalar_t__ h2o_mem_realloc (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  h2o_socket_buffer_prototype ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (TYPE_9__*,int /*<<< orphan*/ ,struct st_collect_req_status_cbdata_t*) ; 
 scalar_t__ stub2 (TYPE_9__*,int /*<<< orphan*/ ,struct st_collect_req_status_cbdata_t*) ; 
 scalar_t__ stub3 (TYPE_9__*,int /*<<< orphan*/ ,struct st_collect_req_status_cbdata_t*) ; 

__attribute__((used)) static void requests_status_per_thread(void *priv, h2o_context_t *ctx)
{
    struct st_requests_status_ctx_t *rsc = priv;
    struct st_collect_req_status_cbdata_t cbdata = {rsc->logconf};

    /* we encountered an error at init() time, return early */
    if (rsc->logconf == NULL)
        return;

    h2o_buffer_init(&cbdata.buffer, &h2o_socket_buffer_prototype);
    if (ctx->globalconf->http1.callbacks.foreach_request(ctx, collect_req_status, &cbdata) != 0 ||
        ctx->globalconf->http2.callbacks.foreach_request(ctx, collect_req_status, &cbdata) != 0 ||
        ctx->globalconf->http3.callbacks.foreach_request(ctx, collect_req_status, &cbdata) != 0) {
        h2o_buffer_dispose(&cbdata.buffer);
        return;
    }

    /* concat JSON elements */
    if (cbdata.buffer->size != 0) {
        pthread_mutex_lock(&rsc->mutex);
        if (rsc->req_data.len == 0)
            h2o_buffer_consume(&cbdata.buffer, 1); /* skip preceeding comma */
        rsc->req_data.base = h2o_mem_realloc(rsc->req_data.base, rsc->req_data.len + cbdata.buffer->size);
        memcpy(rsc->req_data.base + rsc->req_data.len, cbdata.buffer->bytes, cbdata.buffer->size);
        rsc->req_data.len += cbdata.buffer->size;
        pthread_mutex_unlock(&rsc->mutex);
    }

    h2o_buffer_dispose(&cbdata.buffer);
}