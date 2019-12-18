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
typedef  int /*<<< orphan*/  serf_bucket_alloc_t ;
struct TYPE_5__ {int /*<<< orphan*/  bucket; struct TYPE_5__* next; } ;
typedef  TYPE_1__ bucket_list_t ;
struct TYPE_6__ {TYPE_1__* done; scalar_t__ bucket_owner; } ;
typedef  TYPE_2__ aggregate_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  serf_bucket_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serf_bucket_mem_free (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void cleanup_aggregate(aggregate_context_t *ctx,
                              serf_bucket_alloc_t *allocator)
{
    bucket_list_t *next_list;

    /* If we finished reading a bucket during the previous read, then
     * we can now toss that bucket.
     */
    while (ctx->done != NULL) {
        next_list = ctx->done->next;

        if (ctx->bucket_owner) {
            serf_bucket_destroy(ctx->done->bucket);
        }
        serf_bucket_mem_free(allocator, ctx->done);

        ctx->done = next_list;
    }
}