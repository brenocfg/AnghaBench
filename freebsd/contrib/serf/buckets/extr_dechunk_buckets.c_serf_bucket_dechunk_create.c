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
struct TYPE_4__ {int /*<<< orphan*/  linebuf; int /*<<< orphan*/  state; int /*<<< orphan*/ * stream; } ;
typedef  TYPE_1__ dechunk_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  STATE_SIZE ; 
 int /*<<< orphan*/ * serf_bucket_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* serf_bucket_mem_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  serf_bucket_type_dechunk ; 
 int /*<<< orphan*/  serf_linebuf_init (int /*<<< orphan*/ *) ; 

serf_bucket_t *serf_bucket_dechunk_create(
    serf_bucket_t *stream,
    serf_bucket_alloc_t *allocator)
{
    dechunk_context_t *ctx;

    ctx = serf_bucket_mem_alloc(allocator, sizeof(*ctx));
    ctx->stream = stream;
    ctx->state = STATE_SIZE;

    serf_linebuf_init(&ctx->linebuf);

    return serf_bucket_create(&serf_bucket_type_dechunk, allocator, ctx);
}