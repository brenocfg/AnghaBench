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
typedef  int u64 ;
struct jit_ctx {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  scalar_t__ s16 ;

/* Variables and functions */
 int MIPS_R_ZERO ; 
 int /*<<< orphan*/  daddiu ; 
 int /*<<< orphan*/  dsll_safe ; 
 int /*<<< orphan*/  emit_instr (struct jit_ctx*,int /*<<< orphan*/ ,int,int,...) ; 
 int /*<<< orphan*/  lui ; 
 int /*<<< orphan*/  ori ; 

__attribute__((used)) static void emit_const_to_reg(struct jit_ctx *ctx, int dst, u64 value)
{
	if (value >= 0xffffffffffff8000ull || value < 0x8000ull) {
		emit_instr(ctx, daddiu, dst, MIPS_R_ZERO, (int)value);
	} else if (value >= 0xffffffff80000000ull ||
		   (value < 0x80000000 && value > 0xffff)) {
		emit_instr(ctx, lui, dst, (s32)(s16)(value >> 16));
		emit_instr(ctx, ori, dst, dst, (unsigned int)(value & 0xffff));
	} else {
		int i;
		bool seen_part = false;
		int needed_shift = 0;

		for (i = 0; i < 4; i++) {
			u64 part = (value >> (16 * (3 - i))) & 0xffff;

			if (seen_part && needed_shift > 0 && (part || i == 3)) {
				emit_instr(ctx, dsll_safe, dst, dst, needed_shift);
				needed_shift = 0;
			}
			if (part) {
				if (i == 0 || (!seen_part && i < 3 && part < 0x8000)) {
					emit_instr(ctx, lui, dst, (s32)(s16)part);
					needed_shift = -16;
				} else {
					emit_instr(ctx, ori, dst,
						   seen_part ? dst : MIPS_R_ZERO,
						   (unsigned int)part);
				}
				seen_part = true;
			}
			if (seen_part)
				needed_shift += 16;
		}
	}
}