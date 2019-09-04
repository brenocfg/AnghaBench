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
struct sline {unsigned long flag; int /*<<< orphan*/ * p_lno; struct lline* lost; } ;
struct lline {unsigned long parent_map; struct lline* next; } ;

/* Variables and functions */

__attribute__((used)) static void reuse_combine_diff(struct sline *sline, unsigned long cnt,
			       int i, int j)
{
	/* We have already examined parent j and we know parent i
	 * and parent j are the same, so reuse the combined result
	 * of parent j for parent i.
	 */
	unsigned long lno, imask, jmask;
	imask = (1UL<<i);
	jmask = (1UL<<j);

	for (lno = 0; lno <= cnt; lno++) {
		struct lline *ll = sline->lost;
		sline->p_lno[i] = sline->p_lno[j];
		while (ll) {
			if (ll->parent_map & jmask)
				ll->parent_map |= imask;
			ll = ll->next;
		}
		if (sline->flag & jmask)
			sline->flag |= imask;
		sline++;
	}
	/* the overall size of the file (sline[cnt]) */
	sline->p_lno[i] = sline->p_lno[j];
}