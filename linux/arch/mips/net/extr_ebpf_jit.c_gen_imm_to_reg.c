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
struct jit_ctx {int dummy; } ;
struct bpf_insn {int imm; } ;
typedef  int s16 ;

/* Variables and functions */
 int MIPS_R_ZERO ; 
 int S16_MAX ; 
 int S16_MIN ; 
 int /*<<< orphan*/  addiu ; 
 int /*<<< orphan*/  emit_instr (struct jit_ctx*,int /*<<< orphan*/ ,int,int,...) ; 
 int /*<<< orphan*/  lui ; 

__attribute__((used)) static void gen_imm_to_reg(const struct bpf_insn *insn, int reg,
			   struct jit_ctx *ctx)
{
	if (insn->imm >= S16_MIN && insn->imm <= S16_MAX) {
		emit_instr(ctx, addiu, reg, MIPS_R_ZERO, insn->imm);
	} else {
		int lower = (s16)(insn->imm & 0xffff);
		int upper = insn->imm - lower;

		emit_instr(ctx, lui, reg, upper >> 16);
		emit_instr(ctx, addiu, reg, reg, lower);
	}
}