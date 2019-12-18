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
typedef  int /*<<< orphan*/  u32 ;
struct rv_jit_context {size_t ninsns; int /*<<< orphan*/ * insns; } ;

/* Variables and functions */

__attribute__((used)) static void emit(const u32 insn, struct rv_jit_context *ctx)
{
	if (ctx->insns)
		ctx->insns[ctx->ninsns] = insn;

	ctx->ninsns++;
}