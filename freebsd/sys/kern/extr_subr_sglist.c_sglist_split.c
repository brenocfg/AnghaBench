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
struct sglist {int sg_refs; int sg_nseg; int sg_maxseg; TYPE_1__* sg_segs; } ;
struct TYPE_3__ {size_t ss_len; scalar_t__ ss_paddr; } ;

/* Variables and functions */
 int EDOOFUS ; 
 int EFBIG ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  bcopy (TYPE_1__*,TYPE_1__*,int) ; 
 struct sglist* sglist_alloc (int,int) ; 

int
sglist_split(struct sglist *original, struct sglist **head, size_t length,
    int mflags)
{
	struct sglist *sg;
	size_t space, split;
	int count, i;

	if (original->sg_refs > 1)
		return (EDOOFUS);

	/* Figure out how big of a sglist '*head' has to hold. */
	count = 0;
	space = 0;
	split = 0;
	for (i = 0; i < original->sg_nseg; i++) {
		space += original->sg_segs[i].ss_len;
		count++;
		if (space >= length) {
			/*
			 * If 'length' falls in the middle of a
			 * scatter/gather list entry, then 'split'
			 * holds how much of that entry will remain in
			 * 'original'.
			 */
			split = space - length;
			break;
		}
	}

	/* Nothing to do, so leave head empty. */
	if (count == 0)
		return (0);

	if (*head == NULL) {
		sg = sglist_alloc(count, mflags);
		if (sg == NULL)
			return (ENOMEM);
		*head = sg;
	} else {
		sg = *head;
		if (sg->sg_maxseg < count)
			return (EFBIG);
		if (sg->sg_nseg != 0)
			return (EINVAL);
	}

	/* Copy 'count' entries to 'sg' from 'original'. */
	bcopy(original->sg_segs, sg->sg_segs, count *
	    sizeof(struct sglist_seg));
	sg->sg_nseg = count;

	/*
	 * If we had to split a list entry, fixup the last entry in
	 * 'sg' and the new first entry in 'original'.  We also
	 * decrement 'count' by 1 since we will only be removing
	 * 'count - 1' segments from 'original' now.
	 */
	if (split != 0) {
		count--;
		sg->sg_segs[count].ss_len -= split;
		original->sg_segs[count].ss_paddr =
		    sg->sg_segs[count].ss_paddr + split;
		original->sg_segs[count].ss_len = split;
	}

	/* Trim 'count' entries from the front of 'original'. */
	original->sg_nseg -= count;
	bcopy(original->sg_segs + count, original->sg_segs, count *
	    sizeof(struct sglist_seg));
	return (0);
}