#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  mode; void* R_DS; void* R_ES; void* R_IP; void* R_BH; void* R_DH; void* R_CH; void* R_AH; void* R_BL; void* R_DL; void* R_CL; void* R_AL; int /*<<< orphan*/  register_di; int /*<<< orphan*/  register_si; int /*<<< orphan*/  register_bp; int /*<<< orphan*/  register_sp; int /*<<< orphan*/  register_b; int /*<<< orphan*/  register_d; int /*<<< orphan*/  register_c; int /*<<< orphan*/  register_a; int /*<<< orphan*/  R_AX; void* R_SS; void* R_CS; } ;
struct x86emu {TYPE_1__ x86; } ;

/* Variables and functions */
 int ACCESS_FLAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLEAR_FLAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_CF ; 
 int /*<<< orphan*/  F_DF ; 
 int /*<<< orphan*/  F_IF ; 
 int /*<<< orphan*/  F_OF ; 
 int /*<<< orphan*/  F_PF ; 
 int /*<<< orphan*/  F_SF ; 
 int /*<<< orphan*/  F_ZF ; 
 int /*<<< orphan*/  SET_FLAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYSMODE_CLRMASK ; 
 int /*<<< orphan*/  SYSMODE_PREFIX_ADDR ; 
 int /*<<< orphan*/  SYSMODE_PREFIX_DATA ; 
 int /*<<< orphan*/  SYSMODE_PREFIX_REPE ; 
 int /*<<< orphan*/  SYSMODE_PREFIX_REPNE ; 
 int /*<<< orphan*/  SYSMODE_SEGOVR_CS ; 
 int /*<<< orphan*/  SYSMODE_SEGOVR_DS ; 
 int /*<<< orphan*/  SYSMODE_SEGOVR_ES ; 
 int /*<<< orphan*/  SYSMODE_SEGOVR_FS ; 
 int /*<<< orphan*/  SYSMODE_SEGOVR_GS ; 
 int /*<<< orphan*/  SYSMODE_SEGOVR_SS ; 
 int /*<<< orphan*/  aaa_word (struct x86emu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aas_word (struct x86emu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adc_byte ; 
 int /*<<< orphan*/  adc_long ; 
 int /*<<< orphan*/  adc_word ; 
 int /*<<< orphan*/  add_byte ; 
 int /*<<< orphan*/  add_long ; 
 int /*<<< orphan*/  add_word ; 
 int /*<<< orphan*/  and_byte ; 
 int /*<<< orphan*/  and_long ; 
 int /*<<< orphan*/  and_word ; 
 int /*<<< orphan*/  cmp_byte_no_return (struct x86emu*,void*,void*) ; 
 int /*<<< orphan*/  cmp_long_no_return ; 
 int /*<<< orphan*/  cmp_word_no_return ; 
 int /*<<< orphan*/  common_binop_byte_imm (struct x86emu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  common_binop_byte_r_rm (struct x86emu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  common_binop_byte_rm_r (struct x86emu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  common_binop_ns_byte_rm_r (struct x86emu*,int /*<<< orphan*/  (*) (struct x86emu*,void*,void*)) ; 
 int /*<<< orphan*/  common_binop_ns_word_long_rm_r (struct x86emu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  common_binop_word_long_imm (struct x86emu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  common_binop_word_long_r_rm (struct x86emu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  common_binop_word_long_rm_r (struct x86emu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  common_dec_word_long (struct x86emu*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  common_imul_imm (struct x86emu*,int) ; 
 int /*<<< orphan*/  common_inc_word_long (struct x86emu*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  common_jmp_near (struct x86emu*,int) ; 
 int /*<<< orphan*/  common_load_far_pointer (struct x86emu*,void**) ; 
 int /*<<< orphan*/  common_pop_word_long (struct x86emu*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  common_push_word_long (struct x86emu*,int /*<<< orphan*/ *) ; 
 void* daa_byte (struct x86emu*,void*) ; 
 void* das_byte (struct x86emu*,void*) ; 
 void* fetch_byte_imm (struct x86emu*) ; 
 int /*<<< orphan*/  ins (struct x86emu*,int) ; 
 int /*<<< orphan*/  or_byte ; 
 int /*<<< orphan*/  or_long ; 
 int /*<<< orphan*/  or_word ; 
 int /*<<< orphan*/  outs (struct x86emu*,int) ; 
 void* pop_word (struct x86emu*) ; 
 int /*<<< orphan*/  push_word (struct x86emu*,void*) ; 
 int /*<<< orphan*/  sbb_byte ; 
 int /*<<< orphan*/  sbb_long ; 
 int /*<<< orphan*/  sbb_word ; 
 int /*<<< orphan*/  sub_byte ; 
 int /*<<< orphan*/  sub_long ; 
 int /*<<< orphan*/  sub_word ; 
 int /*<<< orphan*/  test_byte (struct x86emu*,void*,void*) ; 
 int /*<<< orphan*/  test_long ; 
 int /*<<< orphan*/  test_word ; 
 int /*<<< orphan*/  x86emuOp_aad (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_aam (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_call_far_IMM (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_call_near_IMM (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_cbw (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_cmc (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_cmp_byte_AL_IMM (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_cmp_byte_R_RM (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_cmp_word_AX_IMM (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_cmp_word_R_RM (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_cmps_byte (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_cmps_word (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_cwd (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_enter (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_esc_coprocess_d8 (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_esc_coprocess_d9 (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_esc_coprocess_da (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_esc_coprocess_db (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_esc_coprocess_dc (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_esc_coprocess_dd (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_esc_coprocess_de (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_esc_coprocess_df (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_in_byte_AL_DX (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_in_byte_AL_IMM (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_in_word_AX_DX (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_in_word_AX_IMM (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_ins_word (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_int3 (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_int_IMM (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_into (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_iret (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_jcxz (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_jump_byte_IMM (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_jump_far_IMM (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_jump_near_IMM (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_jump_near_L (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_jump_near_LE (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_jump_near_NL (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_jump_near_NLE (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_lahf (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_lea_word_R_M (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_leave (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_lock (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_lods_byte (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_lods_word (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_loop (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_loope (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_loopne (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_mov_AL_M_IMM (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_mov_AX_M_IMM (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_mov_M_AL_IMM (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_mov_M_AX_IMM (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_mov_byte_RM_IMM (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_mov_byte_RM_R (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_mov_byte_R_RM (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_mov_word_AX_IMM (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_mov_word_BP_IMM (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_mov_word_BX_IMM (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_mov_word_CX_IMM (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_mov_word_DI_IMM (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_mov_word_DX_IMM (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_mov_word_RM_IMM (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_mov_word_RM_R (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_mov_word_RM_SR (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_mov_word_R_RM (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_mov_word_SI_IMM (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_mov_word_SP_IMM (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_mov_word_SR_RM (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_movs_byte (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_movs_word (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_opc80_byte_RM_IMM (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_opc81_word_RM_IMM (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_opc82_byte_RM_IMM (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_opc83_word_RM_IMM (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_opcC0_byte_RM_MEM (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_opcC1_word_RM_MEM (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_opcD0_byte_RM_1 (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_opcD1_word_RM_1 (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_opcD2_byte_RM_CL (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_opcD3_word_RM_CL (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_opcF6_byte_RM (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_opcF7_word_RM (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_opcFE_byte_RM (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_opcFF_word_RM (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_out_byte_DX_AL (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_out_byte_IMM_AL (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_out_word_DX_AX (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_out_word_IMM_AX (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_outs_word (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_pop_RM (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_pop_all (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_popf_word (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_push_all (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_push_byte_IMM (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_push_word_IMM (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_pushf_word (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_ret_far (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_ret_far_IMM (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_ret_near_IMM (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_sahf (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_scas_byte (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_scas_word (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_stos_byte (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_stos_word (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_test_AX_IMM (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_xchg_byte_RM_R (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_xchg_word_AX_BP (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_xchg_word_AX_BX (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_xchg_word_AX_CX (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_xchg_word_AX_DI (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_xchg_word_AX_DX (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_xchg_word_AX_SI (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_xchg_word_AX_SP (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_xchg_word_RM_R (struct x86emu*) ; 
 int /*<<< orphan*/  x86emuOp_xlat (struct x86emu*) ; 
 int /*<<< orphan*/  x86emu_exec_two_byte (struct x86emu*) ; 
 int /*<<< orphan*/  x86emu_halt_sys (struct x86emu*) ; 
 int /*<<< orphan*/  xor_byte ; 
 int /*<<< orphan*/  xor_long ; 
 int /*<<< orphan*/  xor_word ; 

__attribute__((used)) static void
x86emu_exec_one_byte(struct x86emu * emu)
{
	uint8_t op1;

	op1 = fetch_byte_imm(emu);

	switch (op1) {
	case 0x00:
		common_binop_byte_rm_r(emu, add_byte);
		break;
	case 0x01:
		common_binop_word_long_rm_r(emu, add_word, add_long);
		break;
	case 0x02:
		common_binop_byte_r_rm(emu, add_byte);
		break;
	case 0x03:
		common_binop_word_long_r_rm(emu, add_word, add_long);
		break;
	case 0x04:
		common_binop_byte_imm(emu, add_byte);
		break;
	case 0x05:
		common_binop_word_long_imm(emu, add_word, add_long);
		break;
	case 0x06:
		push_word(emu, emu->x86.R_ES);
		break;
	case 0x07:
		emu->x86.R_ES = pop_word(emu);
		break;

	case 0x08:
		common_binop_byte_rm_r(emu, or_byte);
		break;
	case 0x09:
		common_binop_word_long_rm_r(emu, or_word, or_long);
		break;
	case 0x0a:
		common_binop_byte_r_rm(emu, or_byte);
		break;
	case 0x0b:
		common_binop_word_long_r_rm(emu, or_word, or_long);
		break;
	case 0x0c:
		common_binop_byte_imm(emu, or_byte);
		break;
	case 0x0d:
		common_binop_word_long_imm(emu, or_word, or_long);
		break;
	case 0x0e:
		push_word(emu, emu->x86.R_CS);
		break;
	case 0x0f:
		x86emu_exec_two_byte(emu);
		break;

	case 0x10:
		common_binop_byte_rm_r(emu, adc_byte);
		break;
	case 0x11:
		common_binop_word_long_rm_r(emu, adc_word, adc_long);
		break;
	case 0x12:
		common_binop_byte_r_rm(emu, adc_byte);
		break;
	case 0x13:
		common_binop_word_long_r_rm(emu, adc_word, adc_long);
		break;
	case 0x14:
		common_binop_byte_imm(emu, adc_byte);
		break;
	case 0x15:
		common_binop_word_long_imm(emu, adc_word, adc_long);
		break;
	case 0x16:
		push_word(emu, emu->x86.R_SS);
		break;
	case 0x17:
		emu->x86.R_SS = pop_word(emu);
		break;

	case 0x18:
		common_binop_byte_rm_r(emu, sbb_byte);
		break;
	case 0x19:
		common_binop_word_long_rm_r(emu, sbb_word, sbb_long);
		break;
	case 0x1a:
		common_binop_byte_r_rm(emu, sbb_byte);
		break;
	case 0x1b:
		common_binop_word_long_r_rm(emu, sbb_word, sbb_long);
		break;
	case 0x1c:
		common_binop_byte_imm(emu, sbb_byte);
		break;
	case 0x1d:
		common_binop_word_long_imm(emu, sbb_word, sbb_long);
		break;
	case 0x1e:
		push_word(emu, emu->x86.R_DS);
		break;
	case 0x1f:
		emu->x86.R_DS = pop_word(emu);
		break;

	case 0x20:
		common_binop_byte_rm_r(emu, and_byte);
		break;
	case 0x21:
		common_binop_word_long_rm_r(emu, and_word, and_long);
		break;
	case 0x22:
		common_binop_byte_r_rm(emu, and_byte);
		break;
	case 0x23:
		common_binop_word_long_r_rm(emu, and_word, and_long);
		break;
	case 0x24:
		common_binop_byte_imm(emu, and_byte);
		break;
	case 0x25:
		common_binop_word_long_imm(emu, and_word, and_long);
		break;
	case 0x26:
		emu->x86.mode |= SYSMODE_SEGOVR_ES;
		break;
	case 0x27:
		emu->x86.R_AL = daa_byte(emu, emu->x86.R_AL);
		break;

	case 0x28:
		common_binop_byte_rm_r(emu, sub_byte);
		break;
	case 0x29:
		common_binop_word_long_rm_r(emu, sub_word, sub_long);
		break;
	case 0x2a:
		common_binop_byte_r_rm(emu, sub_byte);
		break;
	case 0x2b:
		common_binop_word_long_r_rm(emu, sub_word, sub_long);
		break;
	case 0x2c:
		common_binop_byte_imm(emu, sub_byte);
		break;
	case 0x2d:
		common_binop_word_long_imm(emu, sub_word, sub_long);
		break;
	case 0x2e:
		emu->x86.mode |= SYSMODE_SEGOVR_CS;
		break;
	case 0x2f:
		emu->x86.R_AL = das_byte(emu, emu->x86.R_AL);
		break;

	case 0x30:
		common_binop_byte_rm_r(emu, xor_byte);
		break;
	case 0x31:
		common_binop_word_long_rm_r(emu, xor_word, xor_long);
		break;
	case 0x32:
		common_binop_byte_r_rm(emu, xor_byte);
		break;
	case 0x33:
		common_binop_word_long_r_rm(emu, xor_word, xor_long);
		break;
	case 0x34:
		common_binop_byte_imm(emu, xor_byte);
		break;
	case 0x35:
		common_binop_word_long_imm(emu, xor_word, xor_long);
		break;
	case 0x36:
		emu->x86.mode |= SYSMODE_SEGOVR_SS;
		break;
	case 0x37:
		emu->x86.R_AX = aaa_word(emu, emu->x86.R_AX);
		break;

	case 0x38:
		common_binop_ns_byte_rm_r(emu, cmp_byte_no_return);
		break;
	case 0x39:
		common_binop_ns_word_long_rm_r(emu, cmp_word_no_return,
		    cmp_long_no_return);
		break;
	case 0x3a:
		x86emuOp_cmp_byte_R_RM(emu);
		break;
	case 0x3b:
		x86emuOp_cmp_word_R_RM(emu);
		break;
	case 0x3c:
		x86emuOp_cmp_byte_AL_IMM(emu);
		break;
	case 0x3d:
		x86emuOp_cmp_word_AX_IMM(emu);
		break;
	case 0x3e:
		emu->x86.mode |= SYSMODE_SEGOVR_DS;
		break;
	case 0x3f:
		emu->x86.R_AX = aas_word(emu, emu->x86.R_AX);
		break;

	case 0x40:
		common_inc_word_long(emu, &emu->x86.register_a);
		break;
	case 0x41:
		common_inc_word_long(emu, &emu->x86.register_c);
		break;
	case 0x42:
		common_inc_word_long(emu, &emu->x86.register_d);
		break;
	case 0x43:
		common_inc_word_long(emu, &emu->x86.register_b);
		break;
	case 0x44:
		common_inc_word_long(emu, &emu->x86.register_sp);
		break;
	case 0x45:
		common_inc_word_long(emu, &emu->x86.register_bp);
		break;
	case 0x46:
		common_inc_word_long(emu, &emu->x86.register_si);
		break;
	case 0x47:
		common_inc_word_long(emu, &emu->x86.register_di);
		break;

	case 0x48:
		common_dec_word_long(emu, &emu->x86.register_a);
		break;
	case 0x49:
		common_dec_word_long(emu, &emu->x86.register_c);
		break;
	case 0x4a:
		common_dec_word_long(emu, &emu->x86.register_d);
		break;
	case 0x4b:
		common_dec_word_long(emu, &emu->x86.register_b);
		break;
	case 0x4c:
		common_dec_word_long(emu, &emu->x86.register_sp);
		break;
	case 0x4d:
		common_dec_word_long(emu, &emu->x86.register_bp);
		break;
	case 0x4e:
		common_dec_word_long(emu, &emu->x86.register_si);
		break;
	case 0x4f:
		common_dec_word_long(emu, &emu->x86.register_di);
		break;

	case 0x50:
		common_push_word_long(emu, &emu->x86.register_a);
		break;
	case 0x51:
		common_push_word_long(emu, &emu->x86.register_c);
		break;
	case 0x52:
		common_push_word_long(emu, &emu->x86.register_d);
		break;
	case 0x53:
		common_push_word_long(emu, &emu->x86.register_b);
		break;
	case 0x54:
		common_push_word_long(emu, &emu->x86.register_sp);
		break;
	case 0x55:
		common_push_word_long(emu, &emu->x86.register_bp);
		break;
	case 0x56:
		common_push_word_long(emu, &emu->x86.register_si);
		break;
	case 0x57:
		common_push_word_long(emu, &emu->x86.register_di);
		break;

	case 0x58:
		common_pop_word_long(emu, &emu->x86.register_a);
		break;
	case 0x59:
		common_pop_word_long(emu, &emu->x86.register_c);
		break;
	case 0x5a:
		common_pop_word_long(emu, &emu->x86.register_d);
		break;
	case 0x5b:
		common_pop_word_long(emu, &emu->x86.register_b);
		break;
	case 0x5c:
		common_pop_word_long(emu, &emu->x86.register_sp);
		break;
	case 0x5d:
		common_pop_word_long(emu, &emu->x86.register_bp);
		break;
	case 0x5e:
		common_pop_word_long(emu, &emu->x86.register_si);
		break;
	case 0x5f:
		common_pop_word_long(emu, &emu->x86.register_di);
		break;

	case 0x60:
		x86emuOp_push_all(emu);
		break;
	case 0x61:
		x86emuOp_pop_all(emu);
		break;
	/* 0x62 bound */
	/* 0x63 arpl */
	case 0x64:
		emu->x86.mode |= SYSMODE_SEGOVR_FS;
		break;
	case 0x65:
		emu->x86.mode |= SYSMODE_SEGOVR_GS;
		break;
	case 0x66:
		emu->x86.mode |= SYSMODE_PREFIX_DATA;
		break;
	case 0x67:
		emu->x86.mode |= SYSMODE_PREFIX_ADDR;
		break;

	case 0x68:
		x86emuOp_push_word_IMM(emu);
		break;
	case 0x69:
		common_imul_imm(emu, 0);
		break;
	case 0x6a:
		x86emuOp_push_byte_IMM(emu);
		break;
	case 0x6b:
		common_imul_imm(emu, 1);
		break;
	case 0x6c:
		ins(emu, 1);
		break;
	case 0x6d:
		x86emuOp_ins_word(emu);
		break;
	case 0x6e:
		outs(emu, 1);
		break;
	case 0x6f:
		x86emuOp_outs_word(emu);
		break;

	case 0x70:
		common_jmp_near(emu, ACCESS_FLAG(F_OF));
		break;
	case 0x71:
		common_jmp_near(emu, !ACCESS_FLAG(F_OF));
		break;
	case 0x72:
		common_jmp_near(emu, ACCESS_FLAG(F_CF));
		break;
	case 0x73:
		common_jmp_near(emu, !ACCESS_FLAG(F_CF));
		break;
	case 0x74:
		common_jmp_near(emu, ACCESS_FLAG(F_ZF));
		break;
	case 0x75:
		common_jmp_near(emu, !ACCESS_FLAG(F_ZF));
		break;
	case 0x76:
		common_jmp_near(emu, ACCESS_FLAG(F_CF) || ACCESS_FLAG(F_ZF));
		break;
	case 0x77:
		common_jmp_near(emu, !ACCESS_FLAG(F_CF) && !ACCESS_FLAG(F_ZF));
		break;

	case 0x78:
		common_jmp_near(emu, ACCESS_FLAG(F_SF));
		break;
	case 0x79:
		common_jmp_near(emu, !ACCESS_FLAG(F_SF));
		break;
	case 0x7a:
		common_jmp_near(emu, ACCESS_FLAG(F_PF));
		break;
	case 0x7b:
		common_jmp_near(emu, !ACCESS_FLAG(F_PF));
		break;
	case 0x7c:
		x86emuOp_jump_near_L(emu);
		break;
	case 0x7d:
		x86emuOp_jump_near_NL(emu);
		break;
	case 0x7e:
		x86emuOp_jump_near_LE(emu);
		break;
	case 0x7f:
		x86emuOp_jump_near_NLE(emu);
		break;

	case 0x80:
		x86emuOp_opc80_byte_RM_IMM(emu);
		break;
	case 0x81:
		x86emuOp_opc81_word_RM_IMM(emu);
		break;
	case 0x82:
		x86emuOp_opc82_byte_RM_IMM(emu);
		break;
	case 0x83:
		x86emuOp_opc83_word_RM_IMM(emu);
		break;
	case 0x84:
		common_binop_ns_byte_rm_r(emu, test_byte);
		break;
	case 0x85:
		common_binop_ns_word_long_rm_r(emu, test_word, test_long);
		break;
	case 0x86:
		x86emuOp_xchg_byte_RM_R(emu);
		break;
	case 0x87:
		x86emuOp_xchg_word_RM_R(emu);
		break;

	case 0x88:
		x86emuOp_mov_byte_RM_R(emu);
		break;
	case 0x89:
		x86emuOp_mov_word_RM_R(emu);
		break;
	case 0x8a:
		x86emuOp_mov_byte_R_RM(emu);
		break;
	case 0x8b:
		x86emuOp_mov_word_R_RM(emu);
		break;
	case 0x8c:
		x86emuOp_mov_word_RM_SR(emu);
		break;
	case 0x8d:
		x86emuOp_lea_word_R_M(emu);
		break;
	case 0x8e:
		x86emuOp_mov_word_SR_RM(emu);
		break;
	case 0x8f:
		x86emuOp_pop_RM(emu);
		break;

	case 0x90:
		/* nop */
		break;
	case 0x91:
		x86emuOp_xchg_word_AX_CX(emu);
		break;
	case 0x92:
		x86emuOp_xchg_word_AX_DX(emu);
		break;
	case 0x93:
		x86emuOp_xchg_word_AX_BX(emu);
		break;
	case 0x94:
		x86emuOp_xchg_word_AX_SP(emu);
		break;
	case 0x95:
		x86emuOp_xchg_word_AX_BP(emu);
		break;
	case 0x96:
		x86emuOp_xchg_word_AX_SI(emu);
		break;
	case 0x97:
		x86emuOp_xchg_word_AX_DI(emu);
		break;

	case 0x98:
		x86emuOp_cbw(emu);
		break;
	case 0x99:
		x86emuOp_cwd(emu);
		break;
	case 0x9a:
		x86emuOp_call_far_IMM(emu);
		break;
	case 0x9b:
		/* wait */
		break;
	case 0x9c:
		x86emuOp_pushf_word(emu);
		break;
	case 0x9d:
		x86emuOp_popf_word(emu);
		break;
	case 0x9e:
		x86emuOp_sahf(emu);
		break;
	case 0x9f:
		x86emuOp_lahf(emu);
		break;

	case 0xa0:
		x86emuOp_mov_AL_M_IMM(emu);
		break;
	case 0xa1:
		x86emuOp_mov_AX_M_IMM(emu);
		break;
	case 0xa2:
		x86emuOp_mov_M_AL_IMM(emu);
		break;
	case 0xa3:
		x86emuOp_mov_M_AX_IMM(emu);
		break;
	case 0xa4:
		x86emuOp_movs_byte(emu);
		break;
	case 0xa5:
		x86emuOp_movs_word(emu);
		break;
	case 0xa6:
		x86emuOp_cmps_byte(emu);
		break;
	case 0xa7:
		x86emuOp_cmps_word(emu);
		break;

	case 0xa8:
		test_byte(emu, emu->x86.R_AL, fetch_byte_imm(emu));
		break;
	case 0xa9:
		x86emuOp_test_AX_IMM(emu);
		break;
	case 0xaa:
		x86emuOp_stos_byte(emu);
		break;
	case 0xab:
		x86emuOp_stos_word(emu);
		break;
	case 0xac:
		x86emuOp_lods_byte(emu);
		break;
	case 0xad:
		x86emuOp_lods_word(emu);
		break;
	case 0xae:
		x86emuOp_scas_byte(emu);
		break;
	case 0xaf:
		x86emuOp_scas_word(emu);
		break;

	case 0xb0:
		emu->x86.R_AL = fetch_byte_imm(emu);
		break;
	case 0xb1:
		emu->x86.R_CL = fetch_byte_imm(emu);
		break;
	case 0xb2:
		emu->x86.R_DL = fetch_byte_imm(emu);
		break;
	case 0xb3:
		emu->x86.R_BL = fetch_byte_imm(emu);
		break;
	case 0xb4:
		emu->x86.R_AH = fetch_byte_imm(emu);
		break;
	case 0xb5:
		emu->x86.R_CH = fetch_byte_imm(emu);
		break;
	case 0xb6:
		emu->x86.R_DH = fetch_byte_imm(emu);
		break;
	case 0xb7:
		emu->x86.R_BH = fetch_byte_imm(emu);
		break;

	case 0xb8:
		x86emuOp_mov_word_AX_IMM(emu);
		break;
	case 0xb9:
		x86emuOp_mov_word_CX_IMM(emu);
		break;
	case 0xba:
		x86emuOp_mov_word_DX_IMM(emu);
		break;
	case 0xbb:
		x86emuOp_mov_word_BX_IMM(emu);
		break;
	case 0xbc:

		x86emuOp_mov_word_SP_IMM(emu);
		break;
	case 0xbd:
		x86emuOp_mov_word_BP_IMM(emu);
		break;
	case 0xbe:
		x86emuOp_mov_word_SI_IMM(emu);
		break;
	case 0xbf:
		x86emuOp_mov_word_DI_IMM(emu);
		break;

	case 0xc0:
		x86emuOp_opcC0_byte_RM_MEM(emu);
		break;
	case 0xc1:
		x86emuOp_opcC1_word_RM_MEM(emu);
		break;
	case 0xc2:
		x86emuOp_ret_near_IMM(emu);
		break;
	case 0xc3:
		emu->x86.R_IP = pop_word(emu);
		break;
	case 0xc4:
		common_load_far_pointer(emu, &emu->x86.R_ES);
		break;
	case 0xc5:
		common_load_far_pointer(emu, &emu->x86.R_DS);
		break;
	case 0xc6:
		x86emuOp_mov_byte_RM_IMM(emu);
		break;
	case 0xc7:
		x86emuOp_mov_word_RM_IMM(emu);
		break;
	case 0xc8:
		x86emuOp_enter(emu);
		break;
	case 0xc9:
		x86emuOp_leave(emu);
		break;
	case 0xca:
		x86emuOp_ret_far_IMM(emu);
		break;
	case 0xcb:
		x86emuOp_ret_far(emu);
		break;
	case 0xcc:
		x86emuOp_int3(emu);
		break;
	case 0xcd:
		x86emuOp_int_IMM(emu);
		break;
	case 0xce:
		x86emuOp_into(emu);
		break;
	case 0xcf:
		x86emuOp_iret(emu);
		break;

	case 0xd0:
		x86emuOp_opcD0_byte_RM_1(emu);
		break;
	case 0xd1:
		x86emuOp_opcD1_word_RM_1(emu);
		break;
	case 0xd2:
		x86emuOp_opcD2_byte_RM_CL(emu);
		break;
	case 0xd3:
		x86emuOp_opcD3_word_RM_CL(emu);
		break;
	case 0xd4:
		x86emuOp_aam(emu);
		break;
	case 0xd5:
		x86emuOp_aad(emu);
		break;
	/* 0xd6 Undocumented SETALC instruction */
	case 0xd7:
		x86emuOp_xlat(emu);
		break;
	case 0xd8:
		x86emuOp_esc_coprocess_d8(emu);
		break;
	case 0xd9:
		x86emuOp_esc_coprocess_d9(emu);
		break;
	case 0xda:
		x86emuOp_esc_coprocess_da(emu);
		break;
	case 0xdb:
		x86emuOp_esc_coprocess_db(emu);
		break;
	case 0xdc:
		x86emuOp_esc_coprocess_dc(emu);
		break;
	case 0xdd:
		x86emuOp_esc_coprocess_dd(emu);
		break;
	case 0xde:
		x86emuOp_esc_coprocess_de(emu);
		break;
	case 0xdf:
		x86emuOp_esc_coprocess_df(emu);
		break;

	case 0xe0:
		x86emuOp_loopne(emu);
		break;
	case 0xe1:
		x86emuOp_loope(emu);
		break;
	case 0xe2:
		x86emuOp_loop(emu);
		break;
	case 0xe3:
		x86emuOp_jcxz(emu);
		break;
	case 0xe4:
		x86emuOp_in_byte_AL_IMM(emu);
		break;
	case 0xe5:
		x86emuOp_in_word_AX_IMM(emu);
		break;
	case 0xe6:
		x86emuOp_out_byte_IMM_AL(emu);
		break;
	case 0xe7:
		x86emuOp_out_word_IMM_AX(emu);
		break;

	case 0xe8:
		x86emuOp_call_near_IMM(emu);
		break;
	case 0xe9:
		x86emuOp_jump_near_IMM(emu);
		break;
	case 0xea:
		x86emuOp_jump_far_IMM(emu);
		break;
	case 0xeb:
		x86emuOp_jump_byte_IMM(emu);
		break;
	case 0xec:
		x86emuOp_in_byte_AL_DX(emu);
		break;
	case 0xed:
		x86emuOp_in_word_AX_DX(emu);
		break;
	case 0xee:
		x86emuOp_out_byte_DX_AL(emu);
		break;
	case 0xef:
		x86emuOp_out_word_DX_AX(emu);
		break;

	case 0xf0:
		x86emuOp_lock(emu);
		break;
	case 0xf2:
		emu->x86.mode |= SYSMODE_PREFIX_REPNE;
		break;
	case 0xf3:
		emu->x86.mode |= SYSMODE_PREFIX_REPE;
		break;
	case 0xf4:
		x86emu_halt_sys(emu);
		break;
	case 0xf5:
		x86emuOp_cmc(emu);
		break;
	case 0xf6:
		x86emuOp_opcF6_byte_RM(emu);
		break;
	case 0xf7:
		x86emuOp_opcF7_word_RM(emu);
		break;

	case 0xf8:
		CLEAR_FLAG(F_CF);
		break;
	case 0xf9:
		SET_FLAG(F_CF);
		break;
	case 0xfa:
		CLEAR_FLAG(F_IF);
		break;
	case 0xfb:
		SET_FLAG(F_IF);
		break;
	case 0xfc:
		CLEAR_FLAG(F_DF);
		break;
	case 0xfd:
		SET_FLAG(F_DF);
		break;
	case 0xfe:
		x86emuOp_opcFE_byte_RM(emu);
		break;
	case 0xff:
		x86emuOp_opcFF_word_RM(emu);
		break;
	default:
		x86emu_halt_sys(emu);
		break;
	}
	if (op1 != 0x26 && op1 != 0x2e && op1 != 0x36 && op1 != 0x3e &&
	    (op1 | 3) != 0x67)
		emu->x86.mode &= ~SYSMODE_CLRMASK;
}