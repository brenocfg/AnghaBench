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
struct que_elem {struct que_elem* next; struct que_elem* prev; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,struct que_elem*,struct que_elem*,struct que_elem*) ; 
 int /*<<< orphan*/  stderr ; 

void
insque(void *element, void *pred)
{
	struct que_elem *prev, *next, *elem;

	elem = (struct que_elem *)element;
	prev = (struct que_elem *)pred;

	if (prev == NULL) {
		elem->prev = elem->next = NULL;
		return;
	}

	next = prev->next;
	if (next != NULL) {
#ifdef DEBUG
		if (next->prev != prev) {
			fprintf(stderr, "insque: Inconsistency detected:"
			    " next(%p)->prev(%p) != prev(%p)\n",
			    next, next->prev, prev);
		}
#endif
		next->prev = elem;
	}
	prev->next = elem;
	elem->prev = prev;
	elem->next = next;
}