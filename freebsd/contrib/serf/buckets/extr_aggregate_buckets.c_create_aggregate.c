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
typedef  int /*<<< orphan*/  serf_bucket_alloc_t ;
struct TYPE_4__ {int bucket_owner; int /*<<< orphan*/ * hold_open_baton; int /*<<< orphan*/ * hold_open; int /*<<< orphan*/ * done; int /*<<< orphan*/ * last; int /*<<< orphan*/ * list; } ;
typedef  TYPE_1__ aggregate_context_t ;

/* Variables and functions */
 TYPE_1__* serf_bucket_mem_alloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static aggregate_context_t *create_aggregate(serf_bucket_alloc_t *allocator)
{
    aggregate_context_t *ctx;

    ctx = serf_bucket_mem_alloc(allocator, sizeof(*ctx));

    ctx->list = NULL;
    ctx->last = NULL;
    ctx->done = NULL;
    ctx->hold_open = NULL;
    ctx->hold_open_baton = NULL;
    ctx->bucket_owner = 1;

    return ctx;
}