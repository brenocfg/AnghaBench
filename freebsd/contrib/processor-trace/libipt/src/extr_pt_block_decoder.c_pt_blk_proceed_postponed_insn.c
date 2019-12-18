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
struct pt_block_decoder {int /*<<< orphan*/  iext; int /*<<< orphan*/  insn; int /*<<< orphan*/  ip; int /*<<< orphan*/  enabled; int /*<<< orphan*/  process_insn; } ;

/* Variables and functions */
 int pt_blk_clear_postponed_insn (struct pt_block_decoder*) ; 
 int pt_blk_proceed_with_trace (struct pt_block_decoder*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pt_insn_next_ip (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pte_bad_query ; 
 int pte_internal ; 

__attribute__((used)) static int pt_blk_proceed_postponed_insn(struct pt_block_decoder *decoder)
{
	int status;

	if (!decoder)
		return -pte_internal;

	/* There's nothing to do if we have no postponed instruction. */
	if (!decoder->process_insn)
		return 0;

	/* There's nothing to do if tracing got disabled. */
	if (!decoder->enabled)
		return pt_blk_clear_postponed_insn(decoder);

	status = pt_insn_next_ip(&decoder->ip, &decoder->insn, &decoder->iext);
	if (status < 0) {
		if (status != -pte_bad_query)
			return status;

		status = pt_blk_proceed_with_trace(decoder, &decoder->insn,
						   &decoder->iext);
		if (status < 0)
			return status;
	}

	return pt_blk_clear_postponed_insn(decoder);
}