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
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct utrapframe {scalar_t__ uf_pc; scalar_t__ uf_sfar; } ;

/* Variables and functions */
 int /*<<< orphan*/  IF_F3_OP3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IF_F3_RD (int /*<<< orphan*/ ) ; 
 int IF_OP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IF_SEXT (int /*<<< orphan*/ ,int) ; 
#define  INS3_LDSH 136 
#define  INS3_LDSW 135 
#define  INS3_LDUH 134 
#define  INS3_LDUW 133 
#define  INS3_LDX 132 
#define  INS3_STH 131 
#define  INS3_STW 130 
#define  INS3_STX 129 
#define  IOP_LDST 128 
 int SIGILL ; 
 int /*<<< orphan*/  __emul_fetch_reg (struct utrapframe*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __emul_store_reg (struct utrapframe*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __unaligned_load (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  __unaligned_store (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  flushw () ; 

int
__unaligned_fixup(struct utrapframe *uf)
{
	u_char *addr;
	u_long val;
	u_int insn;
	int sig;

	sig = 0;
	addr = (u_char *)uf->uf_sfar;
	insn = *(u_int *)uf->uf_pc;
	flushw();
	switch (IF_OP(insn)) {
	case IOP_LDST:
		switch (IF_F3_OP3(insn)) {
		case INS3_LDUH:
			val = __unaligned_load(addr, 2);
			__emul_store_reg(uf, IF_F3_RD(insn), val);
			break;
		case INS3_LDUW:
			val = __unaligned_load(addr, 4);
			__emul_store_reg(uf, IF_F3_RD(insn), val);
			break;
		case INS3_LDX:
			val = __unaligned_load(addr, 8);
			__emul_store_reg(uf, IF_F3_RD(insn), val);
			break;
		case INS3_LDSH:
			val = __unaligned_load(addr, 2);
			__emul_store_reg(uf, IF_F3_RD(insn),
			    IF_SEXT(val, 16));
			break;
		case INS3_LDSW:
			val = __unaligned_load(addr, 4);
			__emul_store_reg(uf, IF_F3_RD(insn),
			    IF_SEXT(val, 32));
			break;
		case INS3_STH:
			val = __emul_fetch_reg(uf, IF_F3_RD(insn));
			__unaligned_store(addr, val, 2);
			break;
		case INS3_STW:
			val = __emul_fetch_reg(uf, IF_F3_RD(insn));
			__unaligned_store(addr, val, 4);
			break;
		case INS3_STX:
			val = __emul_fetch_reg(uf, IF_F3_RD(insn));
			__unaligned_store(addr, val, 8);
			break;
		default:
			sig = SIGILL;
			break;
		}
		break;
	default:
		sig = SIGILL;
		break;
	}
	return (sig);
}