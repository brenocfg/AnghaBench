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
struct codegen_context {int seen; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_REG_FP ; 
 int SEEN_FUNC ; 
 scalar_t__ bpf_is_seen_register (struct codegen_context*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool bpf_has_stack_frame(struct codegen_context *ctx)
{
	/*
	 * We only need a stack frame if:
	 * - we call other functions (kernel helpers), or
	 * - the bpf program uses its stack area
	 * The latter condition is deduced from the usage of BPF_REG_FP
	 */
	return ctx->seen & SEEN_FUNC || bpf_is_seen_register(ctx, BPF_REG_FP);
}