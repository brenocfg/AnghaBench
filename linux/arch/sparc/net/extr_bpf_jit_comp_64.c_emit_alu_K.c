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
struct jit_ctx {int tmp_1_used; } ;

/* Variables and functions */
 unsigned int IMMED ; 
 unsigned int RD (unsigned int) ; 
 unsigned int RS1 (unsigned int) ; 
 unsigned int RS2 (unsigned int) ; 
 unsigned int S13 (unsigned int) ; 
 size_t TMP_REG_1 ; 
 unsigned int* bpf2sparc ; 
 int /*<<< orphan*/  emit (unsigned int,struct jit_ctx*) ; 
 int /*<<< orphan*/  emit_set_const_sext (unsigned int,unsigned int,struct jit_ctx*) ; 
 int is_simm13 (unsigned int) ; 

__attribute__((used)) static void emit_alu_K(unsigned int opcode, unsigned int dst, unsigned int imm,
		       struct jit_ctx *ctx)
{
	bool small_immed = is_simm13(imm);
	unsigned int insn = opcode;

	insn |= RS1(dst) | RD(dst);
	if (small_immed) {
		emit(insn | IMMED | S13(imm), ctx);
	} else {
		unsigned int tmp = bpf2sparc[TMP_REG_1];

		ctx->tmp_1_used = true;

		emit_set_const_sext(imm, tmp, ctx);
		emit(insn | RS2(tmp), ctx);
	}
}