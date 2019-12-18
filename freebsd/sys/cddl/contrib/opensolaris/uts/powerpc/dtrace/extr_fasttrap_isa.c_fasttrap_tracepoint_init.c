#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  proc_t ;
typedef  int /*<<< orphan*/  instr ;
struct TYPE_3__ {scalar_t__ ftt_type; int ftt_instr; int ftt_dest; int /*<<< orphan*/  ftt_flags; void* ftt_bi; void* ftt_bo; } ;
typedef  TYPE_1__ fasttrap_tracepoint_t ;
typedef  int /*<<< orphan*/  fasttrap_probe_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  FASTTRAP_F_RETMAYBE ; 
 scalar_t__ FASTTRAP_T_B ; 
 scalar_t__ FASTTRAP_T_BC ; 
 void* FASTTRAP_T_BCTR ; 
 scalar_t__ FASTTRAP_T_COMMON ; 
 void* FASTTRAP_T_NOP ; 
 scalar_t__ FASTTRAP_T_RESTORE ; 
 int OP (int) ; 
 scalar_t__ OP3 (int) ; 
 scalar_t__ OP3_RETURN ; 
 int OPX (int) ; 
 void* OP_BI (int) ; 
 void* OP_BO (int) ; 
 int /*<<< orphan*/  OP_RA (int) ; 
 int /*<<< orphan*/  OP_RB (int) ; 
 int /*<<< orphan*/  OP_RS (int) ; 
 scalar_t__ uread (int /*<<< orphan*/ *,int*,int,uintptr_t) ; 

int
fasttrap_tracepoint_init(proc_t *p, fasttrap_tracepoint_t *tp, uintptr_t pc,
    fasttrap_probe_type_t type)
{
	uint32_t instr;
	//int32_t disp;

	/*
	 * Read the instruction at the given address out of the process's
	 * address space. We don't have to worry about a debugger
	 * changing this instruction before we overwrite it with our trap
	 * instruction since P_PR_LOCK is set.
	 */
	if (uread(p, &instr, 4, pc) != 0)
		return (-1);

	/*
	 * Decode the instruction to fill in the probe flags. We can have
	 * the process execute most instructions on its own using a pc/npc
	 * trick, but pc-relative control transfer present a problem since
	 * we're relocating the instruction. We emulate these instructions
	 * in the kernel. We assume a default type and over-write that as
	 * needed.
	 *
	 * pc-relative instructions must be emulated for correctness;
	 * other instructions (which represent a large set of commonly traced
	 * instructions) are emulated or otherwise optimized for performance.
	 */
	tp->ftt_type = FASTTRAP_T_COMMON;
	tp->ftt_instr = instr;

	switch (OP(instr)) {
	/* The following are invalid for trapping (invalid opcodes, tw/twi). */
	case 0:
	case 1:
	case 2:
	case 4:
	case 5:
	case 6:
	case 30:
	case 39:
	case 58:
	case 62:
	case 3:	/* twi */
		return (-1);
	case 31:	/* tw */
		if (OPX(instr) == 4)
			return (-1);
		else if (OPX(instr) == 444 && OP_RS(instr) == OP_RA(instr) &&
		    OP_RS(instr) == OP_RB(instr))
			tp->ftt_type = FASTTRAP_T_NOP;
		break;
	case 16:
		tp->ftt_type = FASTTRAP_T_BC;
		tp->ftt_dest = instr & 0x0000FFFC; /* Extract target address */
		if (instr & 0x00008000)
			tp->ftt_dest |= 0xFFFF0000;
		/* Use as offset if not absolute address. */
		if (!(instr & 0x02))
			tp->ftt_dest += pc;
		tp->ftt_bo = OP_BO(instr);
		tp->ftt_bi = OP_BI(instr);
		break;
	case 18:
		tp->ftt_type = FASTTRAP_T_B;
		tp->ftt_dest = instr & 0x03FFFFFC; /* Extract target address */
		if (instr & 0x02000000)
			tp->ftt_dest |= 0xFC000000;
		/* Use as offset if not absolute address. */
		if (!(instr & 0x02))
			tp->ftt_dest += pc;
		break;
	case 19:
		switch (OPX(instr)) {
		case 528:	/* bcctr */
			tp->ftt_type = FASTTRAP_T_BCTR;
			tp->ftt_bo = OP_BO(instr);
			tp->ftt_bi = OP_BI(instr);
			break;
		case 16:	/* bclr */
			tp->ftt_type = FASTTRAP_T_BCTR;
			tp->ftt_bo = OP_BO(instr);
			tp->ftt_bi = OP_BI(instr);
			break;
		};
		break;
	case 24:
		if (OP_RS(instr) == OP_RA(instr) &&
		    (instr & 0x0000FFFF) == 0)
			tp->ftt_type = FASTTRAP_T_NOP;
		break;
	};

	/*
	 * We don't know how this tracepoint is going to be used, but in case
	 * it's used as part of a function return probe, we need to indicate
	 * whether it's always a return site or only potentially a return
	 * site. If it's part of a return probe, it's always going to be a
	 * return from that function if it's a restore instruction or if
	 * the previous instruction was a return. If we could reliably
	 * distinguish jump tables from return sites, this wouldn't be
	 * necessary.
	 */
#if 0
	if (tp->ftt_type != FASTTRAP_T_RESTORE &&
	    (uread(p, &instr, 4, pc - sizeof (instr)) != 0 ||
	    !(OP(instr) == 2 && OP3(instr) == OP3_RETURN)))
		tp->ftt_flags |= FASTTRAP_F_RETMAYBE;
#endif

	return (0);
}