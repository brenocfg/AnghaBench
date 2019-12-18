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
struct pt_insn {int /*<<< orphan*/  ip; int /*<<< orphan*/  mode; } ;
struct TYPE_3__ {int /*<<< orphan*/  ip; int /*<<< orphan*/  aborted; } ;
struct TYPE_4__ {TYPE_1__ tsx; } ;
struct pt_event {TYPE_2__ variant; } ;
struct pt_block_decoder {int /*<<< orphan*/  ip; int /*<<< orphan*/  asid; int /*<<< orphan*/  image; int /*<<< orphan*/  mode; } ;
struct pt_block {int /*<<< orphan*/  end_ip; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  bdm64_max_steps ; 
 scalar_t__ pt_blk_block_is_empty (struct pt_block const*) ; 
 int pt_insn_decode (struct pt_insn*,struct pt_insn_ext*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pt_insn_is_branch (struct pt_insn*,struct pt_insn_ext*) ; 
 int pt_insn_range_is_contiguous (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pte_internal ; 

__attribute__((used)) static int pt_blk_handle_erratum_bdm64(struct pt_block_decoder *decoder,
				       const struct pt_block *block,
				       const struct pt_event *ev)
{
	struct pt_insn_ext iext;
	struct pt_insn insn;
	int status;

	if (!decoder || !block || !ev)
		return -pte_internal;

	/* This only affects aborts. */
	if (!ev->variant.tsx.aborted)
		return 0;

	/* This only affects branches that require trace.
	 *
	 * If the erratum hits, that branch ended the current block and brought
	 * us to the trailing event flow.
	 */
	if (pt_blk_block_is_empty(block))
		return 0;

	insn.mode = block->mode;
	insn.ip = block->end_ip;

	status = pt_insn_decode(&insn, &iext, decoder->image, &decoder->asid);
	if (status < 0)
		return 0;

	if (!pt_insn_is_branch(&insn, &iext))
		return 0;

	/* Let's check if we can reach the event location from here.
	 *
	 * If we can, let's assume the erratum did not hit.  We might still be
	 * wrong but we're not able to tell.
	 */
	status = pt_insn_range_is_contiguous(decoder->ip, ev->variant.tsx.ip,
					     decoder->mode, decoder->image,
					     &decoder->asid, bdm64_max_steps);
	if (status > 0)
		return status;

	/* We can't reach the event location.  This could either mean that we
	 * stopped too early (and status is zero) or that the erratum hit.
	 *
	 * We assume the latter and pretend that the previous branch brought us
	 * to the event location, instead.
	 */
	decoder->ip = ev->variant.tsx.ip;

	return 1;
}