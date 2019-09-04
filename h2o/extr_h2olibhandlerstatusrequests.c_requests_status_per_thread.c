#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_11__ ;

/* Type definitions */
struct TYPE_20__ {scalar_t__ len; scalar_t__ base; } ;
struct st_requests_status_ctx_t {int /*<<< orphan*/  mutex; TYPE_6__ req_data; int /*<<< orphan*/ * logconf; } ;
struct st_collect_req_status_cbdata_t {TYPE_11__* buffer; int /*<<< orphan*/ * member_0; } ;
struct TYPE_21__ {TYPE_5__* globalconf; } ;
typedef  TYPE_7__ h2o_context_t ;
struct TYPE_17__ {int /*<<< orphan*/  (* foreach_request ) (TYPE_7__*,int /*<<< orphan*/ ,struct st_collect_req_status_cbdata_t*) ;} ;
struct TYPE_18__ {TYPE_3__ callbacks; } ;
struct TYPE_15__ {int /*<<< orphan*/  (* foreach_request ) (TYPE_7__*,int /*<<< orphan*/ ,struct st_collect_req_status_cbdata_t*) ;} ;
struct TYPE_16__ {TYPE_1__ callbacks; } ;
struct TYPE_19__ {TYPE_4__ http2; TYPE_2__ http1; } ;
struct TYPE_14__ {scalar_t__ size; int /*<<< orphan*/  bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  collect_req_status ; 
 int /*<<< orphan*/  h2o_buffer_consume (TYPE_11__**,int) ; 
 int /*<<< orphan*/  h2o_buffer_dispose (TYPE_11__**) ; 
 int /*<<< orphan*/  h2o_buffer_init (TYPE_11__**,int /*<<< orphan*/ *) ; 
 scalar_t__ h2o_mem_realloc (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  h2o_socket_buffer_prototype ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_7__*,int /*<<< orphan*/ ,struct st_collect_req_status_cbdata_t*) ; 
 int /*<<< orphan*/  stub2 (TYPE_7__*,int /*<<< orphan*/ ,struct st_collect_req_status_cbdata_t*) ; 

__attribute__((used)) static void requests_status_per_thread(void *priv, h2o_context_t *ctx)
{
    struct st_requests_status_ctx_t *rsc = priv;
    struct st_collect_req_status_cbdata_t cbdata = {rsc->logconf};

    /* we encountered an error at init() time, return early */
    if (rsc->logconf == NULL)
        return;

    h2o_buffer_init(&cbdata.buffer, &h2o_socket_buffer_prototype);
    ctx->globalconf->http1.callbacks.foreach_request(ctx, collect_req_status, &cbdata);
    ctx->globalconf->http2.callbacks.foreach_request(ctx, collect_req_status, &cbdata);

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