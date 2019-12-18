#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sglist_seg {int dummy; } ;
struct sglist {int sg_nseg; int sg_maxseg; TYPE_1__* sg_segs; } ;
struct TYPE_3__ {size_t ss_len; scalar_t__ ss_paddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTR1 (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  CTR2 (int /*<<< orphan*/ ,char*,int,size_t) ; 
 int EFBIG ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  KTR_DEV ; 
 int /*<<< orphan*/  bcopy (TYPE_1__*,TYPE_1__*,int) ; 
 struct sglist* sglist_alloc (int,int) ; 

int
sglist_slice(struct sglist *original, struct sglist **slice, size_t offset,
    size_t length, int mflags)
{
	struct sglist *sg;
	size_t space, end, foffs, loffs;
	int count, i, fseg;

	/* Nothing to do. */
	if (length == 0)
		return (0);

	/* Figure out how many segments '*slice' needs to have. */
	end = offset + length;
	space = 0;
	count = 0;
	fseg = 0;
	foffs = loffs = 0;
	for (i = 0; i < original->sg_nseg; i++) {
		space += original->sg_segs[i].ss_len;
		if (space > offset) {
			/*
			 * When we hit the first segment, store its index
			 * in 'fseg' and the offset into the first segment
			 * of 'offset' in 'foffs'.
			 */
			if (count == 0) {
				fseg = i;
				foffs = offset - (space -
				    original->sg_segs[i].ss_len);
				CTR1(KTR_DEV, "sglist_slice: foffs = %08lx",
				    foffs);
			}
			count++;

			/*
			 * When we hit the last segment, break out of
			 * the loop.  Store the amount of extra space
			 * at the end of this segment in 'loffs'.
			 */
			if (space >= end) {
				loffs = space - end;
				CTR1(KTR_DEV, "sglist_slice: loffs = %08lx",
				    loffs);
				break;
			}
		}
	}

	/* If we never hit 'end', then 'length' ran off the end, so fail. */
	if (space < end)
		return (EINVAL);

	if (*slice == NULL) {
		sg = sglist_alloc(count, mflags);
		if (sg == NULL)
			return (ENOMEM);
		*slice = sg;
	} else {
		sg = *slice;
		if (sg->sg_maxseg < count)
			return (EFBIG);
		if (sg->sg_nseg != 0)
			return (EINVAL);
	}

	/*
	 * Copy over 'count' segments from 'original' starting at
	 * 'fseg' to 'sg'.
	 */
	bcopy(original->sg_segs + fseg, sg->sg_segs,
	    count * sizeof(struct sglist_seg));
	sg->sg_nseg = count;

	/* Fixup first and last segments if needed. */
	if (foffs != 0) {
		sg->sg_segs[0].ss_paddr += foffs;
		sg->sg_segs[0].ss_len -= foffs;
		CTR2(KTR_DEV, "sglist_slice seg[0]: %08lx:%08lx",
		    (long)sg->sg_segs[0].ss_paddr, sg->sg_segs[0].ss_len);
	}
	if (loffs != 0) {
		sg->sg_segs[count - 1].ss_len -= loffs;
		CTR2(KTR_DEV, "sglist_slice seg[%d]: len %08x", count - 1,
		    sg->sg_segs[count - 1].ss_len);
	}
	return (0);
}