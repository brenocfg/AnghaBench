#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct pt_insn_ext {int dummy; } ;
struct pt_insn {scalar_t__ iclass; } ;
struct pt_conf_addr_filter {int dummy; } ;
struct TYPE_8__ {scalar_t__ end_on_jump; scalar_t__ end_on_call; } ;
struct TYPE_9__ {TYPE_3__ block; } ;
struct TYPE_10__ {TYPE_4__ variant; } ;
struct TYPE_6__ {struct pt_conf_addr_filter addr_filter; } ;
struct TYPE_7__ {TYPE_1__ config; } ;
struct pt_block_decoder {TYPE_5__ flags; int /*<<< orphan*/  ip; TYPE_2__ query; } ;
struct pt_block {int dummy; } ;

/* Variables and functions */
 int pt_blk_proceed_to_insn (struct pt_block_decoder*,struct pt_block*,struct pt_insn*,struct pt_insn_ext*,int /*<<< orphan*/ ) ; 
 int pt_filter_addr_check (struct pt_conf_addr_filter const*,int /*<<< orphan*/ ) ; 
 scalar_t__ pt_insn_changes_cr3 (struct pt_insn*,struct pt_insn_ext*) ; 
 int pt_insn_next_ip (int /*<<< orphan*/ *,struct pt_insn*,struct pt_insn_ext*) ; 
 int /*<<< orphan*/  pt_insn_skl014 ; 
 int pte_internal ; 
 scalar_t__ ptic_call ; 
 scalar_t__ ptic_jump ; 

__attribute__((used)) static int pt_blk_proceed_skl014(struct pt_block_decoder *decoder,
				 struct pt_block *block, struct pt_insn *insn,
				 struct pt_insn_ext *iext)
{
	const struct pt_conf_addr_filter *addr_filter;
	int status;

	if (!decoder || !block || !insn || !iext)
		return -pte_internal;

	addr_filter = &decoder->query.config.addr_filter;
	for (;;) {
		uint64_t ip;

		status = pt_blk_proceed_to_insn(decoder, block, insn, iext,
						pt_insn_skl014);
		if (status <= 0)
			break;

		/* The erratum doesn't apply if we can bind the event to a
		 * CR3-changing instruction.
		 */
		if (pt_insn_changes_cr3(insn, iext))
			break;

		/* Check the filter against the branch target. */
		status = pt_insn_next_ip(&ip, insn, iext);
		if (status < 0)
			break;

		status = pt_filter_addr_check(addr_filter, ip);
		if (status <= 0) {
			/* We need to flip the indication.
			 *
			 * We reached the event location when @ip lies inside a
			 * tracing-disabled region.
			 */
			if (!status)
				status = 1;

			break;
		}

		/* This is not the correct instruction.  Proceed past it and try
		 * again.
		 */
		decoder->ip = ip;

		/* End the block if the user asked us to.
		 *
		 * We only need to take care about direct near branches.
		 * Indirect and far branches require trace and will naturally
		 * end a block.
		 */
		if ((decoder->flags.variant.block.end_on_call &&
		    (insn->iclass == ptic_call)) ||
		    (decoder->flags.variant.block.end_on_jump &&
		    (insn->iclass == ptic_jump)))
			break;
	}

	return status;
}