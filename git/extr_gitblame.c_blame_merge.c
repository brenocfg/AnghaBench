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
struct blame_entry {scalar_t__ s_lno; struct blame_entry* next; } ;

/* Variables and functions */

__attribute__((used)) static struct blame_entry *blame_merge(struct blame_entry *list1,
				       struct blame_entry *list2)
{
	struct blame_entry *p1 = list1, *p2 = list2,
		**tail = &list1;

	if (!p1)
		return p2;
	if (!p2)
		return p1;

	if (p1->s_lno <= p2->s_lno) {
		do {
			tail = &p1->next;
			if ((p1 = *tail) == NULL) {
				*tail = p2;
				return list1;
			}
		} while (p1->s_lno <= p2->s_lno);
	}
	for (;;) {
		*tail = p2;
		do {
			tail = &p2->next;
			if ((p2 = *tail) == NULL)  {
				*tail = p1;
				return list1;
			}
		} while (p1->s_lno > p2->s_lno);
		*tail = p1;
		do {
			tail = &p1->next;
			if ((p1 = *tail) == NULL) {
				*tail = p2;
				return list1;
			}
		} while (p1->s_lno <= p2->s_lno);
	}
}