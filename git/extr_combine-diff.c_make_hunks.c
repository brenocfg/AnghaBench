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
struct sline {unsigned long flag; struct lline* lost; } ;
struct lline {unsigned long parent_map; struct lline* next; } ;

/* Variables and functions */
 unsigned long adjust_hunk_tail (struct sline*,unsigned long,unsigned long,unsigned long) ; 
 unsigned long context ; 
 int give_context (struct sline*,unsigned long,int) ; 
 scalar_t__ interesting (struct sline*,unsigned long) ; 

__attribute__((used)) static int make_hunks(struct sline *sline, unsigned long cnt,
		       int num_parent, int dense)
{
	unsigned long all_mask = (1UL<<num_parent) - 1;
	unsigned long mark = (1UL<<num_parent);
	unsigned long i;
	int has_interesting = 0;

	for (i = 0; i <= cnt; i++) {
		if (interesting(&sline[i], all_mask))
			sline[i].flag |= mark;
		else
			sline[i].flag &= ~mark;
	}
	if (!dense)
		return give_context(sline, cnt, num_parent);

	/* Look at each hunk, and if we have changes from only one
	 * parent, or the changes are the same from all but one
	 * parent, mark that uninteresting.
	 */
	i = 0;
	while (i <= cnt) {
		unsigned long j, hunk_begin, hunk_end;
		unsigned long same_diff;
		while (i <= cnt && !(sline[i].flag & mark))
			i++;
		if (cnt < i)
			break; /* No more interesting hunks */
		hunk_begin = i;
		for (j = i + 1; j <= cnt; j++) {
			if (!(sline[j].flag & mark)) {
				/* Look beyond the end to see if there
				 * is an interesting line after this
				 * hunk within context span.
				 */
				unsigned long la; /* lookahead */
				int contin = 0;
				la = adjust_hunk_tail(sline, all_mask,
						     hunk_begin, j);
				la = (la + context < cnt + 1) ?
					(la + context) : cnt + 1;
				while (la && j <= --la) {
					if (sline[la].flag & mark) {
						contin = 1;
						break;
					}
				}
				if (!contin)
					break;
				j = la;
			}
		}
		hunk_end = j;

		/* [i..hunk_end) are interesting.  Now is it really
		 * interesting?  We check if there are only two versions
		 * and the result matches one of them.  That is, we look
		 * at:
		 *   (+) line, which records lines added to which parents;
		 *       this line appears in the result.
		 *   (-) line, which records from what parents the line
		 *       was removed; this line does not appear in the result.
		 * then check the set of parents the result has difference
		 * from, from all lines.  If there are lines that has
		 * different set of parents that the result has differences
		 * from, that means we have more than two versions.
		 *
		 * Even when we have only two versions, if the result does
		 * not match any of the parents, the it should be considered
		 * interesting.  In such a case, we would have all '+' line.
		 * After passing the above "two versions" test, that would
		 * appear as "the same set of parents" to be "all parents".
		 */
		same_diff = 0;
		has_interesting = 0;
		for (j = i; j < hunk_end && !has_interesting; j++) {
			unsigned long this_diff = sline[j].flag & all_mask;
			struct lline *ll = sline[j].lost;
			if (this_diff) {
				/* This has some changes.  Is it the
				 * same as others?
				 */
				if (!same_diff)
					same_diff = this_diff;
				else if (same_diff != this_diff) {
					has_interesting = 1;
					break;
				}
			}
			while (ll && !has_interesting) {
				/* Lost this line from these parents;
				 * who are they?  Are they the same?
				 */
				this_diff = ll->parent_map;
				if (!same_diff)
					same_diff = this_diff;
				else if (same_diff != this_diff) {
					has_interesting = 1;
				}
				ll = ll->next;
			}
		}

		if (!has_interesting && same_diff != all_mask) {
			/* This hunk is not that interesting after all */
			for (j = hunk_begin; j < hunk_end; j++)
				sline[j].flag &= ~mark;
		}
		i = hunk_end;
	}

	has_interesting = give_context(sline, cnt, num_parent);
	return has_interesting;
}