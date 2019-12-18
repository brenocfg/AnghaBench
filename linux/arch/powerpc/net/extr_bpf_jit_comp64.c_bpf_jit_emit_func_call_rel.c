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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct codegen_context {unsigned int idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  PPC_BLRL () ; 
 int /*<<< orphan*/  PPC_BPF_LL (int,int,int) ; 
 int /*<<< orphan*/  PPC_LI64 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PPC_MTLR (int) ; 
 int /*<<< orphan*/  PPC_NOP () ; 

__attribute__((used)) static void bpf_jit_emit_func_call_rel(u32 *image, struct codegen_context *ctx,
				       u64 func)
{
	unsigned int i, ctx_idx = ctx->idx;

	/* Load function address into r12 */
	PPC_LI64(12, func);

	/* For bpf-to-bpf function calls, the callee's address is unknown
	 * until the last extra pass. As seen above, we use PPC_LI64() to
	 * load the callee's address, but this may optimize the number of
	 * instructions required based on the nature of the address.
	 *
	 * Since we don't want the number of instructions emitted to change,
	 * we pad the optimized PPC_LI64() call with NOPs to guarantee that
	 * we always have a five-instruction sequence, which is the maximum
	 * that PPC_LI64() can emit.
	 */
	for (i = ctx->idx - ctx_idx; i < 5; i++)
		PPC_NOP();

#ifdef PPC64_ELF_ABI_v1
	/*
	 * Load TOC from function descriptor at offset 8.
	 * We can clobber r2 since we get called through a
	 * function pointer (so caller will save/restore r2)
	 * and since we don't use a TOC ourself.
	 */
	PPC_BPF_LL(2, 12, 8);
	/* Load actual entry point from function descriptor */
	PPC_BPF_LL(12, 12, 0);
#endif

	PPC_MTLR(12);
	PPC_BLRL();
}