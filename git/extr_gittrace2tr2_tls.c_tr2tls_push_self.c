#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct tr2tls_thread_ctx {scalar_t__ nr_open_regions; int /*<<< orphan*/ * array_us_start; int /*<<< orphan*/  alloc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 struct tr2tls_thread_ctx* tr2tls_get_self () ; 

void tr2tls_push_self(uint64_t us_now)
{
	struct tr2tls_thread_ctx *ctx = tr2tls_get_self();

	ALLOC_GROW(ctx->array_us_start, ctx->nr_open_regions + 1, ctx->alloc);
	ctx->array_us_start[ctx->nr_open_regions++] = us_now;
}