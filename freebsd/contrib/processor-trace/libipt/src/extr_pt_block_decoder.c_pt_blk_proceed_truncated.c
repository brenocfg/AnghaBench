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
struct pt_insn_ext {int /*<<< orphan*/  size; int /*<<< orphan*/  iclass; int /*<<< orphan*/  raw; int /*<<< orphan*/  truncated; int /*<<< orphan*/  ip; int /*<<< orphan*/  mode; } ;
struct pt_insn {int /*<<< orphan*/  size; int /*<<< orphan*/  iclass; int /*<<< orphan*/  raw; int /*<<< orphan*/  truncated; int /*<<< orphan*/  ip; int /*<<< orphan*/  mode; } ;
struct pt_block_decoder {int /*<<< orphan*/  ip; int /*<<< orphan*/  asid; int /*<<< orphan*/  image; int /*<<< orphan*/  mode; } ;
struct pt_block {int truncated; int /*<<< orphan*/  size; int /*<<< orphan*/  iclass; int /*<<< orphan*/  raw; } ;
typedef  int /*<<< orphan*/  insn ;
typedef  int /*<<< orphan*/  iext ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct pt_insn_ext*,int /*<<< orphan*/ ,int) ; 
 int pt_blk_log_call (struct pt_block_decoder*,struct pt_insn_ext*,struct pt_insn_ext*) ; 
 int pt_blk_proceed_with_trace (struct pt_block_decoder*,struct pt_insn_ext*,struct pt_insn_ext*) ; 
 int pt_insn_decode (struct pt_insn_ext*,struct pt_insn_ext*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int pt_insn_next_ip (int /*<<< orphan*/ *,struct pt_insn_ext*,struct pt_insn_ext*) ; 
 int pte_bad_query ; 
 int pte_internal ; 

__attribute__((used)) static int pt_blk_proceed_truncated(struct pt_block_decoder *decoder,
				    struct pt_block *block)
{
	struct pt_insn_ext iext;
	struct pt_insn insn;
	int errcode;

	if (!decoder || !block)
		return -pte_internal;

	memset(&iext, 0, sizeof(iext));
	memset(&insn, 0, sizeof(insn));

	insn.mode = decoder->mode;
	insn.ip = decoder->ip;

	errcode = pt_insn_decode(&insn, &iext, decoder->image, &decoder->asid);
	if (errcode < 0)
		return errcode;

	/* We shouldn't use this function if the instruction isn't truncated. */
	if (!insn.truncated)
		return -pte_internal;

	/* Provide the instruction in the block.  This ends the block. */
	memcpy(block->raw, insn.raw, insn.size);
	block->iclass = insn.iclass;
	block->size = insn.size;
	block->truncated = 1;

	/* Log calls' return addresses for return compression. */
	errcode = pt_blk_log_call(decoder, &insn, &iext);
	if (errcode < 0)
		return errcode;

	/* Let's see if we can proceed to the next IP without trace.
	 *
	 * The truncated instruction ends the block but we still need to get the
	 * next block's start IP.
	 */
	errcode = pt_insn_next_ip(&decoder->ip, &insn, &iext);
	if (errcode < 0) {
		if (errcode != -pte_bad_query)
			return errcode;

		return pt_blk_proceed_with_trace(decoder, &insn, &iext);
	}

	return 0;
}