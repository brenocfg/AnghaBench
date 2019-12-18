#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_10__** our_stream; TYPE_4__* ssl_ctx; } ;
typedef  TYPE_3__ ssl_context_t ;
struct TYPE_13__ {void* status; } ;
struct TYPE_14__ {TYPE_6__* stream_next; TYPE_10__* pending; TYPE_10__* stream; TYPE_1__ databuf; void* status; } ;
struct TYPE_16__ {int /*<<< orphan*/  allocator; TYPE_2__ encrypt; } ;
typedef  TYPE_4__ serf_ssl_context_t ;
struct TYPE_17__ {TYPE_3__* data; } ;
typedef  TYPE_5__ serf_bucket_t ;
struct TYPE_18__ {struct TYPE_18__* next; TYPE_10__* bucket; } ;
typedef  TYPE_6__ bucket_list_t ;
struct TYPE_12__ {int /*<<< orphan*/  allocator; } ;

/* Variables and functions */
 void* APR_SUCCESS ; 
 TYPE_10__* serf_bucket_aggregate_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serf_bucket_destroy (TYPE_10__*) ; 
 int /*<<< orphan*/  serf_bucket_mem_free (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  serf_ssl_destroy_and_data (TYPE_5__*) ; 

__attribute__((used)) static void serf_ssl_encrypt_destroy_and_data(serf_bucket_t *bucket)
{
    ssl_context_t *ctx = bucket->data;
    serf_ssl_context_t *ssl_ctx = ctx->ssl_ctx;

    if (ssl_ctx->encrypt.stream == *ctx->our_stream) {
        serf_bucket_destroy(*ctx->our_stream);
        serf_bucket_destroy(ssl_ctx->encrypt.pending);

        /* Reset our encrypted status and databuf. */
        ssl_ctx->encrypt.status = APR_SUCCESS;
        ssl_ctx->encrypt.databuf.status = APR_SUCCESS;

        /* Advance to the next stream - if we have one. */
        if (ssl_ctx->encrypt.stream_next == NULL) {
            ssl_ctx->encrypt.stream = NULL;
            ssl_ctx->encrypt.pending = NULL;
        }
        else {
            bucket_list_t *cur;

            cur = ssl_ctx->encrypt.stream_next;
            ssl_ctx->encrypt.stream = cur->bucket;
            ssl_ctx->encrypt.pending =
                serf_bucket_aggregate_create(cur->bucket->allocator);
            ssl_ctx->encrypt.stream_next = cur->next;
            serf_bucket_mem_free(ssl_ctx->allocator, cur);
        }
    }
    else {
        /* Ah, darn.  We haven't sent this one along yet. */
        return;
    }
    serf_ssl_destroy_and_data(bucket);
}