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
struct TYPE_9__ {int /*<<< orphan*/  allocator; TYPE_3__* data; } ;
typedef  TYPE_1__ serf_bucket_t ;
struct TYPE_10__ {struct TYPE_10__* next; TYPE_1__* bucket; } ;
typedef  TYPE_2__ bucket_list_t ;
typedef  scalar_t__ apr_status_t ;
typedef  scalar_t__ apr_size_t ;
struct TYPE_11__ {scalar_t__ (* hold_open ) (int /*<<< orphan*/ ,TYPE_1__*) ;int /*<<< orphan*/  hold_open_baton; TYPE_2__* list; TYPE_2__* done; } ;
typedef  TYPE_3__ aggregate_context_t ;

/* Variables and functions */
 scalar_t__ APR_EAGAIN ; 
 scalar_t__ APR_EOF ; 
 scalar_t__ APR_SUCCESS ; 
 scalar_t__ SERF_BUCKET_READ_ERROR (scalar_t__) ; 
 int /*<<< orphan*/  cleanup_aggregate (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ serf_bucket_readline (TYPE_1__*,int,int*,char const**,scalar_t__*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static apr_status_t serf_aggregate_readline(serf_bucket_t *bucket,
                                            int acceptable, int *found,
                                            const char **data, apr_size_t *len)
{
    aggregate_context_t *ctx = bucket->data;
    apr_status_t status;

    cleanup_aggregate(ctx, bucket->allocator);

    do {
        serf_bucket_t *head;

        *len = 0;

        if (!ctx->list) {
            if (ctx->hold_open) {
                return ctx->hold_open(ctx->hold_open_baton, bucket);
            }
            else {
                return APR_EOF;
            }
        }

        head = ctx->list->bucket;

        status = serf_bucket_readline(head, acceptable, found,
                                      data, len);
        if (SERF_BUCKET_READ_ERROR(status))
            return status;

        if (status == APR_EOF) {
            bucket_list_t *next_list;

            /* head bucket is empty, move to to-be-cleaned-up list. */
            next_list = ctx->list->next;
            ctx->list->next = ctx->done;
            ctx->done = ctx->list;
            ctx->list = next_list;

            /* If we have no more in our list, return EOF. */
            if (!ctx->list) {
                if (ctx->hold_open) {
                    return ctx->hold_open(ctx->hold_open_baton, bucket);
                }
                else {
                    return APR_EOF;
                }
            }

            /* we read something, so bail out and let the appl. read again. */
            if (*len)
                status = APR_SUCCESS;
        }

        /* continue with APR_SUCCESS or APR_EOF and no data read yet. */
    } while (!*len && status != APR_EAGAIN);

    return status;
}