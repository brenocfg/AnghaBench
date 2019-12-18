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
typedef  int /*<<< orphan*/  u32 ;
typedef  int s64 ;
typedef  enum aarch64_reloc_op { ____Placeholder_aarch64_reloc_op } aarch64_reloc_op ;
typedef  enum aarch64_insn_imm_type { ____Placeholder_aarch64_insn_imm_type } aarch64_insn_imm_type ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int BIT (int) ; 
 int ERANGE ; 
 int /*<<< orphan*/  aarch64_insn_encode_immediate (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int do_reloc (int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int reloc_insn_imm(enum aarch64_reloc_op op, __le32 *place, u64 val,
			  int lsb, int len, enum aarch64_insn_imm_type imm_type)
{
	u64 imm, imm_mask;
	s64 sval;
	u32 insn = le32_to_cpu(*place);

	/* Calculate the relocation value. */
	sval = do_reloc(op, place, val);
	sval >>= lsb;

	/* Extract the value bits and shift them to bit 0. */
	imm_mask = (BIT(lsb + len) - 1) >> lsb;
	imm = sval & imm_mask;

	/* Update the instruction's immediate field. */
	insn = aarch64_insn_encode_immediate(imm_type, insn, imm);
	*place = cpu_to_le32(insn);

	/*
	 * Extract the upper value bits (including the sign bit) and
	 * shift them to bit 0.
	 */
	sval = (s64)(sval & ~(imm_mask >> 1)) >> (len - 1);

	/*
	 * Overflow has occurred if the upper bits are not all equal to
	 * the sign bit of the value.
	 */
	if ((u64)(sval + 1) >= 2)
		return -ERANGE;

	return 0;
}