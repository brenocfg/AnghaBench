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
struct pt_insn_ext {int dummy; } ;
struct pt_insn {int /*<<< orphan*/  ip; } ;
struct TYPE_3__ {int /*<<< orphan*/  ip; } ;
struct TYPE_4__ {TYPE_1__ ptwrite; } ;
struct pt_event {TYPE_2__ variant; scalar_t__ ip_suppressed; } ;
struct pt_block_decoder {int dummy; } ;
struct pt_block {int dummy; } ;

/* Variables and functions */
 int pt_blk_proceed_one_insn (struct pt_block_decoder*,struct pt_block*,struct pt_insn*,struct pt_insn_ext*) ; 
 int pt_blk_proceed_to_insn (struct pt_block_decoder*,struct pt_block*,struct pt_insn*,struct pt_insn_ext*,int /*<<< orphan*/ ) ; 
 int pt_blk_proceed_to_ip (struct pt_block_decoder*,struct pt_block*,struct pt_insn*,struct pt_insn_ext*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pt_insn_is_ptwrite ; 
 int pte_internal ; 

__attribute__((used)) static int pt_blk_proceed_to_ptwrite(struct pt_block_decoder *decoder,
				     struct pt_block *block,
				     struct pt_insn *insn,
				     struct pt_insn_ext *iext,
				     struct pt_event *ev)
{
	int status;

	if (!insn || !ev)
		return -pte_internal;

	/* If we don't have an IP, the event binds to the next PTWRITE
	 * instruction.
	 *
	 * If we have an IP it still binds to the next PTWRITE instruction but
	 * now the IP tells us where that instruction is.  This makes most sense
	 * when tracing is disabled and we don't have any other means of finding
	 * the PTWRITE instruction.  We nevertheless distinguish the two cases,
	 * here.
	 *
	 * In both cases, we move beyond the PTWRITE instruction, so it will be
	 * the last instruction in the current block and @decoder->ip will point
	 * to the instruction following it.
	 */
	if (ev->ip_suppressed) {
		status = pt_blk_proceed_to_insn(decoder, block, insn, iext,
						pt_insn_is_ptwrite);
		if (status <= 0)
			return status;

		/* We now know the IP of the PTWRITE instruction corresponding
		 * to this event.  Fill it in to make it more convenient for the
		 * user to process the event.
		 */
		ev->variant.ptwrite.ip = insn->ip;
		ev->ip_suppressed = 0;
	} else {
		status = pt_blk_proceed_to_ip(decoder, block, insn, iext,
					      ev->variant.ptwrite.ip);
		if (status <= 0)
			return status;

		/* We reached the PTWRITE instruction and @decoder->ip points to
		 * it; @insn/@iext still contain the preceding instruction.
		 *
		 * Proceed beyond the PTWRITE to account for it.  Note that we
		 * may still overflow the block, which would cause us to
		 * postpone both instruction and event to the next block.
		 */
		status = pt_blk_proceed_one_insn(decoder, block, insn, iext);
		if (status <= 0)
			return status;
	}

	return 1;
}