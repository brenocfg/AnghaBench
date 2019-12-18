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
typedef  int u32 ;
typedef  int s64 ;
typedef  enum aarch64_reloc_op { ____Placeholder_aarch64_reloc_op } aarch64_reloc_op ;
typedef  enum aarch64_insn_movw_imm_type { ____Placeholder_aarch64_insn_movw_imm_type } aarch64_insn_movw_imm_type ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  AARCH64_INSN_IMM_16 ; 
 int AARCH64_INSN_IMM_MOVNZ ; 
 int ERANGE ; 
 int U16_MAX ; 
 int aarch64_insn_encode_immediate (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int do_reloc (int,int /*<<< orphan*/ *,int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int reloc_insn_movw(enum aarch64_reloc_op op, __le32 *place, u64 val,
			   int lsb, enum aarch64_insn_movw_imm_type imm_type)
{
	u64 imm;
	s64 sval;
	u32 insn = le32_to_cpu(*place);

	sval = do_reloc(op, place, val);
	imm = sval >> lsb;

	if (imm_type == AARCH64_INSN_IMM_MOVNZ) {
		/*
		 * For signed MOVW relocations, we have to manipulate the
		 * instruction encoding depending on whether or not the
		 * immediate is less than zero.
		 */
		insn &= ~(3 << 29);
		if (sval >= 0) {
			/* >=0: Set the instruction to MOVZ (opcode 10b). */
			insn |= 2 << 29;
		} else {
			/*
			 * <0: Set the instruction to MOVN (opcode 00b).
			 *     Since we've masked the opcode already, we
			 *     don't need to do anything other than
			 *     inverting the new immediate field.
			 */
			imm = ~imm;
		}
	}

	/* Update the instruction with the new encoding. */
	insn = aarch64_insn_encode_immediate(AARCH64_INSN_IMM_16, insn, imm);
	*place = cpu_to_le32(insn);

	if (imm > U16_MAX)
		return -ERANGE;

	return 0;
}