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
struct region {unsigned int end1; unsigned int begin1; unsigned int begin2; unsigned int end2; } ;
struct record {unsigned int cnt; unsigned int ptr; struct record* next; } ;
struct histindex {unsigned int cnt; int has_common; struct record** records; } ;

/* Variables and functions */
 int CMP (struct histindex*,int,unsigned int,int,unsigned int) ; 
 int /*<<< orphan*/  CNT (struct histindex*,unsigned int) ; 
 unsigned int LINE_END (int) ; 
 unsigned int NEXT_PTR (struct histindex*,unsigned int) ; 
 size_t TABLE_HASH (struct histindex*,int,unsigned int) ; 
 unsigned int XDL_MIN (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int try_lcs(
	struct histindex *index, struct region *lcs, unsigned int b_ptr,
	unsigned int line1, unsigned int count1,
	unsigned int line2, unsigned int count2)
{
	unsigned int b_next = b_ptr + 1;
	struct record *rec = index->records[TABLE_HASH(index, 2, b_ptr)];
	unsigned int as, ae, bs, be, np, rc;
	int should_break;

	for (; rec; rec = rec->next) {
		if (rec->cnt > index->cnt) {
			if (!index->has_common)
				index->has_common = CMP(index, 1, rec->ptr, 2, b_ptr);
			continue;
		}

		as = rec->ptr;
		if (!CMP(index, 1, as, 2, b_ptr))
			continue;

		index->has_common = 1;
		for (;;) {
			should_break = 0;
			np = NEXT_PTR(index, as);
			bs = b_ptr;
			ae = as;
			be = bs;
			rc = rec->cnt;

			while (line1 < as && line2 < bs
				&& CMP(index, 1, as - 1, 2, bs - 1)) {
				as--;
				bs--;
				if (1 < rc)
					rc = XDL_MIN(rc, CNT(index, as));
			}
			while (ae < LINE_END(1) && be < LINE_END(2)
				&& CMP(index, 1, ae + 1, 2, be + 1)) {
				ae++;
				be++;
				if (1 < rc)
					rc = XDL_MIN(rc, CNT(index, ae));
			}

			if (b_next <= be)
				b_next = be + 1;
			if (lcs->end1 - lcs->begin1 < ae - as || rc < index->cnt) {
				lcs->begin1 = as;
				lcs->begin2 = bs;
				lcs->end1 = ae;
				lcs->end2 = be;
				index->cnt = rc;
			}

			if (np == 0)
				break;

			while (np <= ae) {
				np = NEXT_PTR(index, np);
				if (np == 0) {
					should_break = 1;
					break;
				}
			}

			if (should_break)
				break;

			as = np;
		}
	}
	return b_next;
}