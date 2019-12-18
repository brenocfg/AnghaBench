#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct module {int /*<<< orphan*/  name; } ;
struct TYPE_11__ {int r_offset; int /*<<< orphan*/  r_info; scalar_t__ r_addend; } ;
struct TYPE_10__ {int sh_size; size_t sh_info; scalar_t__ sh_addr; } ;
struct TYPE_9__ {scalar_t__ st_value; } ;
typedef  TYPE_1__ Elf64_Sym ;
typedef  TYPE_2__ Elf64_Shdr ;
typedef  TYPE_3__ Elf64_Rela ;

/* Variables and functions */
 int /*<<< orphan*/  AARCH64_INSN_IMM_12 ; 
 int /*<<< orphan*/  AARCH64_INSN_IMM_14 ; 
 int /*<<< orphan*/  AARCH64_INSN_IMM_19 ; 
 int /*<<< orphan*/  AARCH64_INSN_IMM_26 ; 
 int /*<<< orphan*/  AARCH64_INSN_IMM_ADR ; 
 int /*<<< orphan*/  AARCH64_INSN_IMM_MOVKZ ; 
 int /*<<< orphan*/  AARCH64_INSN_IMM_MOVNZ ; 
 int /*<<< orphan*/  CONFIG_ARM64_MODULE_PLTS ; 
 int ELF64_R_SYM (int /*<<< orphan*/ ) ; 
 int ELF64_R_TYPE (int /*<<< orphan*/ ) ; 
 int ENOEXEC ; 
 int ERANGE ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RELOC_OP_ABS ; 
 int /*<<< orphan*/  RELOC_OP_PREL ; 
#define  R_AARCH64_ABS16 166 
#define  R_AARCH64_ABS32 165 
#define  R_AARCH64_ABS64 164 
#define  R_AARCH64_ADD_ABS_LO12_NC 163 
#define  R_AARCH64_ADR_PREL_LO21 162 
#define  R_AARCH64_ADR_PREL_PG_HI21 161 
#define  R_AARCH64_ADR_PREL_PG_HI21_NC 160 
#define  R_AARCH64_CALL26 159 
#define  R_AARCH64_CONDBR19 158 
#define  R_AARCH64_JUMP26 157 
#define  R_AARCH64_LDST128_ABS_LO12_NC 156 
#define  R_AARCH64_LDST16_ABS_LO12_NC 155 
#define  R_AARCH64_LDST32_ABS_LO12_NC 154 
#define  R_AARCH64_LDST64_ABS_LO12_NC 153 
#define  R_AARCH64_LDST8_ABS_LO12_NC 152 
#define  R_AARCH64_LD_PREL_LO19 151 
#define  R_AARCH64_MOVW_PREL_G0 150 
#define  R_AARCH64_MOVW_PREL_G0_NC 149 
#define  R_AARCH64_MOVW_PREL_G1 148 
#define  R_AARCH64_MOVW_PREL_G1_NC 147 
#define  R_AARCH64_MOVW_PREL_G2 146 
#define  R_AARCH64_MOVW_PREL_G2_NC 145 
#define  R_AARCH64_MOVW_PREL_G3 144 
#define  R_AARCH64_MOVW_SABS_G0 143 
#define  R_AARCH64_MOVW_SABS_G1 142 
#define  R_AARCH64_MOVW_SABS_G2 141 
#define  R_AARCH64_MOVW_UABS_G0 140 
#define  R_AARCH64_MOVW_UABS_G0_NC 139 
#define  R_AARCH64_MOVW_UABS_G1 138 
#define  R_AARCH64_MOVW_UABS_G1_NC 137 
#define  R_AARCH64_MOVW_UABS_G2 136 
#define  R_AARCH64_MOVW_UABS_G2_NC 135 
#define  R_AARCH64_MOVW_UABS_G3 134 
#define  R_AARCH64_NONE 133 
#define  R_AARCH64_PREL16 132 
#define  R_AARCH64_PREL32 131 
#define  R_AARCH64_PREL64 130 
#define  R_AARCH64_TSTBR14 129 
#define  R_ARM_NONE 128 
 scalar_t__ module_emit_plt_entry (struct module*,TYPE_2__*,void*,TYPE_3__*,TYPE_1__*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int,...) ; 
 int reloc_data (int /*<<< orphan*/ ,void*,scalar_t__,int) ; 
 int reloc_insn_adrp (struct module*,TYPE_2__*,void*,scalar_t__) ; 
 int reloc_insn_imm (int /*<<< orphan*/ ,void*,scalar_t__,int,int,int /*<<< orphan*/ ) ; 
 int reloc_insn_movw (int /*<<< orphan*/ ,void*,scalar_t__,int,int /*<<< orphan*/ ) ; 

int apply_relocate_add(Elf64_Shdr *sechdrs,
		       const char *strtab,
		       unsigned int symindex,
		       unsigned int relsec,
		       struct module *me)
{
	unsigned int i;
	int ovf;
	bool overflow_check;
	Elf64_Sym *sym;
	void *loc;
	u64 val;
	Elf64_Rela *rel = (void *)sechdrs[relsec].sh_addr;

	for (i = 0; i < sechdrs[relsec].sh_size / sizeof(*rel); i++) {
		/* loc corresponds to P in the AArch64 ELF document. */
		loc = (void *)sechdrs[sechdrs[relsec].sh_info].sh_addr
			+ rel[i].r_offset;

		/* sym is the ELF symbol we're referring to. */
		sym = (Elf64_Sym *)sechdrs[symindex].sh_addr
			+ ELF64_R_SYM(rel[i].r_info);

		/* val corresponds to (S + A) in the AArch64 ELF document. */
		val = sym->st_value + rel[i].r_addend;

		/* Check for overflow by default. */
		overflow_check = true;

		/* Perform the static relocation. */
		switch (ELF64_R_TYPE(rel[i].r_info)) {
		/* Null relocations. */
		case R_ARM_NONE:
		case R_AARCH64_NONE:
			ovf = 0;
			break;

		/* Data relocations. */
		case R_AARCH64_ABS64:
			overflow_check = false;
			ovf = reloc_data(RELOC_OP_ABS, loc, val, 64);
			break;
		case R_AARCH64_ABS32:
			ovf = reloc_data(RELOC_OP_ABS, loc, val, 32);
			break;
		case R_AARCH64_ABS16:
			ovf = reloc_data(RELOC_OP_ABS, loc, val, 16);
			break;
		case R_AARCH64_PREL64:
			overflow_check = false;
			ovf = reloc_data(RELOC_OP_PREL, loc, val, 64);
			break;
		case R_AARCH64_PREL32:
			ovf = reloc_data(RELOC_OP_PREL, loc, val, 32);
			break;
		case R_AARCH64_PREL16:
			ovf = reloc_data(RELOC_OP_PREL, loc, val, 16);
			break;

		/* MOVW instruction relocations. */
		case R_AARCH64_MOVW_UABS_G0_NC:
			overflow_check = false;
			/* Fall through */
		case R_AARCH64_MOVW_UABS_G0:
			ovf = reloc_insn_movw(RELOC_OP_ABS, loc, val, 0,
					      AARCH64_INSN_IMM_MOVKZ);
			break;
		case R_AARCH64_MOVW_UABS_G1_NC:
			overflow_check = false;
			/* Fall through */
		case R_AARCH64_MOVW_UABS_G1:
			ovf = reloc_insn_movw(RELOC_OP_ABS, loc, val, 16,
					      AARCH64_INSN_IMM_MOVKZ);
			break;
		case R_AARCH64_MOVW_UABS_G2_NC:
			overflow_check = false;
			/* Fall through */
		case R_AARCH64_MOVW_UABS_G2:
			ovf = reloc_insn_movw(RELOC_OP_ABS, loc, val, 32,
					      AARCH64_INSN_IMM_MOVKZ);
			break;
		case R_AARCH64_MOVW_UABS_G3:
			/* We're using the top bits so we can't overflow. */
			overflow_check = false;
			ovf = reloc_insn_movw(RELOC_OP_ABS, loc, val, 48,
					      AARCH64_INSN_IMM_MOVKZ);
			break;
		case R_AARCH64_MOVW_SABS_G0:
			ovf = reloc_insn_movw(RELOC_OP_ABS, loc, val, 0,
					      AARCH64_INSN_IMM_MOVNZ);
			break;
		case R_AARCH64_MOVW_SABS_G1:
			ovf = reloc_insn_movw(RELOC_OP_ABS, loc, val, 16,
					      AARCH64_INSN_IMM_MOVNZ);
			break;
		case R_AARCH64_MOVW_SABS_G2:
			ovf = reloc_insn_movw(RELOC_OP_ABS, loc, val, 32,
					      AARCH64_INSN_IMM_MOVNZ);
			break;
		case R_AARCH64_MOVW_PREL_G0_NC:
			overflow_check = false;
			ovf = reloc_insn_movw(RELOC_OP_PREL, loc, val, 0,
					      AARCH64_INSN_IMM_MOVKZ);
			break;
		case R_AARCH64_MOVW_PREL_G0:
			ovf = reloc_insn_movw(RELOC_OP_PREL, loc, val, 0,
					      AARCH64_INSN_IMM_MOVNZ);
			break;
		case R_AARCH64_MOVW_PREL_G1_NC:
			overflow_check = false;
			ovf = reloc_insn_movw(RELOC_OP_PREL, loc, val, 16,
					      AARCH64_INSN_IMM_MOVKZ);
			break;
		case R_AARCH64_MOVW_PREL_G1:
			ovf = reloc_insn_movw(RELOC_OP_PREL, loc, val, 16,
					      AARCH64_INSN_IMM_MOVNZ);
			break;
		case R_AARCH64_MOVW_PREL_G2_NC:
			overflow_check = false;
			ovf = reloc_insn_movw(RELOC_OP_PREL, loc, val, 32,
					      AARCH64_INSN_IMM_MOVKZ);
			break;
		case R_AARCH64_MOVW_PREL_G2:
			ovf = reloc_insn_movw(RELOC_OP_PREL, loc, val, 32,
					      AARCH64_INSN_IMM_MOVNZ);
			break;
		case R_AARCH64_MOVW_PREL_G3:
			/* We're using the top bits so we can't overflow. */
			overflow_check = false;
			ovf = reloc_insn_movw(RELOC_OP_PREL, loc, val, 48,
					      AARCH64_INSN_IMM_MOVNZ);
			break;

		/* Immediate instruction relocations. */
		case R_AARCH64_LD_PREL_LO19:
			ovf = reloc_insn_imm(RELOC_OP_PREL, loc, val, 2, 19,
					     AARCH64_INSN_IMM_19);
			break;
		case R_AARCH64_ADR_PREL_LO21:
			ovf = reloc_insn_imm(RELOC_OP_PREL, loc, val, 0, 21,
					     AARCH64_INSN_IMM_ADR);
			break;
		case R_AARCH64_ADR_PREL_PG_HI21_NC:
			overflow_check = false;
			/* Fall through */
		case R_AARCH64_ADR_PREL_PG_HI21:
			ovf = reloc_insn_adrp(me, sechdrs, loc, val);
			if (ovf && ovf != -ERANGE)
				return ovf;
			break;
		case R_AARCH64_ADD_ABS_LO12_NC:
		case R_AARCH64_LDST8_ABS_LO12_NC:
			overflow_check = false;
			ovf = reloc_insn_imm(RELOC_OP_ABS, loc, val, 0, 12,
					     AARCH64_INSN_IMM_12);
			break;
		case R_AARCH64_LDST16_ABS_LO12_NC:
			overflow_check = false;
			ovf = reloc_insn_imm(RELOC_OP_ABS, loc, val, 1, 11,
					     AARCH64_INSN_IMM_12);
			break;
		case R_AARCH64_LDST32_ABS_LO12_NC:
			overflow_check = false;
			ovf = reloc_insn_imm(RELOC_OP_ABS, loc, val, 2, 10,
					     AARCH64_INSN_IMM_12);
			break;
		case R_AARCH64_LDST64_ABS_LO12_NC:
			overflow_check = false;
			ovf = reloc_insn_imm(RELOC_OP_ABS, loc, val, 3, 9,
					     AARCH64_INSN_IMM_12);
			break;
		case R_AARCH64_LDST128_ABS_LO12_NC:
			overflow_check = false;
			ovf = reloc_insn_imm(RELOC_OP_ABS, loc, val, 4, 8,
					     AARCH64_INSN_IMM_12);
			break;
		case R_AARCH64_TSTBR14:
			ovf = reloc_insn_imm(RELOC_OP_PREL, loc, val, 2, 14,
					     AARCH64_INSN_IMM_14);
			break;
		case R_AARCH64_CONDBR19:
			ovf = reloc_insn_imm(RELOC_OP_PREL, loc, val, 2, 19,
					     AARCH64_INSN_IMM_19);
			break;
		case R_AARCH64_JUMP26:
		case R_AARCH64_CALL26:
			ovf = reloc_insn_imm(RELOC_OP_PREL, loc, val, 2, 26,
					     AARCH64_INSN_IMM_26);

			if (IS_ENABLED(CONFIG_ARM64_MODULE_PLTS) &&
			    ovf == -ERANGE) {
				val = module_emit_plt_entry(me, sechdrs, loc, &rel[i], sym);
				if (!val)
					return -ENOEXEC;
				ovf = reloc_insn_imm(RELOC_OP_PREL, loc, val, 2,
						     26, AARCH64_INSN_IMM_26);
			}
			break;

		default:
			pr_err("module %s: unsupported RELA relocation: %llu\n",
			       me->name, ELF64_R_TYPE(rel[i].r_info));
			return -ENOEXEC;
		}

		if (overflow_check && ovf == -ERANGE)
			goto overflow;

	}

	return 0;

overflow:
	pr_err("module %s: overflow in relocation type %d val %Lx\n",
	       me->name, (int)ELF64_R_TYPE(rel[i].r_info), val);
	return -ENOEXEC;
}