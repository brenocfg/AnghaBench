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
struct blame_entry {scalar_t__ suspect; scalar_t__ s_lno; } ;

/* Variables and functions */

__attribute__((used)) static int compare_blame_suspect(const void *p1, const void *p2)
{
	const struct blame_entry *s1 = p1, *s2 = p2;
	/*
	 * to allow for collating suspects, we sort according to the
	 * respective pointer value as the primary sorting criterion.
	 * The actual relation is pretty unimportant as long as it
	 * establishes a total order.  Comparing as integers gives us
	 * that.
	 */
	if (s1->suspect != s2->suspect)
		return (intptr_t)s1->suspect > (intptr_t)s2->suspect ? 1 : -1;
	if (s1->s_lno == s2->s_lno)
		return 0;
	return s1->s_lno > s2->s_lno ? 1 : -1;
}