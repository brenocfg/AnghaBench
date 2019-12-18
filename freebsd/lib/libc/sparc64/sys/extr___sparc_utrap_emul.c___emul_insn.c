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
typedef  int u_long ;
typedef  int /*<<< orphan*/  u_int ;
struct utrapframe {scalar_t__ uf_pc; } ;

/* Variables and functions */
 int /*<<< orphan*/  IF_F3_OP3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IF_F3_RD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IF_F3_RS1 (int /*<<< orphan*/ ) ; 
 int IF_OP (int /*<<< orphan*/ ) ; 
#define  INS2_POPC 132 
#define  INS3_LDQF 131 
#define  INS3_STQF 130 
 int INSFPdq_RN (int /*<<< orphan*/ ) ; 
#define  IOP_LDST 129 
#define  IOP_MISC 128 
 int SIGILL ; 
 scalar_t__ __emul_f3_memop_addr (struct utrapframe*,int /*<<< orphan*/ ) ; 
 int __emul_f3_op2 (struct utrapframe*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __emul_store_reg (struct utrapframe*,int /*<<< orphan*/ ,int) ; 
 int __fpu_getreg64 (int) ; 
 int /*<<< orphan*/  __fpu_setreg64 (int,int) ; 
 int /*<<< orphan*/  flushw () ; 

int
__emul_insn(struct utrapframe *uf)
{
	u_long reg, res;
	u_long *addr;
	u_int insn;
	int sig;
	int rd;
	int i;

	sig = 0;
	insn = *(u_int *)uf->uf_pc;
	flushw();
	switch (IF_OP(insn)) {
	case IOP_MISC:
		switch (IF_F3_OP3(insn)) {
		case INS2_POPC:
			if (IF_F3_RS1(insn) != 0) {
				sig = SIGILL;
				break;
			}
			reg = __emul_f3_op2(uf, insn);
			for (i = 0; i < 64; i++)
				res += (reg >> i) & 1;
			__emul_store_reg(uf, IF_F3_RD(insn), res);
			break;
		default:
			sig = SIGILL;
			break;
		}
		break;
	case IOP_LDST:
		switch (IF_F3_OP3(insn)) {
		case INS3_LDQF:
			rd = INSFPdq_RN(IF_F3_RD(insn));
			addr = (u_long *)__emul_f3_memop_addr(uf, insn);
			__fpu_setreg64(rd, addr[0]);
			__fpu_setreg64(rd + 2, addr[1]);
			break;
		case INS3_STQF:
			rd = INSFPdq_RN(IF_F3_RD(insn));
			addr = (u_long *)__emul_f3_memop_addr(uf, insn);
			addr[0] = __fpu_getreg64(rd);
			addr[1] = __fpu_getreg64(rd + 2);
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