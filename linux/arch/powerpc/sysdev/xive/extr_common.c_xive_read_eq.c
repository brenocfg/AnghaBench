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
typedef  int u32 ;
struct xive_q {int idx; int toggle; int msk; scalar_t__ qpage; } ;

/* Variables and functions */
 int be32_to_cpup (scalar_t__) ; 

__attribute__((used)) static u32 xive_read_eq(struct xive_q *q, bool just_peek)
{
	u32 cur;

	if (!q->qpage)
		return 0;
	cur = be32_to_cpup(q->qpage + q->idx);

	/* Check valid bit (31) vs current toggle polarity */
	if ((cur >> 31) == q->toggle)
		return 0;

	/* If consuming from the queue ... */
	if (!just_peek) {
		/* Next entry */
		q->idx = (q->idx + 1) & q->msk;

		/* Wrap around: flip valid toggle */
		if (q->idx == 0)
			q->toggle ^= 1;
	}
	/* Mask out the valid bit (31) */
	return cur & 0x7fffffff;
}