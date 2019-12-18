#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct iovec {scalar_t__ iov_len; } ;
struct TYPE_8__ {TYPE_3__* data; } ;
typedef  TYPE_1__ serf_bucket_t ;
struct TYPE_9__ {struct TYPE_9__* next; TYPE_1__* bucket; } ;
typedef  TYPE_2__ bucket_list_t ;
typedef  int /*<<< orphan*/  apr_status_t ;
typedef  scalar_t__ apr_size_t ;
struct TYPE_10__ {int /*<<< orphan*/  hold_open_baton; int /*<<< orphan*/  (* hold_open ) (int /*<<< orphan*/ ,TYPE_1__*) ;TYPE_2__* list; TYPE_2__* done; } ;
typedef  TYPE_3__ aggregate_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_EOF ; 
 scalar_t__ APR_STATUS_IS_EAGAIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  APR_SUCCESS ; 
 scalar_t__ SERF_BUCKET_READ_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SERF_ERROR_WAIT_CONN ; 
 scalar_t__ SERF_READ_ALL_AVAIL ; 
 int /*<<< orphan*/  serf_bucket_read_iovec (TYPE_1__*,scalar_t__,int,struct iovec*,int*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static apr_status_t read_aggregate(serf_bucket_t *bucket,
                                   apr_size_t requested,
                                   int vecs_size, struct iovec *vecs,
                                   int *vecs_used)
{
    aggregate_context_t *ctx = bucket->data;
    int cur_vecs_used;
    apr_status_t status;

    *vecs_used = 0;

    if (!ctx->list) {
        if (ctx->hold_open) {
            return ctx->hold_open(ctx->hold_open_baton, bucket);
        }
        else {
            return APR_EOF;
        }
    }

    status = APR_SUCCESS;
    while (requested) {
        serf_bucket_t *head = ctx->list->bucket;

        status = serf_bucket_read_iovec(head, requested, vecs_size, vecs,
                                        &cur_vecs_used);

        if (SERF_BUCKET_READ_ERROR(status))
            return status;

        /* Add the number of vecs we read to our running total. */
        *vecs_used += cur_vecs_used;

        if (cur_vecs_used > 0 || status) {
            bucket_list_t *next_list;

            /* If we got SUCCESS (w/bytes) or EAGAIN, we want to return now
             * as it isn't safe to read more without returning to our caller.
             */
            if (!status || APR_STATUS_IS_EAGAIN(status) || status == SERF_ERROR_WAIT_CONN) {
                return status;
            }

            /* However, if we read EOF, we can stash this bucket in a
             * to-be-freed list and move on to the next bucket.  This ensures
             * that the bucket stays alive (so as not to violate our read
             * semantics).  We'll destroy this list of buckets the next time
             * we are asked to perform a read operation - thus ensuring the
             * proper read lifetime.
             */
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

            /* At this point, it safe to read the next bucket - if we can. */

            /* If the caller doesn't want ALL_AVAIL, decrement the size
             * of the items we just read from the list.
             */
            if (requested != SERF_READ_ALL_AVAIL) {
                int i;

                for (i = 0; i < cur_vecs_used; i++)
                    requested -= vecs[i].iov_len;
            }

            /* Adjust our vecs to account for what we just read. */
            vecs_size -= cur_vecs_used;
            vecs += cur_vecs_used;

            /* We reached our max.  Oh well. */
            if (!requested || !vecs_size) {
                return APR_SUCCESS;
            }
        }
    }

    return status;
}