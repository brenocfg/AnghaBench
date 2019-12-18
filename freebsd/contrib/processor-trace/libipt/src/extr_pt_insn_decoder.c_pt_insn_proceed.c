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
typedef  scalar_t__ uint64_t ;
struct TYPE_3__ {scalar_t__ displacement; scalar_t__ is_direct; } ;
struct TYPE_4__ {TYPE_1__ branch; } ;
struct pt_insn_ext {TYPE_2__ variant; } ;
struct pt_insn_decoder {int status; int /*<<< orphan*/  ip; int /*<<< orphan*/  retstack; } ;
struct pt_insn {int iclass; scalar_t__ size; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int pt_insn_cond_branch (struct pt_insn_decoder*,int*) ; 
 int pt_insn_indirect_branch (struct pt_insn_decoder*,int /*<<< orphan*/ *) ; 
 int pt_retstack_pop (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pt_retstack_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pte_bad_insn ; 
 int pte_bad_retcomp ; 
 int pte_internal ; 
 int pte_noip ; 
#define  ptic_call 137 
#define  ptic_cond_jump 136 
#define  ptic_error 135 
#define  ptic_far_call 134 
#define  ptic_far_jump 133 
#define  ptic_far_return 132 
#define  ptic_jump 131 
#define  ptic_other 130 
#define  ptic_ptwrite 129 
#define  ptic_return 128 
 int pts_ip_suppressed ; 

__attribute__((used)) static int pt_insn_proceed(struct pt_insn_decoder *decoder,
			   const struct pt_insn *insn,
			   const struct pt_insn_ext *iext)
{
	if (!decoder || !insn || !iext)
		return -pte_internal;

	/* Branch displacements apply to the next instruction. */
	decoder->ip += insn->size;

	/* We handle non-branches, non-taken conditional branches, and
	 * compressed returns directly in the switch and do some pre-work for
	 * calls.
	 *
	 * All kinds of branches are handled below the switch.
	 */
	switch (insn->iclass) {
	case ptic_ptwrite:
	case ptic_other:
		return 0;

	case ptic_cond_jump: {
		int status, taken;

		status = pt_insn_cond_branch(decoder, &taken);
		if (status < 0)
			return status;

		decoder->status = status;
		if (!taken)
			return 0;

		break;
	}

	case ptic_call:
		/* Log the call for return compression.
		 *
		 * Unless this is a call to the next instruction as is used
		 * for position independent code.
		 */
		if (iext->variant.branch.displacement ||
		    !iext->variant.branch.is_direct)
			pt_retstack_push(&decoder->retstack, decoder->ip);

		break;

	case ptic_return: {
		int taken, status;

		/* Check for a compressed return. */
		status = pt_insn_cond_branch(decoder, &taken);
		if (status >= 0) {
			decoder->status = status;

			/* A compressed return is indicated by a taken
			 * conditional branch.
			 */
			if (!taken)
				return -pte_bad_retcomp;

			return pt_retstack_pop(&decoder->retstack,
					       &decoder->ip);
		}

		break;
	}

	case ptic_jump:
	case ptic_far_call:
	case ptic_far_return:
	case ptic_far_jump:
		break;

	case ptic_error:
		return -pte_bad_insn;
	}

	/* Process a direct or indirect branch.
	 *
	 * This combines calls, uncompressed returns, taken conditional jumps,
	 * and all flavors of far transfers.
	 */
	if (iext->variant.branch.is_direct)
		decoder->ip += (uint64_t) (int64_t)
			iext->variant.branch.displacement;
	else {
		int status;

		status = pt_insn_indirect_branch(decoder, &decoder->ip);

		if (status < 0)
			return status;

		decoder->status = status;

		/* We do need an IP to proceed. */
		if (status & pts_ip_suppressed)
			return -pte_noip;
	}

	return 0;
}