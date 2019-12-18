#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* data; } ;
typedef  TYPE_1__ serf_bucket_t ;
struct TYPE_5__ {scalar_t__ state; int /*<<< orphan*/  chunk; } ;
typedef  TYPE_2__ chunk_context_t ;
typedef  int /*<<< orphan*/  apr_status_t ;
typedef  int /*<<< orphan*/  apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_EAGAIN ; 
 scalar_t__ APR_STATUS_IS_EOF (int /*<<< orphan*/ ) ; 
 scalar_t__ STATE_CHUNK ; 
 int /*<<< orphan*/  serf_bucket_peek (int /*<<< orphan*/ ,char const**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static apr_status_t serf_chunk_peek(serf_bucket_t *bucket,
                                     const char **data,
                                     apr_size_t *len)
{
    chunk_context_t *ctx = bucket->data;
    apr_status_t status;

    status = serf_bucket_peek(ctx->chunk, data, len);

    /* Mask EOF from aggregate bucket. */
    if (APR_STATUS_IS_EOF(status) && ctx->state == STATE_CHUNK) {
        status = APR_EAGAIN;
    }

    return status;
}