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
union offset_union {int un; } ;
typedef  int u32 ;
typedef  int u16 ;
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDST_L_BIT (int) ; 
 int RD_BITS (int) ; 
 int RN_BITS (int) ; 
 void* do_alignment_ldmstm ; 
 void* do_alignment_ldrdstrd ; 

__attribute__((used)) static void *
do_alignment_t32_to_handler(u32 *pinstr, struct pt_regs *regs,
			    union offset_union *poffset)
{
	u32 instr = *pinstr;
	u16 tinst1 = (instr >> 16) & 0xffff;
	u16 tinst2 = instr & 0xffff;

	switch (tinst1 & 0xffe0) {
	/* A6.3.5 Load/Store multiple */
	case 0xe880:		/* STM/STMIA/STMEA,LDM/LDMIA, PUSH/POP T2 */
	case 0xe8a0:		/* ...above writeback version */
	case 0xe900:		/* STMDB/STMFD, LDMDB/LDMEA */
	case 0xe920:		/* ...above writeback version */
		/* no need offset decision since handler calculates it */
		return do_alignment_ldmstm;

	case 0xf840:		/* POP/PUSH T3 (single register) */
		if (RN_BITS(instr) == 13 && (tinst2 & 0x09ff) == 0x0904) {
			u32 L = !!(LDST_L_BIT(instr));
			const u32 subset[2] = {
				0xe92d0000,	/* STMDB sp!,{registers} */
				0xe8bd0000,	/* LDMIA sp!,{registers} */
			};
			*pinstr = subset[L] | (1<<RD_BITS(instr));
			return do_alignment_ldmstm;
		}
		/* Else fall through for illegal instruction case */
		break;

	/* A6.3.6 Load/store double, STRD/LDRD(immed, lit, reg) */
	case 0xe860:
	case 0xe960:
	case 0xe8e0:
	case 0xe9e0:
		poffset->un = (tinst2 & 0xff) << 2;
		/* Fall through */

	case 0xe940:
	case 0xe9c0:
		return do_alignment_ldrdstrd;

	/*
	 * No need to handle load/store instructions up to word size
	 * since ARMv6 and later CPUs can perform unaligned accesses.
	 */
	default:
		break;
	}
	return NULL;
}