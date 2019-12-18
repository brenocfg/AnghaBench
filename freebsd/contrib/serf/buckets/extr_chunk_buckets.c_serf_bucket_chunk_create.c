#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  serf_bucket_t ;
typedef  int /*<<< orphan*/  serf_bucket_alloc_t ;
struct TYPE_4__ {int /*<<< orphan*/ * stream; int /*<<< orphan*/  chunk; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ chunk_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  STATE_FETCH ; 
 int /*<<< orphan*/  serf_bucket_aggregate_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * serf_bucket_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* serf_bucket_mem_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  serf_bucket_type_chunk ; 

serf_bucket_t *serf_bucket_chunk_create(
    serf_bucket_t *stream, serf_bucket_alloc_t *allocator)
{
    chunk_context_t *ctx;

    ctx = serf_bucket_mem_alloc(allocator, sizeof(*ctx));
    ctx->state = STATE_FETCH;
    ctx->chunk = serf_bucket_aggregate_create(allocator);
    ctx->stream = stream;

    return serf_bucket_create(&serf_bucket_type_chunk, allocator, ctx);
}