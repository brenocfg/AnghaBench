#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_2__* ssl_ctx; TYPE_4__** our_stream; int /*<<< orphan*/ * databuf; } ;
typedef  TYPE_3__ ssl_context_t ;
typedef  int /*<<< orphan*/  serf_ssl_context_t ;
struct TYPE_16__ {int /*<<< orphan*/  allocator; TYPE_3__* data; } ;
typedef  TYPE_4__ serf_bucket_t ;
typedef  int /*<<< orphan*/  serf_bucket_alloc_t ;
struct TYPE_17__ {struct TYPE_17__* next; TYPE_4__* bucket; } ;
typedef  TYPE_5__ bucket_list_t ;
struct TYPE_13__ {TYPE_5__* stream_next; TYPE_4__* stream; int /*<<< orphan*/  databuf; } ;
struct TYPE_14__ {TYPE_1__ encrypt; int /*<<< orphan*/  allocator; } ;

/* Variables and functions */
 int /*<<< orphan*/  serf_bucket_aggregate_append (TYPE_4__*,TYPE_4__*) ; 
 TYPE_4__* serf_bucket_aggregate_create (int /*<<< orphan*/ ) ; 
 TYPE_5__* serf_bucket_mem_alloc (int /*<<< orphan*/ ,int) ; 
 TYPE_4__* serf_bucket_ssl_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serf_bucket_type_ssl_encrypt ; 

serf_bucket_t *serf_bucket_ssl_encrypt_create(
    serf_bucket_t *stream,
    serf_ssl_context_t *ssl_ctx,
    serf_bucket_alloc_t *allocator)
{
    serf_bucket_t *bkt;
    ssl_context_t *ctx;

    bkt = serf_bucket_ssl_create(ssl_ctx, allocator,
                                 &serf_bucket_type_ssl_encrypt);

    ctx = bkt->data;

    ctx->databuf = &ctx->ssl_ctx->encrypt.databuf;
    ctx->our_stream = &ctx->ssl_ctx->encrypt.stream;
    if (ctx->ssl_ctx->encrypt.stream == NULL) {
        serf_bucket_t *tmp = serf_bucket_aggregate_create(stream->allocator);
        serf_bucket_aggregate_append(tmp, stream);
        ctx->ssl_ctx->encrypt.stream = tmp;
    }
    else {
        bucket_list_t *new_list;

        new_list = serf_bucket_mem_alloc(ctx->ssl_ctx->allocator,
                                         sizeof(*new_list));
        new_list->bucket = stream;
        new_list->next = NULL;
        if (ctx->ssl_ctx->encrypt.stream_next == NULL) {
            ctx->ssl_ctx->encrypt.stream_next = new_list;
        }
        else {
            bucket_list_t *scan = ctx->ssl_ctx->encrypt.stream_next;

            while (scan->next != NULL)
                scan = scan->next;
            scan->next = new_list;
        }
    }

    return bkt;
}