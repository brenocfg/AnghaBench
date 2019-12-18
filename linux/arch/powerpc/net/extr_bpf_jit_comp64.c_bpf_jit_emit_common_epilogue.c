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
struct codegen_context {int seen; scalar_t__ stack_size; } ;

/* Variables and functions */
 scalar_t__ BPF_PPC_STACKFRAME ; 
 int BPF_REG_10 ; 
 int BPF_REG_6 ; 
 int /*<<< orphan*/  PPC_ADDI (int,int,scalar_t__) ; 
 int /*<<< orphan*/  PPC_BPF_LL (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PPC_LR_STKOFF ; 
 int /*<<< orphan*/  PPC_MTLR (int /*<<< orphan*/ ) ; 
 int SEEN_FUNC ; 
 int /*<<< orphan*/ * b2p ; 
 scalar_t__ bpf_has_stack_frame (struct codegen_context*) ; 
 scalar_t__ bpf_is_seen_register (struct codegen_context*,int) ; 
 int /*<<< orphan*/  bpf_jit_stack_offsetof (struct codegen_context*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bpf_jit_emit_common_epilogue(u32 *image, struct codegen_context *ctx)
{
	int i;

	/* Restore NVRs */
	for (i = BPF_REG_6; i <= BPF_REG_10; i++)
		if (bpf_is_seen_register(ctx, i))
			PPC_BPF_LL(b2p[i], 1, bpf_jit_stack_offsetof(ctx, b2p[i]));

	/* Tear down our stack frame */
	if (bpf_has_stack_frame(ctx)) {
		PPC_ADDI(1, 1, BPF_PPC_STACKFRAME + ctx->stack_size);
		if (ctx->seen & SEEN_FUNC) {
			PPC_BPF_LL(0, 1, PPC_LR_STKOFF);
			PPC_MTLR(0);
		}
	}
}