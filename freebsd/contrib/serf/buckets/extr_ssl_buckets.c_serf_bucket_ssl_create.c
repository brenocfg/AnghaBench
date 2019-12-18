#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* ssl_ctx; } ;
typedef  TYPE_1__ ssl_context_t ;
struct TYPE_8__ {int /*<<< orphan*/  refcount; } ;
typedef  TYPE_2__ serf_ssl_context_t ;
typedef  int /*<<< orphan*/  serf_bucket_type_t ;
typedef  int /*<<< orphan*/  serf_bucket_t ;
typedef  int /*<<< orphan*/  serf_bucket_alloc_t ;

/* Variables and functions */
 int /*<<< orphan*/ * serf_bucket_create (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* serf_bucket_mem_alloc (int /*<<< orphan*/ *,int) ; 
 TYPE_2__* ssl_init_context (int /*<<< orphan*/ *) ; 

__attribute__((used)) static serf_bucket_t * serf_bucket_ssl_create(
    serf_ssl_context_t *ssl_ctx,
    serf_bucket_alloc_t *allocator,
    const serf_bucket_type_t *type)
{
    ssl_context_t *ctx;

    ctx = serf_bucket_mem_alloc(allocator, sizeof(*ctx));
    if (!ssl_ctx) {
        ctx->ssl_ctx = ssl_init_context(allocator);
    }
    else {
        ctx->ssl_ctx = ssl_ctx;
    }
    ctx->ssl_ctx->refcount++;

    return serf_bucket_create(type, allocator, ctx);
}