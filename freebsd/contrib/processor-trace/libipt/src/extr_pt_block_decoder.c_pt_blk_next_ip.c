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
struct TYPE_3__ {int /*<<< orphan*/  is_direct; int /*<<< orphan*/  displacement; } ;
struct TYPE_4__ {TYPE_1__ branch; } ;
struct pt_insn_ext {TYPE_2__ variant; } ;
struct pt_insn {int iclass; scalar_t__ size; scalar_t__ ip; } ;
struct pt_block_decoder {int /*<<< orphan*/  retstack; } ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int pt_blk_cond_branch (struct pt_block_decoder*,int*) ; 
 int pt_blk_indirect_branch (struct pt_block_decoder*,scalar_t__*) ; 
 int pt_retstack_pop (int /*<<< orphan*/ *,scalar_t__*) ; 
 int pte_bad_insn ; 
 int pte_bad_query ; 
 int pte_bad_retcomp ; 
 int pte_internal ; 
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

__attribute__((used)) static int pt_blk_next_ip(uint64_t *pip, struct pt_block_decoder *decoder,
			  const struct pt_insn *insn,
			  const struct pt_insn_ext *iext)
{
	int status, errcode;

	if (!pip || !decoder || !insn || !iext)
		return -pte_internal;

	/* We handle non-taken conditional branches, and compressed returns
	 * directly in the switch.
	 *
	 * All kinds of branches are handled below the switch.
	 */
	switch (insn->iclass) {
	case ptic_cond_jump: {
		uint64_t ip;
		int taken;

		status = pt_blk_cond_branch(decoder, &taken);
		if (status < 0)
			return status;

		ip = insn->ip + insn->size;
		if (taken)
			ip += (uint64_t) (int64_t)
				iext->variant.branch.displacement;

		*pip = ip;
		return status;
	}

	case ptic_return: {
		int taken;

		/* Check for a compressed return. */
		status = pt_blk_cond_branch(decoder, &taken);
		if (status < 0) {
			if (status != -pte_bad_query)
				return status;

			break;
		}

		/* A compressed return is indicated by a taken conditional
		 * branch.
		 */
		if (!taken)
			return -pte_bad_retcomp;

		errcode = pt_retstack_pop(&decoder->retstack, pip);
		if (errcode < 0)
			return errcode;

		return status;
	}

	case ptic_jump:
	case ptic_call:
		/* A direct jump or call wouldn't require trace. */
		if (iext->variant.branch.is_direct)
			return -pte_internal;

		break;

	case ptic_far_call:
	case ptic_far_return:
	case ptic_far_jump:
		break;

	case ptic_ptwrite:
	case ptic_other:
		return -pte_internal;

	case ptic_error:
		return -pte_bad_insn;
	}

	/* Process an indirect branch.
	 *
	 * This covers indirect jumps and calls, non-compressed returns, and all
	 * flavors of far transfers.
	 */
	return pt_blk_indirect_branch(decoder, pip);
}