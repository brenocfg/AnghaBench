#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_13__ ;
typedef  struct TYPE_16__   TYPE_12__ ;
typedef  struct TYPE_15__   TYPE_11__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct TYPE_17__ {int cc; int rt; size_t fmt; int cond; int /*<<< orphan*/  fs; } ;
struct TYPE_16__ {int fmt; int ft; int fd; int func; int /*<<< orphan*/  fs; void* opcode; } ;
struct TYPE_15__ {int op; int rt; int /*<<< orphan*/  func; int /*<<< orphan*/  fd; int /*<<< orphan*/  fs; void* opcode; } ;
struct TYPE_14__ {int op; size_t fmt; int rt; int /*<<< orphan*/  fs; } ;
struct TYPE_26__ {size_t fmt; int rt; int /*<<< orphan*/  fs; } ;
struct TYPE_25__ {int rt; int rd; int func; int /*<<< orphan*/  re; int /*<<< orphan*/  rs; void* opcode; } ;
struct TYPE_24__ {int func; size_t fmt; int ft; int fd; int /*<<< orphan*/  fs; int /*<<< orphan*/  op; } ;
struct TYPE_23__ {size_t fmt; int cc; int fd; int /*<<< orphan*/  fs; int /*<<< orphan*/  op; } ;
struct TYPE_22__ {int op; int index; int /*<<< orphan*/  fd; int /*<<< orphan*/  base; } ;
struct TYPE_21__ {int func; int /*<<< orphan*/  fd; int /*<<< orphan*/  fs; int /*<<< orphan*/  ft; int /*<<< orphan*/  fr; void* opcode; } ;
struct TYPE_20__ {int /*<<< orphan*/  fd; int /*<<< orphan*/  fs; int /*<<< orphan*/  ft; int /*<<< orphan*/  fr; } ;
struct TYPE_19__ {int opcode; int /*<<< orphan*/  rt; int /*<<< orphan*/  rs; } ;
struct TYPE_18__ {int flag; int /*<<< orphan*/  bc; void* opcode; } ;
union mips_instruction {TYPE_13__ mm_fp4_format; TYPE_12__ fp0_format; TYPE_11__ fp1_format; TYPE_10__ mm_fp1_format; TYPE_9__ mm_fp3_format; TYPE_8__ r_format; TYPE_7__ mm_fp0_format; TYPE_6__ mm_fp2_format; TYPE_5__ mm_fp5_format; TYPE_4__ fp6_format; TYPE_3__ mm_fp6_format; TYPE_2__ mm_i_format; TYPE_1__ fb_format; } ;

/* Variables and functions */
 int MM_MIPS32_COND_FC ; 
 int SIGILL ; 
 int /*<<< orphan*/  bc_op ; 
 int cfc_op ; 
 void* cop1_op ; 
 void* cop1x_op ; 
 int ctc_op ; 
 int* dwl_format ; 
 int fabs_op ; 
 int fadd_op ; 
 int fceil_op ; 
 int fceill_op ; 
 int fcvtd_op ; 
 int fcvtl_op ; 
 int fcvts_op ; 
 int fcvtw_op ; 
 int fdiv_op ; 
 int ffloor_op ; 
 int ffloorl_op ; 
 int fmov_op ; 
 int fmovc_op ; 
 int fmovn_op ; 
 int fmovz_op ; 
 int fmul_op ; 
 int fneg_op ; 
 int frecip_op ; 
 int fround_op ; 
 int froundl_op ; 
 int frsqrt_op ; 
 int fsqrt_op ; 
 int fsub_op ; 
 int ftrunc_op ; 
 int ftruncl_op ; 
 int ldc1_op ; 
 int ldxc1_op ; 
 int lwc1_op ; 
 int lwxc1_op ; 
 int madd_d_op ; 
 int madd_s_op ; 
 int mfc_op ; 
 int mfhc_op ; 
#define  mm_32f_01_op 180 
#define  mm_32f_02_op 179 
#define  mm_32f_10_op 178 
#define  mm_32f_11_op 177 
#define  mm_32f_12_op 176 
#define  mm_32f_40_op 175 
#define  mm_32f_41_op 174 
#define  mm_32f_42_op 173 
#define  mm_32f_51_op 172 
#define  mm_32f_52_op 171 
#define  mm_32f_60_op 170 
#define  mm_32f_70_op 169 
#define  mm_32f_73_op 168 
#define  mm_32f_74_op 167 
 int /*<<< orphan*/  mm_bc1f_op ; 
 int /*<<< orphan*/  mm_bc1t_op ; 
#define  mm_cfc1_op 166 
#define  mm_ctc1_op 165 
#define  mm_fabs0_op 164 
#define  mm_fabs1_op 163 
 int /*<<< orphan*/  mm_fadd_op ; 
#define  mm_fceill_op 162 
#define  mm_fceilw_op 161 
#define  mm_fcvtd0_op 160 
#define  mm_fcvtd1_op 159 
#define  mm_fcvtl_op 158 
#define  mm_fcvts0_op 157 
#define  mm_fcvts1_op 156 
#define  mm_fcvtw_op 155 
 int /*<<< orphan*/  mm_fdiv_op ; 
#define  mm_ffloorl_op 154 
#define  mm_ffloorw_op 153 
#define  mm_fmov0_op 152 
#define  mm_fmov1_op 151 
 int /*<<< orphan*/  mm_fmovf_op ; 
 int /*<<< orphan*/  mm_fmovn_op ; 
 int /*<<< orphan*/  mm_fmovt_op ; 
 int /*<<< orphan*/  mm_fmovz_op ; 
 int /*<<< orphan*/  mm_fmul_op ; 
#define  mm_fneg0_op 150 
#define  mm_fneg1_op 149 
#define  mm_frecip_op 148 
#define  mm_froundl_op 147 
#define  mm_froundw_op 146 
#define  mm_frsqrt_op 145 
#define  mm_fsqrt_op 144 
 int /*<<< orphan*/  mm_fsub_op ; 
#define  mm_ftruncl_op 143 
#define  mm_ftruncw_op 142 
#define  mm_ldc132_op 141 
 int mm_ldxc1_op ; 
#define  mm_lwc132_op 140 
 int mm_lwxc1_op ; 
#define  mm_mfc1_op 139 
#define  mm_mfhc1_op 138 
#define  mm_movf0_op 137 
#define  mm_movf1_op 136 
#define  mm_movt0_op 135 
#define  mm_movt1_op 134 
#define  mm_mtc1_op 133 
#define  mm_mthc1_op 132 
#define  mm_pool32f_op 131 
#define  mm_pool32i_op 130 
#define  mm_sdc132_op 129 
 int mm_sdxc1_op ; 
#define  mm_swc132_op 128 
 int mm_swxc1_op ; 
 int movc_op ; 
 int msub_d_op ; 
 int msub_s_op ; 
 int mtc_op ; 
 int mthc_op ; 
 int nmadd_d_op ; 
 int nmadd_s_op ; 
 int nmsub_d_op ; 
 int nmsub_s_op ; 
 int* sd_format ; 
 int sdc1_op ; 
 void** sdps_format ; 
 int sdxc1_op ; 
 void* spec_op ; 
 int swc1_op ; 
 int* swl_format ; 
 int swxc1_op ; 

__attribute__((used)) static int microMIPS32_to_MIPS32(union mips_instruction *insn_ptr)
{
	union mips_instruction insn = *insn_ptr;
	union mips_instruction mips32_insn = insn;
	int func, fmt, op;

	switch (insn.mm_i_format.opcode) {
	case mm_ldc132_op:
		mips32_insn.mm_i_format.opcode = ldc1_op;
		mips32_insn.mm_i_format.rt = insn.mm_i_format.rs;
		mips32_insn.mm_i_format.rs = insn.mm_i_format.rt;
		break;
	case mm_lwc132_op:
		mips32_insn.mm_i_format.opcode = lwc1_op;
		mips32_insn.mm_i_format.rt = insn.mm_i_format.rs;
		mips32_insn.mm_i_format.rs = insn.mm_i_format.rt;
		break;
	case mm_sdc132_op:
		mips32_insn.mm_i_format.opcode = sdc1_op;
		mips32_insn.mm_i_format.rt = insn.mm_i_format.rs;
		mips32_insn.mm_i_format.rs = insn.mm_i_format.rt;
		break;
	case mm_swc132_op:
		mips32_insn.mm_i_format.opcode = swc1_op;
		mips32_insn.mm_i_format.rt = insn.mm_i_format.rs;
		mips32_insn.mm_i_format.rs = insn.mm_i_format.rt;
		break;
	case mm_pool32i_op:
		/* NOTE: offset is << by 1 if in microMIPS mode. */
		if ((insn.mm_i_format.rt == mm_bc1f_op) ||
		    (insn.mm_i_format.rt == mm_bc1t_op)) {
			mips32_insn.fb_format.opcode = cop1_op;
			mips32_insn.fb_format.bc = bc_op;
			mips32_insn.fb_format.flag =
				(insn.mm_i_format.rt == mm_bc1t_op) ? 1 : 0;
		} else
			return SIGILL;
		break;
	case mm_pool32f_op:
		switch (insn.mm_fp0_format.func) {
		case mm_32f_01_op:
		case mm_32f_11_op:
		case mm_32f_02_op:
		case mm_32f_12_op:
		case mm_32f_41_op:
		case mm_32f_51_op:
		case mm_32f_42_op:
		case mm_32f_52_op:
			op = insn.mm_fp0_format.func;
			if (op == mm_32f_01_op)
				func = madd_s_op;
			else if (op == mm_32f_11_op)
				func = madd_d_op;
			else if (op == mm_32f_02_op)
				func = nmadd_s_op;
			else if (op == mm_32f_12_op)
				func = nmadd_d_op;
			else if (op == mm_32f_41_op)
				func = msub_s_op;
			else if (op == mm_32f_51_op)
				func = msub_d_op;
			else if (op == mm_32f_42_op)
				func = nmsub_s_op;
			else
				func = nmsub_d_op;
			mips32_insn.fp6_format.opcode = cop1x_op;
			mips32_insn.fp6_format.fr = insn.mm_fp6_format.fr;
			mips32_insn.fp6_format.ft = insn.mm_fp6_format.ft;
			mips32_insn.fp6_format.fs = insn.mm_fp6_format.fs;
			mips32_insn.fp6_format.fd = insn.mm_fp6_format.fd;
			mips32_insn.fp6_format.func = func;
			break;
		case mm_32f_10_op:
			func = -1;	/* Invalid */
			op = insn.mm_fp5_format.op & 0x7;
			if (op == mm_ldxc1_op)
				func = ldxc1_op;
			else if (op == mm_sdxc1_op)
				func = sdxc1_op;
			else if (op == mm_lwxc1_op)
				func = lwxc1_op;
			else if (op == mm_swxc1_op)
				func = swxc1_op;

			if (func != -1) {
				mips32_insn.r_format.opcode = cop1x_op;
				mips32_insn.r_format.rs =
					insn.mm_fp5_format.base;
				mips32_insn.r_format.rt =
					insn.mm_fp5_format.index;
				mips32_insn.r_format.rd = 0;
				mips32_insn.r_format.re = insn.mm_fp5_format.fd;
				mips32_insn.r_format.func = func;
			} else
				return SIGILL;
			break;
		case mm_32f_40_op:
			op = -1;	/* Invalid */
			if (insn.mm_fp2_format.op == mm_fmovt_op)
				op = 1;
			else if (insn.mm_fp2_format.op == mm_fmovf_op)
				op = 0;
			if (op != -1) {
				mips32_insn.fp0_format.opcode = cop1_op;
				mips32_insn.fp0_format.fmt =
					sdps_format[insn.mm_fp2_format.fmt];
				mips32_insn.fp0_format.ft =
					(insn.mm_fp2_format.cc<<2) + op;
				mips32_insn.fp0_format.fs =
					insn.mm_fp2_format.fs;
				mips32_insn.fp0_format.fd =
					insn.mm_fp2_format.fd;
				mips32_insn.fp0_format.func = fmovc_op;
			} else
				return SIGILL;
			break;
		case mm_32f_60_op:
			func = -1;	/* Invalid */
			if (insn.mm_fp0_format.op == mm_fadd_op)
				func = fadd_op;
			else if (insn.mm_fp0_format.op == mm_fsub_op)
				func = fsub_op;
			else if (insn.mm_fp0_format.op == mm_fmul_op)
				func = fmul_op;
			else if (insn.mm_fp0_format.op == mm_fdiv_op)
				func = fdiv_op;
			if (func != -1) {
				mips32_insn.fp0_format.opcode = cop1_op;
				mips32_insn.fp0_format.fmt =
					sdps_format[insn.mm_fp0_format.fmt];
				mips32_insn.fp0_format.ft =
					insn.mm_fp0_format.ft;
				mips32_insn.fp0_format.fs =
					insn.mm_fp0_format.fs;
				mips32_insn.fp0_format.fd =
					insn.mm_fp0_format.fd;
				mips32_insn.fp0_format.func = func;
			} else
				return SIGILL;
			break;
		case mm_32f_70_op:
			func = -1;	/* Invalid */
			if (insn.mm_fp0_format.op == mm_fmovn_op)
				func = fmovn_op;
			else if (insn.mm_fp0_format.op == mm_fmovz_op)
				func = fmovz_op;
			if (func != -1) {
				mips32_insn.fp0_format.opcode = cop1_op;
				mips32_insn.fp0_format.fmt =
					sdps_format[insn.mm_fp0_format.fmt];
				mips32_insn.fp0_format.ft =
					insn.mm_fp0_format.ft;
				mips32_insn.fp0_format.fs =
					insn.mm_fp0_format.fs;
				mips32_insn.fp0_format.fd =
					insn.mm_fp0_format.fd;
				mips32_insn.fp0_format.func = func;
			} else
				return SIGILL;
			break;
		case mm_32f_73_op:    /* POOL32FXF */
			switch (insn.mm_fp1_format.op) {
			case mm_movf0_op:
			case mm_movf1_op:
			case mm_movt0_op:
			case mm_movt1_op:
				if ((insn.mm_fp1_format.op & 0x7f) ==
				    mm_movf0_op)
					op = 0;
				else
					op = 1;
				mips32_insn.r_format.opcode = spec_op;
				mips32_insn.r_format.rs = insn.mm_fp4_format.fs;
				mips32_insn.r_format.rt =
					(insn.mm_fp4_format.cc << 2) + op;
				mips32_insn.r_format.rd = insn.mm_fp4_format.rt;
				mips32_insn.r_format.re = 0;
				mips32_insn.r_format.func = movc_op;
				break;
			case mm_fcvtd0_op:
			case mm_fcvtd1_op:
			case mm_fcvts0_op:
			case mm_fcvts1_op:
				if ((insn.mm_fp1_format.op & 0x7f) ==
				    mm_fcvtd0_op) {
					func = fcvtd_op;
					fmt = swl_format[insn.mm_fp3_format.fmt];
				} else {
					func = fcvts_op;
					fmt = dwl_format[insn.mm_fp3_format.fmt];
				}
				mips32_insn.fp0_format.opcode = cop1_op;
				mips32_insn.fp0_format.fmt = fmt;
				mips32_insn.fp0_format.ft = 0;
				mips32_insn.fp0_format.fs =
					insn.mm_fp3_format.fs;
				mips32_insn.fp0_format.fd =
					insn.mm_fp3_format.rt;
				mips32_insn.fp0_format.func = func;
				break;
			case mm_fmov0_op:
			case mm_fmov1_op:
			case mm_fabs0_op:
			case mm_fabs1_op:
			case mm_fneg0_op:
			case mm_fneg1_op:
				if ((insn.mm_fp1_format.op & 0x7f) ==
				    mm_fmov0_op)
					func = fmov_op;
				else if ((insn.mm_fp1_format.op & 0x7f) ==
					 mm_fabs0_op)
					func = fabs_op;
				else
					func = fneg_op;
				mips32_insn.fp0_format.opcode = cop1_op;
				mips32_insn.fp0_format.fmt =
					sdps_format[insn.mm_fp3_format.fmt];
				mips32_insn.fp0_format.ft = 0;
				mips32_insn.fp0_format.fs =
					insn.mm_fp3_format.fs;
				mips32_insn.fp0_format.fd =
					insn.mm_fp3_format.rt;
				mips32_insn.fp0_format.func = func;
				break;
			case mm_ffloorl_op:
			case mm_ffloorw_op:
			case mm_fceill_op:
			case mm_fceilw_op:
			case mm_ftruncl_op:
			case mm_ftruncw_op:
			case mm_froundl_op:
			case mm_froundw_op:
			case mm_fcvtl_op:
			case mm_fcvtw_op:
				if (insn.mm_fp1_format.op == mm_ffloorl_op)
					func = ffloorl_op;
				else if (insn.mm_fp1_format.op == mm_ffloorw_op)
					func = ffloor_op;
				else if (insn.mm_fp1_format.op == mm_fceill_op)
					func = fceill_op;
				else if (insn.mm_fp1_format.op == mm_fceilw_op)
					func = fceil_op;
				else if (insn.mm_fp1_format.op == mm_ftruncl_op)
					func = ftruncl_op;
				else if (insn.mm_fp1_format.op == mm_ftruncw_op)
					func = ftrunc_op;
				else if (insn.mm_fp1_format.op == mm_froundl_op)
					func = froundl_op;
				else if (insn.mm_fp1_format.op == mm_froundw_op)
					func = fround_op;
				else if (insn.mm_fp1_format.op == mm_fcvtl_op)
					func = fcvtl_op;
				else
					func = fcvtw_op;
				mips32_insn.fp0_format.opcode = cop1_op;
				mips32_insn.fp0_format.fmt =
					sd_format[insn.mm_fp1_format.fmt];
				mips32_insn.fp0_format.ft = 0;
				mips32_insn.fp0_format.fs =
					insn.mm_fp1_format.fs;
				mips32_insn.fp0_format.fd =
					insn.mm_fp1_format.rt;
				mips32_insn.fp0_format.func = func;
				break;
			case mm_frsqrt_op:
			case mm_fsqrt_op:
			case mm_frecip_op:
				if (insn.mm_fp1_format.op == mm_frsqrt_op)
					func = frsqrt_op;
				else if (insn.mm_fp1_format.op == mm_fsqrt_op)
					func = fsqrt_op;
				else
					func = frecip_op;
				mips32_insn.fp0_format.opcode = cop1_op;
				mips32_insn.fp0_format.fmt =
					sdps_format[insn.mm_fp1_format.fmt];
				mips32_insn.fp0_format.ft = 0;
				mips32_insn.fp0_format.fs =
					insn.mm_fp1_format.fs;
				mips32_insn.fp0_format.fd =
					insn.mm_fp1_format.rt;
				mips32_insn.fp0_format.func = func;
				break;
			case mm_mfc1_op:
			case mm_mtc1_op:
			case mm_cfc1_op:
			case mm_ctc1_op:
			case mm_mfhc1_op:
			case mm_mthc1_op:
				if (insn.mm_fp1_format.op == mm_mfc1_op)
					op = mfc_op;
				else if (insn.mm_fp1_format.op == mm_mtc1_op)
					op = mtc_op;
				else if (insn.mm_fp1_format.op == mm_cfc1_op)
					op = cfc_op;
				else if (insn.mm_fp1_format.op == mm_ctc1_op)
					op = ctc_op;
				else if (insn.mm_fp1_format.op == mm_mfhc1_op)
					op = mfhc_op;
				else
					op = mthc_op;
				mips32_insn.fp1_format.opcode = cop1_op;
				mips32_insn.fp1_format.op = op;
				mips32_insn.fp1_format.rt =
					insn.mm_fp1_format.rt;
				mips32_insn.fp1_format.fs =
					insn.mm_fp1_format.fs;
				mips32_insn.fp1_format.fd = 0;
				mips32_insn.fp1_format.func = 0;
				break;
			default:
				return SIGILL;
			}
			break;
		case mm_32f_74_op:	/* c.cond.fmt */
			mips32_insn.fp0_format.opcode = cop1_op;
			mips32_insn.fp0_format.fmt =
				sdps_format[insn.mm_fp4_format.fmt];
			mips32_insn.fp0_format.ft = insn.mm_fp4_format.rt;
			mips32_insn.fp0_format.fs = insn.mm_fp4_format.fs;
			mips32_insn.fp0_format.fd = insn.mm_fp4_format.cc << 2;
			mips32_insn.fp0_format.func =
				insn.mm_fp4_format.cond | MM_MIPS32_COND_FC;
			break;
		default:
			return SIGILL;
		}
		break;
	default:
		return SIGILL;
	}

	*insn_ptr = mips32_insn;
	return 0;
}