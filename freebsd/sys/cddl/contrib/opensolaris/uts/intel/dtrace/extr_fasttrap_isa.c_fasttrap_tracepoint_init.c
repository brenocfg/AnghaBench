#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint_t ;
typedef  int uint8_t ;
typedef  void* uint16_t ;
struct TYPE_6__ {int /*<<< orphan*/  p_model; } ;
typedef  TYPE_1__ proc_t ;
typedef  void* int8_t ;
typedef  void* int32_t ;
struct TYPE_7__ {int ftt_size; int ftt_segment; scalar_t__ ftt_type; int ftt_code; int ftt_ripmode; int /*<<< orphan*/ * ftt_instr; int /*<<< orphan*/  ftt_modrm; void* ftt_dest; void* ftt_index; void* ftt_base; int /*<<< orphan*/  ftt_scale; } ;
typedef  TYPE_2__ fasttrap_tracepoint_t ;
typedef  int /*<<< orphan*/  fasttrap_probe_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DATAMODEL_LP64 ; 
#define  FASTTRAP_0F_JA 183 
#define  FASTTRAP_0F_JAE 182 
#define  FASTTRAP_0F_JB 181 
#define  FASTTRAP_0F_JBE 180 
#define  FASTTRAP_0F_JE 179 
#define  FASTTRAP_0F_JG 178 
#define  FASTTRAP_0F_JGE 177 
#define  FASTTRAP_0F_JL 176 
#define  FASTTRAP_0F_JLE 175 
#define  FASTTRAP_0F_JNE 174 
#define  FASTTRAP_0F_JNO 173 
#define  FASTTRAP_0F_JNP 172 
#define  FASTTRAP_0F_JNS 171 
#define  FASTTRAP_0F_JO 170 
#define  FASTTRAP_0F_JP 169 
#define  FASTTRAP_0F_JS 168 
 int FASTTRAP_2_BYTE_OP ; 
#define  FASTTRAP_CALL 167 
 int FASTTRAP_GROUP5_OP ; 
 int FASTTRAP_INSTR ; 
#define  FASTTRAP_INT 166 
#define  FASTTRAP_INT3 165 
#define  FASTTRAP_JA 164 
#define  FASTTRAP_JAE 163 
#define  FASTTRAP_JB 162 
#define  FASTTRAP_JBE 161 
#define  FASTTRAP_JCXZ 160 
#define  FASTTRAP_JE 159 
#define  FASTTRAP_JG 158 
#define  FASTTRAP_JGE 157 
#define  FASTTRAP_JL 156 
#define  FASTTRAP_JLE 155 
#define  FASTTRAP_JMP32 154 
#define  FASTTRAP_JMP8 153 
#define  FASTTRAP_JNE 152 
#define  FASTTRAP_JNO 151 
#define  FASTTRAP_JNP 150 
#define  FASTTRAP_JNS 149 
#define  FASTTRAP_JO 148 
#define  FASTTRAP_JP 147 
#define  FASTTRAP_JS 146 
#define  FASTTRAP_LOOP 145 
#define  FASTTRAP_LOOPNZ 144 
#define  FASTTRAP_LOOPZ 143 
 int FASTTRAP_MAX_INSTR_SIZE ; 
 int /*<<< orphan*/  FASTTRAP_MODRM (int,size_t,size_t) ; 
 size_t FASTTRAP_MODRM_MOD (int) ; 
 size_t FASTTRAP_MODRM_REG (int) ; 
 size_t FASTTRAP_MODRM_RM (int) ; 
#define  FASTTRAP_NOP 142 
 void* FASTTRAP_NOREG ; 
#define  FASTTRAP_PREFIX_ADDRESS 141 
#define  FASTTRAP_PREFIX_CS 140 
#define  FASTTRAP_PREFIX_DS 139 
#define  FASTTRAP_PREFIX_ES 138 
#define  FASTTRAP_PREFIX_FS 137 
#define  FASTTRAP_PREFIX_GS 136 
#define  FASTTRAP_PREFIX_LOCK 135 
#define  FASTTRAP_PREFIX_OPERAND 134 
#define  FASTTRAP_PREFIX_REP 133 
#define  FASTTRAP_PREFIX_REPNE 132 
#define  FASTTRAP_PREFIX_SS 131 
#define  FASTTRAP_PUSHL_EBP 130 
#define  FASTTRAP_RET 129 
#define  FASTTRAP_RET16 128 
 int FASTTRAP_REX_B (int) ; 
 int FASTTRAP_REX_X (int) ; 
 int FASTTRAP_RIP_1 ; 
 int FASTTRAP_RIP_2 ; 
 int FASTTRAP_RIP_X ; 
 int FASTTRAP_SEG_NONE ; 
 size_t FASTTRAP_SIB_BASE (int) ; 
 size_t FASTTRAP_SIB_INDEX (int) ; 
 int /*<<< orphan*/  FASTTRAP_SIB_SCALE (int) ; 
 void* FASTTRAP_T_CALL ; 
 scalar_t__ FASTTRAP_T_COMMON ; 
 void* FASTTRAP_T_JCC ; 
 scalar_t__ FASTTRAP_T_JCXZ ; 
 void* FASTTRAP_T_JMP ; 
 scalar_t__ FASTTRAP_T_LOOP ; 
 scalar_t__ FASTTRAP_T_NOP ; 
 scalar_t__ FASTTRAP_T_PUSHL_EBP ; 
 scalar_t__ FASTTRAP_T_RET ; 
 scalar_t__ FASTTRAP_T_RET16 ; 
 size_t MIN (size_t,scalar_t__) ; 
 uintptr_t PAGEOFFSET ; 
 scalar_t__ PAGESIZE ; 
 void* REG_RIP ; 
 int /*<<< orphan*/  bcopy (int*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bzero (int*,size_t) ; 
 int dtrace_instr_size_isa (int*,int /*<<< orphan*/ ,int*) ; 
 void** regmap ; 
 scalar_t__ uread (TYPE_1__*,int*,size_t,uintptr_t) ; 

int
fasttrap_tracepoint_init(proc_t *p, fasttrap_tracepoint_t *tp, uintptr_t pc,
    fasttrap_probe_type_t type)
{
	uint8_t instr[FASTTRAP_MAX_INSTR_SIZE + 10];
	size_t len = FASTTRAP_MAX_INSTR_SIZE;
	size_t first = MIN(len, PAGESIZE - (pc & PAGEOFFSET));
	uint_t start = 0;
	int rmindex, size;
	uint8_t seg, rex = 0;

	/*
	 * Read the instruction at the given address out of the process's
	 * address space. We don't have to worry about a debugger
	 * changing this instruction before we overwrite it with our trap
	 * instruction since P_PR_LOCK is set. Since instructions can span
	 * pages, we potentially read the instruction in two parts. If the
	 * second part fails, we just zero out that part of the instruction.
	 */
	if (uread(p, &instr[0], first, pc) != 0)
		return (-1);
	if (len > first &&
	    uread(p, &instr[first], len - first, pc + first) != 0) {
		bzero(&instr[first], len - first);
		len = first;
	}

	/*
	 * If the disassembly fails, then we have a malformed instruction.
	 */
	if ((size = dtrace_instr_size_isa(instr, p->p_model, &rmindex)) <= 0)
		return (-1);

	/*
	 * Make sure the disassembler isn't completely broken.
	 */
	ASSERT(-1 <= rmindex && rmindex < size);

	/*
	 * If the computed size is greater than the number of bytes read,
	 * then it was a malformed instruction possibly because it fell on a
	 * page boundary and the subsequent page was missing or because of
	 * some malicious user.
	 */
	if (size > len)
		return (-1);

	tp->ftt_size = (uint8_t)size;
	tp->ftt_segment = FASTTRAP_SEG_NONE;

	/*
	 * Find the start of the instruction's opcode by processing any
	 * legacy prefixes.
	 */
	for (;;) {
		seg = 0;
		switch (instr[start]) {
		case FASTTRAP_PREFIX_SS:
			seg++;
			/*FALLTHRU*/
		case FASTTRAP_PREFIX_GS:
			seg++;
			/*FALLTHRU*/
		case FASTTRAP_PREFIX_FS:
			seg++;
			/*FALLTHRU*/
		case FASTTRAP_PREFIX_ES:
			seg++;
			/*FALLTHRU*/
		case FASTTRAP_PREFIX_DS:
			seg++;
			/*FALLTHRU*/
		case FASTTRAP_PREFIX_CS:
			seg++;
			/*FALLTHRU*/
		case FASTTRAP_PREFIX_OPERAND:
		case FASTTRAP_PREFIX_ADDRESS:
		case FASTTRAP_PREFIX_LOCK:
		case FASTTRAP_PREFIX_REP:
		case FASTTRAP_PREFIX_REPNE:
			if (seg != 0) {
				/*
				 * It's illegal for an instruction to specify
				 * two segment prefixes -- give up on this
				 * illegal instruction.
				 */
				if (tp->ftt_segment != FASTTRAP_SEG_NONE)
					return (-1);

				tp->ftt_segment = seg;
			}
			start++;
			continue;
		}
		break;
	}

#ifdef __amd64
	/*
	 * Identify the REX prefix on 64-bit processes.
	 */
	if (p->p_model == DATAMODEL_LP64 && (instr[start] & 0xf0) == 0x40)
		rex = instr[start++];
#endif

	/*
	 * Now that we're pretty sure that the instruction is okay, copy the
	 * valid part to the tracepoint.
	 */
	bcopy(instr, tp->ftt_instr, FASTTRAP_MAX_INSTR_SIZE);

	tp->ftt_type = FASTTRAP_T_COMMON;
	if (instr[start] == FASTTRAP_2_BYTE_OP) {
		switch (instr[start + 1]) {
		case FASTTRAP_0F_JO:
		case FASTTRAP_0F_JNO:
		case FASTTRAP_0F_JB:
		case FASTTRAP_0F_JAE:
		case FASTTRAP_0F_JE:
		case FASTTRAP_0F_JNE:
		case FASTTRAP_0F_JBE:
		case FASTTRAP_0F_JA:
		case FASTTRAP_0F_JS:
		case FASTTRAP_0F_JNS:
		case FASTTRAP_0F_JP:
		case FASTTRAP_0F_JNP:
		case FASTTRAP_0F_JL:
		case FASTTRAP_0F_JGE:
		case FASTTRAP_0F_JLE:
		case FASTTRAP_0F_JG:
			tp->ftt_type = FASTTRAP_T_JCC;
			tp->ftt_code = (instr[start + 1] & 0x0f) | FASTTRAP_JO;
			tp->ftt_dest = pc + tp->ftt_size +
			    /* LINTED - alignment */
			    *(int32_t *)&instr[start + 2];
			break;
		}
	} else if (instr[start] == FASTTRAP_GROUP5_OP) {
		uint_t mod = FASTTRAP_MODRM_MOD(instr[start + 1]);
		uint_t reg = FASTTRAP_MODRM_REG(instr[start + 1]);
		uint_t rm = FASTTRAP_MODRM_RM(instr[start + 1]);

		if (reg == 2 || reg == 4) {
			uint_t i, sz;

			if (reg == 2)
				tp->ftt_type = FASTTRAP_T_CALL;
			else
				tp->ftt_type = FASTTRAP_T_JMP;

			if (mod == 3)
				tp->ftt_code = 2;
			else
				tp->ftt_code = 1;

			ASSERT(p->p_model == DATAMODEL_LP64 || rex == 0);

			/*
			 * See AMD x86-64 Architecture Programmer's Manual
			 * Volume 3, Section 1.2.7, Table 1-12, and
			 * Appendix A.3.1, Table A-15.
			 */
			if (mod != 3 && rm == 4) {
				uint8_t sib = instr[start + 2];
				uint_t index = FASTTRAP_SIB_INDEX(sib);
				uint_t base = FASTTRAP_SIB_BASE(sib);

				tp->ftt_scale = FASTTRAP_SIB_SCALE(sib);

				tp->ftt_index = (index == 4) ?
				    FASTTRAP_NOREG :
				    regmap[index | (FASTTRAP_REX_X(rex) << 3)];
				tp->ftt_base = (mod == 0 && base == 5) ?
				    FASTTRAP_NOREG :
				    regmap[base | (FASTTRAP_REX_B(rex) << 3)];

				i = 3;
				sz = mod == 1 ? 1 : 4;
			} else {
				/*
				 * In 64-bit mode, mod == 0 and r/m == 5
				 * denotes %rip-relative addressing; in 32-bit
				 * mode, the base register isn't used. In both
				 * modes, there is a 32-bit operand.
				 */
				if (mod == 0 && rm == 5) {
#ifdef __amd64
					if (p->p_model == DATAMODEL_LP64)
						tp->ftt_base = REG_RIP;
					else
#endif
						tp->ftt_base = FASTTRAP_NOREG;
					sz = 4;
				} else  {
					uint8_t base = rm |
					    (FASTTRAP_REX_B(rex) << 3);

					tp->ftt_base = regmap[base];
					sz = mod == 1 ? 1 : mod == 2 ? 4 : 0;
				}
				tp->ftt_index = FASTTRAP_NOREG;
				i = 2;
			}

			if (sz == 1) {
				tp->ftt_dest = *(int8_t *)&instr[start + i];
			} else if (sz == 4) {
				/* LINTED - alignment */
				tp->ftt_dest = *(int32_t *)&instr[start + i];
			} else {
				tp->ftt_dest = 0;
			}
		}
	} else {
		switch (instr[start]) {
		case FASTTRAP_RET:
			tp->ftt_type = FASTTRAP_T_RET;
			break;

		case FASTTRAP_RET16:
			tp->ftt_type = FASTTRAP_T_RET16;
			/* LINTED - alignment */
			tp->ftt_dest = *(uint16_t *)&instr[start + 1];
			break;

		case FASTTRAP_JO:
		case FASTTRAP_JNO:
		case FASTTRAP_JB:
		case FASTTRAP_JAE:
		case FASTTRAP_JE:
		case FASTTRAP_JNE:
		case FASTTRAP_JBE:
		case FASTTRAP_JA:
		case FASTTRAP_JS:
		case FASTTRAP_JNS:
		case FASTTRAP_JP:
		case FASTTRAP_JNP:
		case FASTTRAP_JL:
		case FASTTRAP_JGE:
		case FASTTRAP_JLE:
		case FASTTRAP_JG:
			tp->ftt_type = FASTTRAP_T_JCC;
			tp->ftt_code = instr[start];
			tp->ftt_dest = pc + tp->ftt_size +
			    (int8_t)instr[start + 1];
			break;

		case FASTTRAP_LOOPNZ:
		case FASTTRAP_LOOPZ:
		case FASTTRAP_LOOP:
			tp->ftt_type = FASTTRAP_T_LOOP;
			tp->ftt_code = instr[start];
			tp->ftt_dest = pc + tp->ftt_size +
			    (int8_t)instr[start + 1];
			break;

		case FASTTRAP_JCXZ:
			tp->ftt_type = FASTTRAP_T_JCXZ;
			tp->ftt_dest = pc + tp->ftt_size +
			    (int8_t)instr[start + 1];
			break;

		case FASTTRAP_CALL:
			tp->ftt_type = FASTTRAP_T_CALL;
			tp->ftt_dest = pc + tp->ftt_size +
			    /* LINTED - alignment */
			    *(int32_t *)&instr[start + 1];
			tp->ftt_code = 0;
			break;

		case FASTTRAP_JMP32:
			tp->ftt_type = FASTTRAP_T_JMP;
			tp->ftt_dest = pc + tp->ftt_size +
			    /* LINTED - alignment */
			    *(int32_t *)&instr[start + 1];
			break;
		case FASTTRAP_JMP8:
			tp->ftt_type = FASTTRAP_T_JMP;
			tp->ftt_dest = pc + tp->ftt_size +
			    (int8_t)instr[start + 1];
			break;

		case FASTTRAP_PUSHL_EBP:
			if (start == 0)
				tp->ftt_type = FASTTRAP_T_PUSHL_EBP;
			break;

		case FASTTRAP_NOP:
#ifdef __amd64
			ASSERT(p->p_model == DATAMODEL_LP64 || rex == 0);

			/*
			 * On amd64 we have to be careful not to confuse a nop
			 * (actually xchgl %eax, %eax) with an instruction using
			 * the same opcode, but that does something different
			 * (e.g. xchgl %r8d, %eax or xcghq %r8, %rax).
			 */
			if (FASTTRAP_REX_B(rex) == 0)
#endif
				tp->ftt_type = FASTTRAP_T_NOP;
			break;

		case FASTTRAP_INT3:
			/*
			 * The pid provider shares the int3 trap with debugger
			 * breakpoints so we can't instrument them.
			 */
			ASSERT(instr[start] == FASTTRAP_INSTR);
			return (-1);

		case FASTTRAP_INT:
			/*
			 * Interrupts seem like they could be traced with
			 * no negative implications, but it's possible that
			 * a thread could be redirected by the trap handling
			 * code which would eventually return to the
			 * instruction after the interrupt. If the interrupt
			 * were in our scratch space, the subsequent
			 * instruction might be overwritten before we return.
			 * Accordingly we refuse to instrument any interrupt.
			 */
			return (-1);
		}
	}

#ifdef __amd64
	if (p->p_model == DATAMODEL_LP64 && tp->ftt_type == FASTTRAP_T_COMMON) {
		/*
		 * If the process is 64-bit and the instruction type is still
		 * FASTTRAP_T_COMMON -- meaning we're going to copy it out an
		 * execute it -- we need to watch for %rip-relative
		 * addressing mode. See the portion of fasttrap_pid_probe()
		 * below where we handle tracepoints with type
		 * FASTTRAP_T_COMMON for how we emulate instructions that
		 * employ %rip-relative addressing.
		 */
		if (rmindex != -1) {
			uint_t mod = FASTTRAP_MODRM_MOD(instr[rmindex]);
			uint_t reg = FASTTRAP_MODRM_REG(instr[rmindex]);
			uint_t rm = FASTTRAP_MODRM_RM(instr[rmindex]);

			ASSERT(rmindex > start);

			if (mod == 0 && rm == 5) {
				/*
				 * We need to be sure to avoid other
				 * registers used by this instruction. While
				 * the reg field may determine the op code
				 * rather than denoting a register, assuming
				 * that it denotes a register is always safe.
				 * We leave the REX field intact and use
				 * whatever value's there for simplicity.
				 */
				if (reg != 0) {
					tp->ftt_ripmode = FASTTRAP_RIP_1 |
					    (FASTTRAP_RIP_X *
					    FASTTRAP_REX_B(rex));
					rm = 0;
				} else {
					tp->ftt_ripmode = FASTTRAP_RIP_2 |
					    (FASTTRAP_RIP_X *
					    FASTTRAP_REX_B(rex));
					rm = 1;
				}

				tp->ftt_modrm = tp->ftt_instr[rmindex];
				tp->ftt_instr[rmindex] =
				    FASTTRAP_MODRM(2, reg, rm);
			}
		}
	}
#endif

	return (0);
}