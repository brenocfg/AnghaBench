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
struct TYPE_2__ {unsigned int* slot; } ;

/* Variables and functions */
 unsigned int BR_INSTR ; 
 unsigned int HEQ_INSTR ; 
 unsigned int ILLEGAL_INSTR ; 
 unsigned int LSCSA_QW_OFFSET (unsigned int) ; 
 unsigned int NOP_INSTR ; 
 unsigned int RESTORE_COMPLETE ; 
#define  SPU_STOPPED_STATUS_H 136 
#define  SPU_STOPPED_STATUS_I 135 
#define  SPU_STOPPED_STATUS_P 134 
#define  SPU_STOPPED_STATUS_P_H 133 
#define  SPU_STOPPED_STATUS_P_I 132 
#define  SPU_STOPPED_STATUS_R 131 
#define  SPU_STOPPED_STATUS_S 130 
#define  SPU_STOPPED_STATUS_S_I 129 
#define  SPU_STOPPED_STATUS_S_P 128 
 unsigned int STOP_INSTR ; 
 TYPE_1__* regs_spill ; 
 int /*<<< orphan*/  spu_sync () ; 

__attribute__((used)) static inline void restore_complete(void)
{
	extern void exit_fini(void);
	unsigned int *exit_instrs = (unsigned int *)exit_fini;
	unsigned int offset;
	unsigned int stopped_status;
	unsigned int stopped_code;

	/* Restore, Step 18:
	 *    Issue a stop-and-signal instruction with
	 *    "good context restore" signal value.
	 *
	 * Restore, Step 19:
	 *    There may be additional instructions placed
	 *    here by the PPE Sequence for SPU Context
	 *    Restore in order to restore the correct
	 *    "stopped state".
	 *
	 *    This step is handled here by analyzing the
	 *    LSCSA.stopped_status and then modifying the
	 *    exit() function to behave appropriately.
	 */

	offset = LSCSA_QW_OFFSET(stopped_status);
	stopped_status = regs_spill[offset].slot[0];
	stopped_code = regs_spill[offset].slot[1];

	switch (stopped_status) {
	case SPU_STOPPED_STATUS_P_I:
		/* SPU_Status[P,I]=1.  Add illegal instruction
		 * followed by stop-and-signal instruction after
		 * end of restore code.
		 */
		exit_instrs[0] = RESTORE_COMPLETE;
		exit_instrs[1] = ILLEGAL_INSTR;
		exit_instrs[2] = STOP_INSTR | stopped_code;
		break;
	case SPU_STOPPED_STATUS_P_H:
		/* SPU_Status[P,H]=1.  Add 'heq $0, $0' followed
		 * by stop-and-signal instruction after end of
		 * restore code.
		 */
		exit_instrs[0] = RESTORE_COMPLETE;
		exit_instrs[1] = HEQ_INSTR;
		exit_instrs[2] = STOP_INSTR | stopped_code;
		break;
	case SPU_STOPPED_STATUS_S_P:
		/* SPU_Status[S,P]=1.  Add nop instruction
		 * followed by 'br -4' after end of restore
		 * code.
		 */
		exit_instrs[0] = RESTORE_COMPLETE;
		exit_instrs[1] = STOP_INSTR | stopped_code;
		exit_instrs[2] = NOP_INSTR;
		exit_instrs[3] = BR_INSTR;
		break;
	case SPU_STOPPED_STATUS_S_I:
		/* SPU_Status[S,I]=1.  Add  illegal instruction
		 * followed by 'br -4' after end of restore code.
		 */
		exit_instrs[0] = RESTORE_COMPLETE;
		exit_instrs[1] = ILLEGAL_INSTR;
		exit_instrs[2] = NOP_INSTR;
		exit_instrs[3] = BR_INSTR;
		break;
	case SPU_STOPPED_STATUS_I:
		/* SPU_Status[I]=1. Add illegal instruction followed
		 * by infinite loop after end of restore sequence.
		 */
		exit_instrs[0] = RESTORE_COMPLETE;
		exit_instrs[1] = ILLEGAL_INSTR;
		exit_instrs[2] = NOP_INSTR;
		exit_instrs[3] = BR_INSTR;
		break;
	case SPU_STOPPED_STATUS_S:
		/* SPU_Status[S]=1. Add two 'nop' instructions. */
		exit_instrs[0] = RESTORE_COMPLETE;
		exit_instrs[1] = NOP_INSTR;
		exit_instrs[2] = NOP_INSTR;
		exit_instrs[3] = BR_INSTR;
		break;
	case SPU_STOPPED_STATUS_H:
		/* SPU_Status[H]=1. Add 'heq $0, $0' instruction
		 * after end of restore code.
		 */
		exit_instrs[0] = RESTORE_COMPLETE;
		exit_instrs[1] = HEQ_INSTR;
		exit_instrs[2] = NOP_INSTR;
		exit_instrs[3] = BR_INSTR;
		break;
	case SPU_STOPPED_STATUS_P:
		/* SPU_Status[P]=1. Add stop-and-signal instruction
		 * after end of restore code.
		 */
		exit_instrs[0] = RESTORE_COMPLETE;
		exit_instrs[1] = STOP_INSTR | stopped_code;
		break;
	case SPU_STOPPED_STATUS_R:
		/* SPU_Status[I,S,H,P,R]=0. Add infinite loop. */
		exit_instrs[0] = RESTORE_COMPLETE;
		exit_instrs[1] = NOP_INSTR;
		exit_instrs[2] = NOP_INSTR;
		exit_instrs[3] = BR_INSTR;
		break;
	default:
		/* SPU_Status[R]=1. No additional instructions. */
		break;
	}
	spu_sync();
}