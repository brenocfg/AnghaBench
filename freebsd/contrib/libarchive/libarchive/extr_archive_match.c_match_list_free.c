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
struct match_list {struct match* first; } ;
struct match {int /*<<< orphan*/  pattern; struct match* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  archive_mstring_clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct match*) ; 

__attribute__((used)) static void
match_list_free(struct match_list *list)
{
	struct match *p, *q;

	for (p = list->first; p != NULL; ) {
		q = p;
		p = p->next;
		archive_mstring_clean(&(q->pattern));
		free(q);
	}
}