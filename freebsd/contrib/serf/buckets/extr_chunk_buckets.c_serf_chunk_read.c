#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* data; } ;
typedef  TYPE_1__ serf_bucket_t ;
struct TYPE_6__ {scalar_t__ state; scalar_t__ last_status; int /*<<< orphan*/  chunk; } ;
typedef  TYPE_2__ chunk_context_t ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_size_t ;

/* Variables and functions */
 scalar_t__ APR_STATUS_IS_EOF (scalar_t__) ; 
 scalar_t__ STATE_CHUNK ; 
 scalar_t__ STATE_FETCH ; 
 scalar_t__ create_chunk (TYPE_1__*) ; 
 scalar_t__ serf_bucket_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static apr_status_t serf_chunk_read(serf_bucket_t *bucket,
                                    apr_size_t requested,
                                    const char **data, apr_size_t *len)
{
    chunk_context_t *ctx = bucket->data;
    apr_status_t status;

    /* Before proceeding, we need to fetch some data from the stream. */
    if (ctx->state == STATE_FETCH) {
        status = create_chunk(bucket);
        if (status) {
            return status;
        }
    }

    status = serf_bucket_read(ctx->chunk, requested, data, len);

    /* Mask EOF from aggregate bucket. */
    if (APR_STATUS_IS_EOF(status) && ctx->state == STATE_CHUNK) {
        status = ctx->last_status;
        ctx->state = STATE_FETCH;
    }

    return status;
}