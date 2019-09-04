#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int instructionCount; } ;
typedef  TYPE_2__ vm_t ;
struct TYPE_5__ {int si; int i; int b; } ;
struct src_insn {int op; int src1_reg_flags; int dst_reg_flags; TYPE_1__ arg; int /*<<< orphan*/  i_count; } ;
struct func_info {int force_emit; struct src_insn* cached_const; int /*<<< orphan*/  fpr_pos; int /*<<< orphan*/  gpr_pos; int /*<<< orphan*/  need_float_tmp; } ;
typedef  enum sparc_iname { ____Placeholder_sparc_iname } sparc_iname ;

/* Variables and functions */
 int /*<<< orphan*/  ADD ; 
 int /*<<< orphan*/  ADDI ; 
 int /*<<< orphan*/  AND ; 
 int /*<<< orphan*/  AsmCall ; 
 int BA ; 
 int BCC ; 
 int BCS ; 
 int BE ; 
 int BG ; 
 int BGE ; 
 int BGU ; 
 int BL ; 
 int BLE ; 
 int BLEU ; 
 int BNE ; 
 int /*<<< orphan*/  BlockCopy ; 
 int CALL ; 
 int /*<<< orphan*/  CallThunk ; 
 int /*<<< orphan*/  Com_Printf (char*,int,char*) ; 
 int /*<<< orphan*/  DIE (char*) ; 
 int /*<<< orphan*/  EMIT_FALSE_CONST (struct func_info* const) ; 
 int /*<<< orphan*/  ErrJump ; 
 int /*<<< orphan*/  F0 ; 
 int /*<<< orphan*/  FADD ; 
 int FBE ; 
 int FBG ; 
 int FBGE ; 
 int FBL ; 
 int FBLE ; 
 int FBNE ; 
 int /*<<< orphan*/  FCMP ; 
 int /*<<< orphan*/  FDIV ; 
 int /*<<< orphan*/  FITOS ; 
 int /*<<< orphan*/  FMUL ; 
 int /*<<< orphan*/  FNEG ; 
 int /*<<< orphan*/  FSTOI ; 
 int /*<<< orphan*/  FSUB ; 
 int G0 ; 
 int I7 ; 
 int /*<<< orphan*/  JMPL ; 
 int /*<<< orphan*/  JMPLI ; 
 int /*<<< orphan*/  L0 ; 
 int /*<<< orphan*/  LDF ; 
 int /*<<< orphan*/  LDFI ; 
 int /*<<< orphan*/  LDL ; 
 int /*<<< orphan*/  LDLI ; 
 int /*<<< orphan*/  LDUB ; 
 int /*<<< orphan*/  LDUH ; 
 int /*<<< orphan*/  LDUW ; 
 int /*<<< orphan*/  LDUWI ; 
 int /*<<< orphan*/  MAYBE_EMIT_CONST (struct func_info* const) ; 
 int /*<<< orphan*/  NOP ; 
 int O0 ; 
 int O1 ; 
 int O2 ; 
 int O3 ; 
 int O5 ; 
 int O6 ; 
 int O7 ; 
#define  OP_ADD 186 
#define  OP_ADDF 185 
#define  OP_ARG 184 
#define  OP_BAND 183 
#define  OP_BCOM 182 
#define  OP_BLOCK_COPY 181 
#define  OP_BOR 180 
#define  OP_BREAK 179 
#define  OP_BXOR 178 
#define  OP_CALL 177 
#define  OP_CONST 176 
#define  OP_CVFI 175 
#define  OP_CVIF 174 
#define  OP_DIVF 173 
#define  OP_DIVI 172 
#define  OP_DIVU 171 
#define  OP_ENTER 170 
#define  OP_EQ 169 
#define  OP_EQF 168 
#define  OP_GEF 167 
#define  OP_GEI 166 
#define  OP_GEU 165 
#define  OP_GTF 164 
#define  OP_GTI 163 
#define  OP_GTU 162 
#define  OP_IGNORE 161 
#define  OP_JUMP 160 
#define  OP_LEAVE 159 
#define  OP_LEF 158 
#define  OP_LEI 157 
#define  OP_LEU 156 
#define  OP_LOAD1 155 
#define  OP_LOAD2 154 
#define  OP_LOAD4 153 
#define  OP_LOCAL 152 
#define  OP_LSH 151 
#define  OP_LTF 150 
#define  OP_LTI 149 
#define  OP_LTU 148 
#define  OP_MODI 147 
#define  OP_MODU 146 
#define  OP_MULF 145 
#define  OP_MULI 144 
#define  OP_MULU 143 
#define  OP_NE 142 
#define  OP_NEF 141 
#define  OP_NEGF 140 
#define  OP_NEGI 139 
#define  OP_POP 138 
#define  OP_PUSH 137 
#define  OP_RSHI 136 
#define  OP_RSHU 135 
#define  OP_SEX16 134 
#define  OP_SEX8 133 
#define  OP_STORE1 132 
#define  OP_STORE2 131 
#define  OP_STORE4 130 
#define  OP_SUB 129 
#define  OP_SUBF 128 
 int /*<<< orphan*/  OR ; 
 int /*<<< orphan*/  ORI ; 
 int /*<<< orphan*/  POP_FPR (struct func_info* const) ; 
 int /*<<< orphan*/  POP_GPR (struct func_info* const) ; 
 int /*<<< orphan*/  PUSH_FPR (struct func_info* const) ; 
 int /*<<< orphan*/  PUSH_GPR (struct func_info* const) ; 
 int REG_FLAGS_FLOAT ; 
 int /*<<< orphan*/  RESTORE ; 
 int /*<<< orphan*/  RESTOREI ; 
 int /*<<< orphan*/  SAVEI ; 
 int /*<<< orphan*/  SDIV ; 
 int /*<<< orphan*/  SETHI ; 
 int /*<<< orphan*/  SIMM13_P (int) ; 
 int SL (int,int) ; 
 int /*<<< orphan*/  SLL ; 
 int /*<<< orphan*/  SLLI ; 
 int /*<<< orphan*/  SMUL ; 
 int /*<<< orphan*/  SRA ; 
 int /*<<< orphan*/  SRAI ; 
 int /*<<< orphan*/  SRL ; 
 int /*<<< orphan*/  SRLI ; 
 int /*<<< orphan*/  STB ; 
 int /*<<< orphan*/  STF ; 
 int /*<<< orphan*/  STFI ; 
 int /*<<< orphan*/  STH ; 
 int /*<<< orphan*/  STW ; 
 int /*<<< orphan*/  STWI ; 
 int /*<<< orphan*/  SUB ; 
 int /*<<< orphan*/  SUBCC ; 
 int /*<<< orphan*/  SUBCCI ; 
 int /*<<< orphan*/  SUBI ; 
 int /*<<< orphan*/  TA ; 
 int /*<<< orphan*/  UDIV ; 
 int /*<<< orphan*/  UMUL ; 
 int VM_Data_Offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRI ; 
 int /*<<< orphan*/  XNOR ; 
 int /*<<< orphan*/  XOR ; 
 int Y_REG ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  emit_jump (TYPE_2__*,struct func_info* const,int,int) ; 
 int /*<<< orphan*/  end_emit (struct func_info* const) ; 
 int fFIRST (struct func_info* const) ; 
 int fSECOND (struct func_info* const) ; 
 int /*<<< orphan*/  iPointers ; 
 int /*<<< orphan*/  in (int,...) ; 
 char** opnames ; 
 int rDATABASE ; 
 int rDATAMASK ; 
 int rFIRST (struct func_info* const) ; 
 int rPSTACK ; 
 int rSECOND (struct func_info* const) ; 
 int rTMP ; 
 int rVMDATA ; 
 int /*<<< orphan*/  start_emit (struct func_info* const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void compile_one_insn(vm_t *vm, struct func_info * const fp, struct src_insn *sp)
{
	start_emit(fp, sp->i_count);

	switch (sp->op) {
	default:
		Com_Printf("VM: Unhandled opcode 0x%02x[%s]\n",
			   sp->op,
			   opnames[sp->op] ? opnames[sp->op] : "UNKNOWN");
		DIE("Unsupported opcode");
		break;

	case OP_ENTER: {
		int stack = SL(64, 128);

		if (fp->need_float_tmp)
			stack += 16;

		in(SAVEI, O6, -stack, O6);
		if (!SIMM13_P(sp->arg.si)) {
			in(SETHI, sp->arg.i >> 10, rTMP);
			in(ORI, rTMP, sp->arg.i & 0x3ff, rTMP);
			in(SUB, rPSTACK, rTMP, rPSTACK);
		} else
			in(SUBI, rPSTACK, sp->arg.si, rPSTACK);
		break;
	}
	case OP_LEAVE:
		if (fp->cached_const && SIMM13_P(fp->cached_const->arg.si)) {
			EMIT_FALSE_CONST(fp);
			if (fp->cached_const->src1_reg_flags & REG_FLAGS_FLOAT)
				DIE("constant float in OP_LEAVE");

			if (!SIMM13_P(sp->arg.si)) {
				in(SETHI, sp->arg.i >> 10, rTMP);
				in(ORI, rTMP, sp->arg.i & 0x3ff, rTMP);
				in(ADD, rPSTACK, rTMP, rPSTACK);
			} else
				in(ADDI, rPSTACK, sp->arg.si, rPSTACK);
			in(JMPLI, I7, 8, G0);
			in(RESTOREI, G0, fp->cached_const->arg.si, O0);
			POP_GPR(fp);
		} else {
			MAYBE_EMIT_CONST(fp);
			if (!SIMM13_P(sp->arg.si)) {
				in(SETHI, sp->arg.i >> 10, rTMP);
				in(ORI, rTMP, sp->arg.i & 0x3ff, rTMP);
				in(ADD, rPSTACK, rTMP, rPSTACK);
			} else
				in(ADDI, rPSTACK, sp->arg.si, rPSTACK);
			if (sp->src1_reg_flags & REG_FLAGS_FLOAT) {
				in(STFI, O6, SL(64, 128), fFIRST(fp));
				in(LDUWI, O6, SL(64, 128), O0);
				in(JMPLI, I7, 8, G0);
				in(RESTORE, O0, G0, O0);
				POP_FPR(fp);
			} else {
				in(JMPLI, I7, 8, G0);
				in(RESTORE, rFIRST(fp), G0, O0);
				POP_GPR(fp);
			}
		}
		assert(fp->gpr_pos == L0);
		assert(fp->fpr_pos == F0);
		break;
	case OP_JUMP:
		if (fp->cached_const) {
			EMIT_FALSE_CONST(fp);
			emit_jump(vm, fp, BA, fp->cached_const->arg.i);
		} else {
			MAYBE_EMIT_CONST(fp);
			in(SETHI, vm->instructionCount >> 10, rTMP);
			in(ORI, rTMP, vm->instructionCount & 0x3ff, rTMP);
			in(SUBCC, rTMP, rFIRST(fp), G0);
			in(BLEU, +4*5);
			in(LDLI, rVMDATA, VM_Data_Offset(ErrJump), rTMP);

			in(SLLI, rFIRST(fp), 2, rFIRST(fp));
			in(LDLI, rVMDATA, VM_Data_Offset(iPointers), rTMP);
			in(LDL, rTMP, rFIRST(fp), rTMP);
			in(JMPL, rTMP, G0, G0);
			in(NOP);
		}
		POP_GPR(fp);
		break;
	case OP_CALL:
		if (fp->cached_const) {
			EMIT_FALSE_CONST(fp);
			if (fp->cached_const->arg.si >= 0) {
				emit_jump(vm, fp, CALL, fp->cached_const->arg.i);
			} else {
				in(LDLI, rVMDATA, VM_Data_Offset(CallThunk), rTMP);
				in(LDLI, rVMDATA, VM_Data_Offset(AsmCall), O3);
				in(ORI, G0, fp->cached_const->arg.si, O0);
				in(JMPL, rTMP, G0, O7);
				in(OR, G0, rPSTACK, O1);
			}
			in(OR, G0, O0, rFIRST(fp));
		} else {
			MAYBE_EMIT_CONST(fp);
			in(SUBCCI, rFIRST(fp), 0, G0);
			in(BL, +4*7);
			in(NOP);

			/* normal call */
			in(SETHI, vm->instructionCount >> 10, rTMP);
			in(ORI, rTMP, vm->instructionCount & 0x3ff, rTMP);
			in(SUBCC, rTMP, rFIRST(fp), G0);
			in(BLEU, +4*9);
			in(LDLI, rVMDATA, VM_Data_Offset(ErrJump), rTMP);
			in(LDLI, rVMDATA, VM_Data_Offset(iPointers), O5);
			in(SLLI, rFIRST(fp), 2, rFIRST(fp));
			in(LDL, O5, rFIRST(fp), rTMP);
			in(BA, +4*4);
			in(NOP);

			/* syscall */
			in(LDLI, rVMDATA, VM_Data_Offset(CallThunk), rTMP);
			in(LDLI, rVMDATA, VM_Data_Offset(AsmCall), O3);

			in(OR, G0, rFIRST(fp), O0);
			in(JMPL, rTMP, G0, O7);
			in(OR, G0, rPSTACK, O1);

			/* return value */
			in(OR, G0, O0, rFIRST(fp));
		}
		break;
	case OP_BLOCK_COPY:
		MAYBE_EMIT_CONST(fp);
		in(LDLI, rVMDATA, VM_Data_Offset(CallThunk), rTMP);
		in(LDLI, rVMDATA, VM_Data_Offset(BlockCopy), O3);
		in(OR, G0, rSECOND(fp), O0);
		in(OR, G0, rFIRST(fp), O1);
		if ((sp->arg.i & ~0x3ff) == 0) {
			in(ORI, G0, sp->arg.i & 0x3ff, O2);
		} else if ((sp->arg.i & 0x3ff) == 0) {
			in(SETHI, sp->arg.i >> 10, O2);
		} else {
			in(SETHI, sp->arg.i >> 10, O2);
			in(ORI, O2, sp->arg.i & 0x3ff, O2);
		}
		in(JMPL, rTMP, G0, O7);
		in(NOP);
		POP_GPR(fp);
		POP_GPR(fp);
		break;

	case OP_PUSH:
		MAYBE_EMIT_CONST(fp);
		if (sp->dst_reg_flags & REG_FLAGS_FLOAT)
			PUSH_FPR(fp);
		else
			PUSH_GPR(fp);
		fp->force_emit = 1;
		break;
	case OP_POP:
		MAYBE_EMIT_CONST(fp);
		if (sp->src1_reg_flags & REG_FLAGS_FLOAT)
			POP_FPR(fp);
		else
			POP_GPR(fp);
		fp->force_emit = 1;
		break;
	case OP_ARG:
		MAYBE_EMIT_CONST(fp);
		in(ADDI, rPSTACK, sp->arg.b, rTMP);
		if (sp->src1_reg_flags & REG_FLAGS_FLOAT) {
			in(STF, rDATABASE, rTMP, fFIRST(fp));
			POP_FPR(fp);
		} else {
			in(STW, rDATABASE, rTMP, rFIRST(fp));
			POP_GPR(fp);
		}
		break;
	case OP_IGNORE:
		MAYBE_EMIT_CONST(fp);
		in(NOP);
		break;
	case OP_BREAK:
		MAYBE_EMIT_CONST(fp);
		in(TA, 0x5);
		break;
	case OP_LOCAL:
		MAYBE_EMIT_CONST(fp);
		PUSH_GPR(fp);
		if (!SIMM13_P(sp->arg.i)) {
			in(SETHI, sp->arg.i >> 10, rTMP);
			in(ORI, rTMP, sp->arg.i & 0x3ff, rTMP);
			in(ADD, rPSTACK, rTMP, rFIRST(fp));
		} else
			in(ADDI, rPSTACK, sp->arg.i, rFIRST(fp));
		break;
	case OP_CONST:
		MAYBE_EMIT_CONST(fp);
		break;
	case OP_LOAD4:
		MAYBE_EMIT_CONST(fp);
		in(AND, rFIRST(fp), rDATAMASK, rFIRST(fp));
		if (sp->dst_reg_flags & REG_FLAGS_FLOAT) {
			PUSH_FPR(fp);
			in(LDF, rFIRST(fp), rDATABASE, fFIRST(fp));
			POP_GPR(fp);
		} else {
			in(LDUW, rFIRST(fp), rDATABASE, rFIRST(fp));
		}
		break;
	case OP_LOAD2:
		MAYBE_EMIT_CONST(fp);
		in(AND, rFIRST(fp), rDATAMASK, rFIRST(fp));
		in(LDUH, rFIRST(fp), rDATABASE, rFIRST(fp));
		break;
	case OP_LOAD1:
		MAYBE_EMIT_CONST(fp);
		in(AND, rFIRST(fp), rDATAMASK, rFIRST(fp));
		in(LDUB, rFIRST(fp), rDATABASE, rFIRST(fp));
		break;
	case OP_STORE4:
		MAYBE_EMIT_CONST(fp);
		if (sp->src1_reg_flags & REG_FLAGS_FLOAT) {
			in(AND, rFIRST(fp), rDATAMASK, rFIRST(fp));
			in(STF, rFIRST(fp), rDATABASE, fFIRST(fp));
			POP_FPR(fp);
		} else {
			in(AND, rSECOND(fp), rDATAMASK, rSECOND(fp));
			in(STW, rSECOND(fp), rDATABASE, rFIRST(fp));
			POP_GPR(fp);
		}
		POP_GPR(fp);
		break;
	case OP_STORE2:
		MAYBE_EMIT_CONST(fp);
		in(AND, rSECOND(fp), rDATAMASK, rSECOND(fp));
		in(STH, rSECOND(fp), rDATABASE, rFIRST(fp));
		POP_GPR(fp);
		POP_GPR(fp);
		break;
	case OP_STORE1:
		MAYBE_EMIT_CONST(fp);
		in(AND, rSECOND(fp), rDATAMASK, rSECOND(fp));
		in(STB, rSECOND(fp), rDATABASE, rFIRST(fp));
		POP_GPR(fp);
		POP_GPR(fp);
		break;
	case OP_EQ:
	case OP_NE:
	case OP_LTI:
	case OP_GEI:
	case OP_GTI:
	case OP_LEI:
	case OP_LTU:
	case OP_GEU:
	case OP_GTU:
	case OP_LEU: {
		enum sparc_iname iname = BA;

		if (fp->cached_const && SIMM13_P(fp->cached_const->arg.si)) {
			EMIT_FALSE_CONST(fp);
			in(SUBCCI, rSECOND(fp), fp->cached_const->arg.si, G0);
		} else {
			MAYBE_EMIT_CONST(fp);
			in(SUBCC, rSECOND(fp), rFIRST(fp), G0);
		}
		switch(sp->op) {
		case OP_EQ: iname = BE; break;
		case OP_NE: iname = BNE; break;
		case OP_LTI: iname = BL; break;
		case OP_GEI: iname = BGE; break;
		case OP_GTI: iname = BG; break;
		case OP_LEI: iname = BLE; break;
		case OP_LTU: iname = BCS; break;
		case OP_GEU: iname = BCC; break;
		case OP_GTU: iname = BGU; break;
		case OP_LEU: iname = BLEU; break;
		}
		emit_jump(vm, fp, iname, sp->arg.i);
		POP_GPR(fp);
		POP_GPR(fp);
		break;
	}

	case OP_SEX8:
		MAYBE_EMIT_CONST(fp);
		in(SLLI, rFIRST(fp), 24, rFIRST(fp));
		in(SRAI, rFIRST(fp), 24, rFIRST(fp));
		break;
	case OP_SEX16:
		MAYBE_EMIT_CONST(fp);
		in(SLLI, rFIRST(fp), 16, rFIRST(fp));
		in(SRAI, rFIRST(fp), 16, rFIRST(fp));
		break;
	case OP_NEGI:
		MAYBE_EMIT_CONST(fp);
		in(SUB, G0, rFIRST(fp), rFIRST(fp));
		break;
	case OP_ADD:
		if (fp->cached_const && SIMM13_P(fp->cached_const->arg.si)) {
			EMIT_FALSE_CONST(fp);
			in(ADDI, rSECOND(fp), fp->cached_const->arg.si, rSECOND(fp));
		} else {
			MAYBE_EMIT_CONST(fp);
			in(ADD, rSECOND(fp), rFIRST(fp), rSECOND(fp));
		}
		POP_GPR(fp);
		break;
	case OP_SUB:
		if (fp->cached_const && SIMM13_P(fp->cached_const->arg.si)) {
			EMIT_FALSE_CONST(fp);
			in(SUBI, rSECOND(fp), fp->cached_const->arg.si, rSECOND(fp));
		} else {
			MAYBE_EMIT_CONST(fp);
			in(SUB, rSECOND(fp), rFIRST(fp), rSECOND(fp));
		}
		POP_GPR(fp);
		break;
	case OP_DIVI:
		MAYBE_EMIT_CONST(fp);
		in(SRAI, rSECOND(fp), 31, rTMP);
		in(WRI, rTMP, 0, Y_REG);
		in(SDIV, rSECOND(fp), rFIRST(fp), rSECOND(fp));
		POP_GPR(fp);
		break;
	case OP_DIVU:
		MAYBE_EMIT_CONST(fp);
		in(WRI, G0, 0, Y_REG);
		in(UDIV, rSECOND(fp), rFIRST(fp), rSECOND(fp));
		POP_GPR(fp);
		break;
	case OP_MODI:
		MAYBE_EMIT_CONST(fp);
		in(SRAI, rSECOND(fp), 31, rTMP);
		in(WRI, rTMP, 0, Y_REG);
		in(SDIV, rSECOND(fp), rFIRST(fp), rTMP);
		in(SMUL, rTMP, rFIRST(fp), rTMP);
		in(SUB, rSECOND(fp), rTMP, rSECOND(fp));
		POP_GPR(fp);
		break;
	case OP_MODU:
		MAYBE_EMIT_CONST(fp);
		in(WRI, G0, 0, Y_REG);
		in(UDIV, rSECOND(fp), rFIRST(fp), rTMP);
		in(SMUL, rTMP, rFIRST(fp), rTMP);
		in(SUB, rSECOND(fp), rTMP, rSECOND(fp));
		POP_GPR(fp);
		break;
	case OP_MULI:
		MAYBE_EMIT_CONST(fp);
		in(SMUL, rSECOND(fp), rFIRST(fp), rSECOND(fp));
		POP_GPR(fp);
		break;
	case OP_MULU:
		MAYBE_EMIT_CONST(fp);
		in(UMUL, rSECOND(fp), rFIRST(fp), rSECOND(fp));
		POP_GPR(fp);
		break;
	case OP_BAND:
		MAYBE_EMIT_CONST(fp);
		in(AND, rSECOND(fp), rFIRST(fp), rSECOND(fp));
		POP_GPR(fp);
		break;
	case OP_BOR:
		MAYBE_EMIT_CONST(fp);
		in(OR, rSECOND(fp), rFIRST(fp), rSECOND(fp));
		POP_GPR(fp);
		break;
	case OP_BXOR:
		MAYBE_EMIT_CONST(fp);
		in(XOR, rSECOND(fp), rFIRST(fp), rSECOND(fp));
		POP_GPR(fp);
		break;
	case OP_BCOM:
		MAYBE_EMIT_CONST(fp);
		in(XNOR, rFIRST(fp), G0, rFIRST(fp));
		break;
	case OP_LSH:
		if (fp->cached_const) {
			EMIT_FALSE_CONST(fp);
			in(SLLI, rSECOND(fp), fp->cached_const->arg.si, rSECOND(fp));
		} else {
			MAYBE_EMIT_CONST(fp);
			in(SLL, rSECOND(fp), rFIRST(fp), rSECOND(fp));
		}
		POP_GPR(fp);
		break;
	case OP_RSHI:
		if (fp->cached_const) {
			EMIT_FALSE_CONST(fp);
			in(SRAI, rSECOND(fp), fp->cached_const->arg.si, rSECOND(fp));
		} else {
			MAYBE_EMIT_CONST(fp);
			in(SRA, rSECOND(fp), rFIRST(fp), rSECOND(fp));
		}
		POP_GPR(fp);
		break;
	case OP_RSHU:
		if (fp->cached_const) {
			EMIT_FALSE_CONST(fp);
			in(SRLI, rSECOND(fp), fp->cached_const->arg.si, rSECOND(fp));
		} else {
			MAYBE_EMIT_CONST(fp);
			in(SRL, rSECOND(fp), rFIRST(fp), rSECOND(fp));
		}
		POP_GPR(fp);
		break;

	case OP_NEGF:
		MAYBE_EMIT_CONST(fp);
		in(FNEG, fFIRST(fp), fFIRST(fp));
		break;
	case OP_ADDF:
		MAYBE_EMIT_CONST(fp);
		in(FADD, fSECOND(fp), fFIRST(fp), fSECOND(fp));
		POP_FPR(fp);
		break;
	case OP_SUBF:
		MAYBE_EMIT_CONST(fp);
		in(FSUB, fSECOND(fp), fFIRST(fp), fSECOND(fp));
		POP_FPR(fp);
		break;
	case OP_DIVF:
		MAYBE_EMIT_CONST(fp);
		in(FDIV, fSECOND(fp), fFIRST(fp), fSECOND(fp));
		POP_FPR(fp);
		break;
	case OP_MULF:
		MAYBE_EMIT_CONST(fp);
		in(FMUL, fSECOND(fp), fFIRST(fp), fSECOND(fp));
		POP_FPR(fp);
		break;

	case OP_EQF:
	case OP_NEF:
	case OP_LTF:
	case OP_GEF:
	case OP_GTF:
	case OP_LEF: {
		enum sparc_iname iname = FBE;

		MAYBE_EMIT_CONST(fp);
		in(FCMP, fSECOND(fp), fFIRST(fp));
		switch(sp->op) {
		case OP_EQF: iname = FBE; break;
		case OP_NEF: iname = FBNE; break;
		case OP_LTF: iname = FBL; break;
		case OP_GEF: iname = FBGE; break;
		case OP_GTF: iname = FBG; break;
		case OP_LEF: iname = FBLE; break;
		}
		emit_jump(vm, fp, iname, sp->arg.i);
		POP_FPR(fp);
		POP_FPR(fp);
		break;
	}
	case OP_CVIF:
		MAYBE_EMIT_CONST(fp);
		PUSH_FPR(fp);
		in(STWI, O6, SL(64, 128), rFIRST(fp));
		in(LDFI, O6, SL(64, 128), fFIRST(fp));
		in(FITOS, fFIRST(fp), fFIRST(fp));
		POP_GPR(fp);
		break;
	case OP_CVFI:
		MAYBE_EMIT_CONST(fp);
		PUSH_GPR(fp);
		in(FSTOI, fFIRST(fp), fFIRST(fp));
		in(STFI, O6, SL(64, 128), fFIRST(fp));
		in(LDUWI, O6, SL(64, 128), rFIRST(fp));
		POP_FPR(fp);
		break;
	}
	if (sp->op != OP_CONST) {
		fp->cached_const = NULL;
		end_emit(fp);
	} else {
		fp->cached_const = sp;
		if (sp->dst_reg_flags & REG_FLAGS_FLOAT) {
			PUSH_FPR(fp);
		} else {
			PUSH_GPR(fp);
		}
	}
	end_emit(fp);
}