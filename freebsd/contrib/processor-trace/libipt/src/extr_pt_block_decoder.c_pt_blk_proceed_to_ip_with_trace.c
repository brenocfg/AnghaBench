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
typedef  int /*<<< orphan*/  uint64_t ;
struct pt_insn_ext {int dummy; } ;
struct pt_insn {int dummy; } ;
struct pt_block_decoder {int dummy; } ;
struct pt_block {int dummy; } ;

/* Variables and functions */
 int pt_blk_proceed_to_ip (struct pt_block_decoder*,struct pt_block*,struct pt_insn*,struct pt_insn_ext*,int /*<<< orphan*/ ) ; 
 int pt_blk_proceed_with_trace (struct pt_block_decoder*,struct pt_insn*,struct pt_insn_ext*) ; 
 int pte_bad_query ; 

__attribute__((used)) static int pt_blk_proceed_to_ip_with_trace(struct pt_block_decoder *decoder,
					   struct pt_block *block,
					   uint64_t ip)
{
	struct pt_insn_ext iext;
	struct pt_insn insn;
	int status;

	/* Try to reach @ip without trace.
	 *
	 * We're also OK if @block overflowed or we switched sections and we
	 * have to try again in the next iteration.
	 */
	status = pt_blk_proceed_to_ip(decoder, block, &insn, &iext, ip);
	if (status != -pte_bad_query)
		return status;

	/* Needing trace is not an error.  We use trace to determine the next
	 * start IP and end the block.
	 */
	return pt_blk_proceed_with_trace(decoder, &insn, &iext);
}