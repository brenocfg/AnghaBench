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
struct jit_ctx {int epilogue_offset; int idx; int /*<<< orphan*/ * target; } ;

/* Variables and functions */

__attribute__((used)) static inline int epilogue_offset(const struct jit_ctx *ctx)
{
	int to, from;
	/* No need for 1st dummy run */
	if (ctx->target == NULL)
		return 0;
	to = ctx->epilogue_offset;
	from = ctx->idx;

	return to - from - 2;
}