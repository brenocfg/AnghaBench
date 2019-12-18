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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint64_t ;
struct pt_mapped_section {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  displacement; int /*<<< orphan*/  is_direct; } ;
struct TYPE_7__ {TYPE_1__ branch; } ;
struct pt_insn_ext {TYPE_2__ variant; } ;
struct pt_insn {scalar_t__ mode; scalar_t__ size; int iclass; scalar_t__ ip; } ;
struct TYPE_8__ {int /*<<< orphan*/  end_on_jump; } ;
struct TYPE_9__ {TYPE_3__ block; } ;
struct TYPE_10__ {TYPE_4__ variant; } ;
struct pt_block_decoder {TYPE_5__ flags; scalar_t__ ip; } ;
struct pt_block_cache {int dummy; } ;
struct pt_block {scalar_t__ truncated; } ;
struct pt_bcache_entry {int ninsn; scalar_t__ mode; scalar_t__ isize; scalar_t__ displacement; void* qualifier; } ;
typedef  scalar_t__ int64_t ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  bce ;

/* Variables and functions */
 int /*<<< orphan*/  fallthrough ; 
 int /*<<< orphan*/  memset (struct pt_bcache_entry*,int /*<<< orphan*/ ,int) ; 
 int pt_bcache_add (struct pt_block_cache*,scalar_t__,struct pt_bcache_entry) ; 
 int pt_bcache_lookup (struct pt_bcache_entry*,struct pt_block_cache*,scalar_t__) ; 
 scalar_t__ pt_bce_exec_mode (struct pt_bcache_entry) ; 
 int /*<<< orphan*/  pt_bce_is_valid (struct pt_bcache_entry) ; 
 int pt_blk_add_decode (struct pt_block_cache*,scalar_t__,scalar_t__) ; 
 int pt_blk_add_trampoline (struct pt_block_cache*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pt_blk_is_in_section (struct pt_mapped_section const*,scalar_t__) ; 
 int pt_blk_proceed_one_insn (struct pt_block_decoder*,struct pt_block*,struct pt_insn*,struct pt_insn_ext*) ; 
 int pt_blk_proceed_with_trace (struct pt_block_decoder*,struct pt_insn*,struct pt_insn_ext*) ; 
 int pt_insn_next_ip (scalar_t__*,struct pt_insn*,struct pt_insn_ext*) ; 
 scalar_t__ pt_msec_unmap (struct pt_mapped_section const*,scalar_t__) ; 
 void* ptbq_cond ; 
 void* ptbq_decode ; 
 void* ptbq_ind_call ; 
 void* ptbq_indirect ; 
 void* ptbq_return ; 
 int pte_bad_query ; 
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

__attribute__((used)) static int
pt_blk_proceed_no_event_fill_cache(struct pt_block_decoder *decoder,
				   struct pt_block *block,
				   struct pt_block_cache *bcache,
				   const struct pt_mapped_section *msec,
				   size_t steps)
{
	struct pt_bcache_entry bce;
	struct pt_insn_ext iext;
	struct pt_insn insn;
	uint64_t nip, dip, ioff, noff;
	int64_t disp;
	int status;

	if (!decoder || !steps)
		return -pte_internal;

	/* Proceed one instruction by decoding and examining it.
	 *
	 * Note that we also return on a status of zero that indicates that the
	 * instruction didn't fit into @block.
	 */
	status = pt_blk_proceed_one_insn(decoder, block, &insn, &iext);
	if (status <= 0)
		return status;

	ioff = pt_msec_unmap(msec, insn.ip);

	/* Let's see if we can proceed to the next IP without trace.
	 *
	 * If we can't, this is certainly a decision point.
	 */
	status = pt_insn_next_ip(&decoder->ip, &insn, &iext);
	if (status < 0) {
		if (status != -pte_bad_query)
			return status;

		memset(&bce, 0, sizeof(bce));
		bce.ninsn = 1;
		bce.mode = insn.mode;
		bce.isize = insn.size;

		/* Clear the instruction size in case of overflows. */
		if ((uint8_t) bce.isize != insn.size)
			bce.isize = 0;

		switch (insn.iclass) {
		case ptic_ptwrite:
		case ptic_error:
		case ptic_other:
			return -pte_internal;

		case ptic_jump:
			/* A direct jump doesn't require trace. */
			if (iext.variant.branch.is_direct)
				return -pte_internal;

			bce.qualifier = ptbq_indirect;
			break;

		case ptic_call:
			/* A direct call doesn't require trace. */
			if (iext.variant.branch.is_direct)
				return -pte_internal;

			bce.qualifier = ptbq_ind_call;
			break;

		case ptic_return:
			bce.qualifier = ptbq_return;
			break;

		case ptic_cond_jump:
			bce.qualifier = ptbq_cond;
			break;

		case ptic_far_call:
		case ptic_far_return:
		case ptic_far_jump:
			bce.qualifier = ptbq_indirect;
			break;
		}

		/* If the block was truncated, we have to decode its last
		 * instruction each time.
		 *
		 * We could have skipped the above switch and size assignment in
		 * this case but this is already a slow and hopefully infrequent
		 * path.
		 */
		if (block->truncated)
			bce.qualifier = ptbq_decode;

		status = pt_bcache_add(bcache, ioff, bce);
		if (status < 0)
			return status;

		return pt_blk_proceed_with_trace(decoder, &insn, &iext);
	}

	/* The next instruction's IP. */
	nip = decoder->ip;
	noff = pt_msec_unmap(msec, nip);

	/* Even if we were able to proceed without trace, we might have to stop
	 * here for various reasons:
	 *
	 *   - at near direct calls to update the return-address stack
	 *
	 *     We are forced to re-decode @insn to get the branch displacement.
	 *
	 *     Even though it is constant, we don't cache it to avoid increasing
	 *     the size of a cache entry.  Note that the displacement field is
	 *     zero for this entry and we might be tempted to use it - but other
	 *     entries that point to this decision point will have non-zero
	 *     displacement.
	 *
	 *     We could proceed after a near direct call but we migh as well
	 *     postpone it to the next iteration.  Make sure to end the block if
	 *     @decoder->flags.variant.block.end_on_call is set, though.
	 *
	 *   - at near direct backwards jumps to detect section splits
	 *
	 *     In case the current section is split underneath us, we must take
	 *     care to detect that split.
	 *
	 *     There is one corner case where the split is in the middle of a
	 *     linear sequence of instructions that branches back into the
	 *     originating section.
	 *
	 *     Calls, indirect branches, and far branches are already covered
	 *     since they either require trace or already require us to stop
	 *     (i.e. near direct calls) for other reasons.  That leaves near
	 *     direct backward jumps.
	 *
	 *     Instead of the decode stop at the jump instruction we're using we
	 *     could have made sure that other block cache entries that extend
	 *     this one insert a trampoline to the jump's entry.  This would
	 *     have been a bit more complicated.
	 *
	 *   - if we switched sections
	 *
	 *     This ends a block just like a branch that requires trace.
	 *
	 *     We need to re-decode @insn in order to determine the start IP of
	 *     the next block.
	 *
	 *   - if the block is truncated
	 *
	 *     We need to read the last instruction's memory from multiple
	 *     sections and provide it to the user.
	 *
	 *     We could still use the block cache but then we'd have to handle
	 *     this case for each qualifier.  Truncation is hopefully rare and
	 *     having to read the memory for the instruction from multiple
	 *     sections is already slow.  Let's rather keep things simple and
	 *     route it through the decode flow, where we already have
	 *     everything in place.
	 */
	switch (insn.iclass) {
	case ptic_call:
		return pt_blk_add_decode(bcache, ioff, insn.mode);

	case ptic_jump:
		/* An indirect branch requires trace and should have been
		 * handled above.
		 */
		if (!iext.variant.branch.is_direct)
			return -pte_internal;

		if (iext.variant.branch.displacement < 0 ||
		    decoder->flags.variant.block.end_on_jump)
			return pt_blk_add_decode(bcache, ioff, insn.mode);

		fallthrough;
	default:
		if (!pt_blk_is_in_section(msec, nip) || block->truncated)
			return pt_blk_add_decode(bcache, ioff, insn.mode);

		break;
	}

	/* We proceeded one instruction.  Let's see if we have a cache entry for
	 * the next instruction.
	 */
	status = pt_bcache_lookup(&bce, bcache, noff);
	if (status < 0)
		return status;

	/* If we don't have a valid cache entry, yet, fill the cache some more.
	 *
	 * On our way back, we add a cache entry for this instruction based on
	 * the cache entry of the succeeding instruction.
	 */
	if (!pt_bce_is_valid(bce)) {
		/* If we exceeded the maximum number of allowed steps, we insert
		 * a trampoline to the next instruction.
		 *
		 * The next time we encounter the same code, we will use the
		 * trampoline to jump directly to where we left off this time
		 * and continue from there.
		 */
		steps -= 1;
		if (!steps)
			return pt_blk_add_trampoline(bcache, ioff, noff,
						     insn.mode);

		status = pt_blk_proceed_no_event_fill_cache(decoder, block,
							    bcache, msec,
							    steps);
		if (status < 0)
			return status;

		/* Let's see if we have more luck this time. */
		status = pt_bcache_lookup(&bce, bcache, noff);
		if (status < 0)
			return status;

		/* If we still don't have a valid cache entry, we're done.  Most
		 * likely, @block overflowed and we couldn't proceed past the
		 * next instruction.
		 */
		if (!pt_bce_is_valid(bce))
			return 0;
	}

	/* We must not have switched execution modes.
	 *
	 * This would require an event and we're on the no-event flow.
	 */
	if (pt_bce_exec_mode(bce) != insn.mode)
		return -pte_internal;

	/* The decision point IP and the displacement from @insn.ip. */
	dip = nip + (uint64_t) (int64_t) bce.displacement;
	disp = (int64_t) (dip - insn.ip);

	/* We may have switched sections if the section was split.  See
	 * pt_blk_proceed_no_event_cached() for a more elaborate comment.
	 *
	 * We're not adding a block cache entry since this won't apply to the
	 * original section which may be shared with other decoders.
	 *
	 * We will instead take the slow path until the end of the section.
	 */
	if (!pt_blk_is_in_section(msec, dip))
		return 0;

	/* Let's try to reach @nip's decision point from @insn.ip.
	 *
	 * There are two fields that may overflow: @bce.ninsn and
	 * @bce.displacement.
	 */
	bce.ninsn += 1;
	bce.displacement = (int32_t) disp;

	/* If none of them overflowed, we're done.
	 *
	 * If one or both overflowed, let's try to insert a trampoline, i.e. we
	 * try to reach @dip via a ptbq_again entry to @nip.
	 */
	if (!bce.ninsn || ((int64_t) bce.displacement != disp))
		return pt_blk_add_trampoline(bcache, ioff, noff, insn.mode);

	/* We're done.  Add the cache entry.
	 *
	 * There's a chance that other decoders updated the cache entry in the
	 * meantime.  They should have come to the same conclusion as we,
	 * though, and the cache entries should be identical.
	 *
	 * Cache updates are atomic so even if the two versions were not
	 * identical, we wouldn't care because they are both correct.
	 */
	return pt_bcache_add(bcache, ioff, bce);
}