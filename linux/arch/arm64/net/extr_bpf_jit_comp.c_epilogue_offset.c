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
struct jit_ctx {int epilogue_offset; int idx; } ;

/* Variables and functions */

__attribute__((used)) static inline int epilogue_offset(const struct jit_ctx *ctx)
{
	int to = ctx->epilogue_offset;
	int from = ctx->idx;

	return to - from;
}