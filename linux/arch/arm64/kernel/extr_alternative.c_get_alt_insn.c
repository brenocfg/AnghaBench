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
struct alt_instr {int dummy; } ;
typedef  unsigned long s32 ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  SZ_4K ; 
 unsigned long aarch64_get_branch_offset (int /*<<< orphan*/ ) ; 
 unsigned long aarch64_insn_adrp_get_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aarch64_insn_adrp_set_offset (int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ aarch64_insn_is_adrp (int /*<<< orphan*/ ) ; 
 scalar_t__ aarch64_insn_is_branch_imm (int /*<<< orphan*/ ) ; 
 scalar_t__ aarch64_insn_uses_literal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aarch64_set_branch_offset (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long align_down (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ branch_insn_requires_update (struct alt_instr*,unsigned long) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 get_alt_insn(struct alt_instr *alt, __le32 *insnptr, __le32 *altinsnptr)
{
	u32 insn;

	insn = le32_to_cpu(*altinsnptr);

	if (aarch64_insn_is_branch_imm(insn)) {
		s32 offset = aarch64_get_branch_offset(insn);
		unsigned long target;

		target = (unsigned long)altinsnptr + offset;

		/*
		 * If we're branching inside the alternate sequence,
		 * do not rewrite the instruction, as it is already
		 * correct. Otherwise, generate the new instruction.
		 */
		if (branch_insn_requires_update(alt, target)) {
			offset = target - (unsigned long)insnptr;
			insn = aarch64_set_branch_offset(insn, offset);
		}
	} else if (aarch64_insn_is_adrp(insn)) {
		s32 orig_offset, new_offset;
		unsigned long target;

		/*
		 * If we're replacing an adrp instruction, which uses PC-relative
		 * immediate addressing, adjust the offset to reflect the new
		 * PC. adrp operates on 4K aligned addresses.
		 */
		orig_offset  = aarch64_insn_adrp_get_offset(insn);
		target = align_down(altinsnptr, SZ_4K) + orig_offset;
		new_offset = target - align_down(insnptr, SZ_4K);
		insn = aarch64_insn_adrp_set_offset(insn, new_offset);
	} else if (aarch64_insn_uses_literal(insn)) {
		/*
		 * Disallow patching unhandled instructions using PC relative
		 * literal addresses
		 */
		BUG();
	}

	return insn;
}