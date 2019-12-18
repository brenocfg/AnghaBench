#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  allocator; TYPE_3__* data; } ;
typedef  TYPE_2__ serf_bucket_t ;
typedef  scalar_t__ apr_status_t ;
typedef  scalar_t__ apr_size_t ;
struct TYPE_11__ {scalar_t__ (* hold_open ) (int /*<<< orphan*/ ,TYPE_2__*) ;int /*<<< orphan*/  hold_open_baton; TYPE_1__* list; } ;
typedef  TYPE_3__ aggregate_context_t ;
struct TYPE_9__ {scalar_t__ next; TYPE_2__* bucket; } ;

/* Variables and functions */
 scalar_t__ APR_EAGAIN ; 
 scalar_t__ APR_EOF ; 
 scalar_t__ APR_SUCCESS ; 
 int /*<<< orphan*/  cleanup_aggregate (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ serf_bucket_peek (TYPE_2__*,char const**,scalar_t__*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static apr_status_t serf_aggregate_peek(serf_bucket_t *bucket,
                                        const char **data,
                                        apr_size_t *len)
{
    aggregate_context_t *ctx = bucket->data;
    serf_bucket_t *head;
    apr_status_t status;

    cleanup_aggregate(ctx, bucket->allocator);

    /* Peek the first bucket in the list, if any. */
    if (!ctx->list) {
        *len = 0;
        if (ctx->hold_open) {
            status = ctx->hold_open(ctx->hold_open_baton, bucket);
            if (status == APR_EAGAIN)
                status = APR_SUCCESS;
            return status;
        }
        else {
            return APR_EOF;
        }
    }

    head = ctx->list->bucket;

    status = serf_bucket_peek(head, data, len);

    if (status == APR_EOF) {
        if (ctx->list->next) {
            status = APR_SUCCESS;
        } else {
            if (ctx->hold_open) {
                status = ctx->hold_open(ctx->hold_open_baton, bucket);
                if (status == APR_EAGAIN)
                    status = APR_SUCCESS;
                return status;
            }
        }
    }

    return status;
}