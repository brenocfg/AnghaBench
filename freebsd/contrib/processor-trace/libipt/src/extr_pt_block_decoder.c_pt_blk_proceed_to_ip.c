#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct pt_insn_ext {int dummy; } ;
struct pt_insn {scalar_t__ iclass; } ;
struct TYPE_4__ {scalar_t__ end_on_jump; scalar_t__ end_on_call; } ;
struct TYPE_5__ {TYPE_1__ block; } ;
struct TYPE_6__ {TYPE_2__ variant; } ;
struct pt_block_decoder {scalar_t__ ip; TYPE_3__ flags; } ;
struct pt_block {int dummy; } ;

/* Variables and functions */
 int pt_blk_proceed_one_insn (struct pt_block_decoder*,struct pt_block*,struct pt_insn*,struct pt_insn_ext*) ; 
 int pt_insn_next_ip (scalar_t__*,struct pt_insn*,struct pt_insn_ext*) ; 
 int pte_internal ; 
 scalar_t__ ptic_call ; 
 scalar_t__ ptic_jump ; 

__attribute__((used)) static int pt_blk_proceed_to_ip(struct pt_block_decoder *decoder,
				struct pt_block *block, struct pt_insn *insn,
				struct pt_insn_ext *iext, uint64_t ip)
{
	int status;

	if (!decoder || !insn)
		return -pte_internal;

	for (;;) {
		/* We're done when we reach @ip.  We may not even have to decode
		 * a single instruction in some cases.
		 */
		if (decoder->ip == ip)
			return 1;

		status = pt_blk_proceed_one_insn(decoder, block, insn, iext);
		if (status <= 0)
			return status;

		/* Let's see if we can proceed to the next IP without trace. */
		status = pt_insn_next_ip(&decoder->ip, insn, iext);
		if (status < 0)
			return status;

		/* End the block if the user asked us to.
		 *
		 * We only need to take care about direct near branches.
		 * Indirect and far branches require trace and will naturally
		 * end a block.
		 *
		 * The call at the end of the block may have reached @ip; make
		 * sure to indicate that.
		 */
		if ((decoder->flags.variant.block.end_on_call &&
		     (insn->iclass == ptic_call)) ||
		    (decoder->flags.variant.block.end_on_jump &&
		     (insn->iclass == ptic_jump))) {
			return (decoder->ip == ip ? 1 : 0);
		}
	}
}