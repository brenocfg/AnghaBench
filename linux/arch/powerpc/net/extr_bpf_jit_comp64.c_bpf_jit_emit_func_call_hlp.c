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
struct codegen_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PPC_BLRL () ; 
 int /*<<< orphan*/  PPC_BPF_LL (int,int,int) ; 
 int /*<<< orphan*/  PPC_FUNC_ADDR (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PPC_LI64 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PPC_MTLR (int) ; 
 size_t TMP_REG_1 ; 
 size_t TMP_REG_2 ; 
 int* b2p ; 

__attribute__((used)) static void bpf_jit_emit_func_call_hlp(u32 *image, struct codegen_context *ctx,
				       u64 func)
{
#ifdef PPC64_ELF_ABI_v1
	/* func points to the function descriptor */
	PPC_LI64(b2p[TMP_REG_2], func);
	/* Load actual entry point from function descriptor */
	PPC_BPF_LL(b2p[TMP_REG_1], b2p[TMP_REG_2], 0);
	/* ... and move it to LR */
	PPC_MTLR(b2p[TMP_REG_1]);
	/*
	 * Load TOC from function descriptor at offset 8.
	 * We can clobber r2 since we get called through a
	 * function pointer (so caller will save/restore r2)
	 * and since we don't use a TOC ourself.
	 */
	PPC_BPF_LL(2, b2p[TMP_REG_2], 8);
#else
	/* We can clobber r12 */
	PPC_FUNC_ADDR(12, func);
	PPC_MTLR(12);
#endif
	PPC_BLRL();
}