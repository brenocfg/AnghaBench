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
typedef  struct pt_insn_ext const pt_insn_ext ;
typedef  struct pt_insn {scalar_t__ iclass; } const pt_insn ;
struct TYPE_4__ {scalar_t__ end_on_jump; scalar_t__ end_on_call; } ;
struct TYPE_5__ {TYPE_1__ block; } ;
struct TYPE_6__ {TYPE_2__ variant; } ;
struct pt_block_decoder {TYPE_3__ flags; int /*<<< orphan*/  ip; } ;
struct pt_block {int dummy; } ;

/* Variables and functions */
 int pt_blk_proceed_one_insn (struct pt_block_decoder*,struct pt_block*,struct pt_insn const*,struct pt_insn_ext const*) ; 
 int pt_insn_next_ip (int /*<<< orphan*/ *,struct pt_insn const*,struct pt_insn_ext const*) ; 
 int pte_internal ; 
 scalar_t__ ptic_call ; 
 scalar_t__ ptic_jump ; 

__attribute__((used)) static int pt_blk_proceed_to_insn(struct pt_block_decoder *decoder,
				  struct pt_block *block,
				  struct pt_insn *insn,
				  struct pt_insn_ext *iext,
				  int (*predicate)(const struct pt_insn *,
						   const struct pt_insn_ext *))
{
	int status;

	if (!decoder || !insn || !predicate)
		return -pte_internal;

	for (;;) {
		status = pt_blk_proceed_one_insn(decoder, block, insn, iext);
		if (status <= 0)
			return status;

		/* We're done if this instruction matches the spec (positive
		 * status) or we run into an error (negative status).
		 */
		status = predicate(insn, iext);
		if (status != 0)
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
		 */
		if ((decoder->flags.variant.block.end_on_call &&
		     (insn->iclass == ptic_call)) ||
		    (decoder->flags.variant.block.end_on_jump &&
		     (insn->iclass == ptic_jump)))
			return 0;
	}
}