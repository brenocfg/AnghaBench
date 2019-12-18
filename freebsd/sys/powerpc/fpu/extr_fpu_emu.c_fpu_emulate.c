#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ i_xo; } ;
struct TYPE_3__ {scalar_t__ i_opcd; } ;
union instr {int i_int; TYPE_2__ i_x; TYPE_1__ i_any; } ;
struct trapframe {scalar_t__ srr0; } ;
struct fpu {int dummy; } ;
struct fpemu {scalar_t__ fe_cx; struct fpu* fe_fpstate; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (int,char*) ; 
#define  FAULT 130 
#define  FPE 129 
 int FPE_EX ; 
 int /*<<< orphan*/  KDB_WHY_UNSET ; 
#define  NOTFPU 128 
 scalar_t__ OPC31_TW ; 
 scalar_t__ OPC_TWI ; 
 scalar_t__ OPC_integer_31 ; 
 int SIGFPE ; 
 int SIGILL ; 
 int SIGSEGV ; 
 int SIGTRAP ; 
 scalar_t__ copyin (void*,int*,int) ; 
 int fpe_debug ; 
 int fpu_execute (struct trapframe*,struct fpemu*,union instr*) ; 
 int /*<<< orphan*/  kdb_enter (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  opc_disasm (scalar_t__,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int
fpu_emulate(struct trapframe *frame, struct fpu *fpf)
{
	union instr insn;
	struct fpemu fe;
	int sig;

	/* initialize insn.is_datasize to tell it is *not* initialized */
	fe.fe_fpstate = fpf;
	fe.fe_cx = 0;

	/* always set this (to avoid a warning) */

	if (copyin((void *) (frame->srr0), &insn.i_int, sizeof (insn.i_int))) {
#ifdef DEBUG
		printf("fpu_emulate: fault reading opcode\n");
#endif
		return SIGSEGV;
	}

	DPRINTF(FPE_EX, ("fpu_emulate: emulating insn %x at %p\n",
	    insn.i_int, (void *)frame->srr0));


	if ((insn.i_any.i_opcd == OPC_TWI) ||
	    ((insn.i_any.i_opcd == OPC_integer_31) &&
	    (insn.i_x.i_xo == OPC31_TW))) {
		/* Check for the two trap insns. */
		DPRINTF(FPE_EX, ("fpu_emulate: SIGTRAP\n"));
		return (SIGTRAP);
	}
	sig = 0;
	switch (fpu_execute(frame, &fe, &insn)) {
	case 0:
		DPRINTF(FPE_EX, ("fpu_emulate: success\n"));
		frame->srr0 += 4;
		break;

	case FPE:
		DPRINTF(FPE_EX, ("fpu_emulate: SIGFPE\n"));
		sig = SIGFPE;
		break;

	case FAULT:
		DPRINTF(FPE_EX, ("fpu_emulate: SIGSEGV\n"));
		sig = SIGSEGV;
		break;

	case NOTFPU:
	default:
		DPRINTF(FPE_EX, ("fpu_emulate: SIGILL\n"));
#ifdef DEBUG
		if (fpe_debug & FPE_EX) {
			printf("fpu_emulate:  illegal insn %x at %p:",
			insn.i_int, (void *) (frame->srr0));
			opc_disasm(frame->srr0, insn.i_int);
		}
#endif
		sig = SIGILL;
#ifdef DEBUG
		if (fpe_debug & FPE_EX)
			kdb_enter(KDB_WHY_UNSET, "illegal instruction");
#endif
		break;
	}

	return (sig);
}