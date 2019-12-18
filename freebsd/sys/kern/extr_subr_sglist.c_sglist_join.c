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
struct sglist_seg {scalar_t__ ss_paddr; scalar_t__ ss_len; } ;
struct sglist {int sg_nseg; int sg_maxseg; struct sglist_seg* sg_segs; } ;

/* Variables and functions */
 int EFBIG ; 
 int /*<<< orphan*/  bcopy (struct sglist_seg*,struct sglist_seg*,int) ; 
 int /*<<< orphan*/  sglist_reset (struct sglist*) ; 

int
sglist_join(struct sglist *first, struct sglist *second)
{
	struct sglist_seg *flast, *sfirst;
	int append;

	/* If 'second' is empty, there is nothing to do. */
	if (second->sg_nseg == 0)
		return (0);

	/*
	 * If the first entry in 'second' can be appended to the last entry
	 * in 'first' then set append to '1'.
	 */
	append = 0;
	flast = &first->sg_segs[first->sg_nseg - 1];
	sfirst = &second->sg_segs[0];
	if (first->sg_nseg != 0 &&
	    flast->ss_paddr + flast->ss_len == sfirst->ss_paddr)
		append = 1;

	/* Make sure 'first' has enough room. */
	if (first->sg_nseg + second->sg_nseg - append > first->sg_maxseg)
		return (EFBIG);

	/* Merge last in 'first' and first in 'second' if needed. */
	if (append)
		flast->ss_len += sfirst->ss_len;

	/* Append new segments from 'second' to 'first'. */
	bcopy(first->sg_segs + first->sg_nseg, second->sg_segs + append,
	    (second->sg_nseg - append) * sizeof(struct sglist_seg));
	first->sg_nseg += second->sg_nseg - append;
	sglist_reset(second);
	return (0);
}