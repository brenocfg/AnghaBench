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
struct codegen_context {int stack_size; } ;

/* Variables and functions */
 int BPF_PPC_NVR_MIN ; 
 int BPF_PPC_STACKFRAME ; 
 int /*<<< orphan*/  BUG () ; 
 scalar_t__ bpf_has_stack_frame (struct codegen_context*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int bpf_jit_stack_offsetof(struct codegen_context *ctx, int reg)
{
	if (reg >= BPF_PPC_NVR_MIN && reg < 32)
		return (bpf_has_stack_frame(ctx) ?
			(BPF_PPC_STACKFRAME + ctx->stack_size) : 0)
				- (8 * (32 - reg));

	pr_err("BPF JIT is asking about unknown registers");
	BUG();
}