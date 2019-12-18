#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  allocator; TYPE_3__* data; } ;
typedef  TYPE_2__ serf_bucket_t ;
struct TYPE_11__ {char* reason; int /*<<< orphan*/  code; int /*<<< orphan*/  version; } ;
struct TYPE_13__ {TYPE_2__* stream; TYPE_2__* headers; TYPE_1__ sl; } ;
typedef  TYPE_3__ response_context_t ;
typedef  int /*<<< orphan*/  apr_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SUCCESS ; 
 TYPE_2__* SERF_BUCKET_SIMPLE_STRING_LEN (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SERF_HTTP_VERSION_MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SERF_HTTP_VERSION_MINOR (int /*<<< orphan*/ ) ; 
 int apr_snprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serf_bucket_aggregate_append (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  serf_bucket_aggregate_become (TYPE_2__*) ; 
 int /*<<< orphan*/  serf_bucket_mem_free (int /*<<< orphan*/ ,TYPE_3__*) ; 
 TYPE_2__* serf_bucket_simple_copy_create (char*,int,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 

apr_status_t serf_response_full_become_aggregate(serf_bucket_t *bucket)
{
    response_context_t *ctx = bucket->data;
    serf_bucket_t *bkt;
    char buf[256];
    int size;

    serf_bucket_aggregate_become(bucket);

    /* Add reconstructed status line. */
    size = apr_snprintf(buf, 256, "HTTP/%d.%d %d ",
                        SERF_HTTP_VERSION_MAJOR(ctx->sl.version),
                        SERF_HTTP_VERSION_MINOR(ctx->sl.version),
                        ctx->sl.code);
    bkt = serf_bucket_simple_copy_create(buf, size,
                                         bucket->allocator);
    serf_bucket_aggregate_append(bucket, bkt);
    bkt = serf_bucket_simple_copy_create(ctx->sl.reason, strlen(ctx->sl.reason),
                                         bucket->allocator);
    serf_bucket_aggregate_append(bucket, bkt);
    bkt = SERF_BUCKET_SIMPLE_STRING_LEN("\r\n", 2,
                                        bucket->allocator);
    serf_bucket_aggregate_append(bucket, bkt);

    /* Add headers and stream buckets in order. */
    serf_bucket_aggregate_append(bucket, ctx->headers);
    serf_bucket_aggregate_append(bucket, ctx->stream);

    serf_bucket_mem_free(bucket->allocator, ctx);

    return APR_SUCCESS;
}