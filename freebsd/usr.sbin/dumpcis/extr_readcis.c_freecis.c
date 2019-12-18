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
struct tuple_list {struct tuple_list* data; struct tuple_list* next; struct tuple_list* tuples; } ;
struct tuple {struct tuple* data; struct tuple* next; struct tuple* tuples; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct tuple_list*) ; 

void
freecis(struct tuple_list *tlist)
{
	struct tuple_list *tl;
	struct tuple *tp;

	while ((tl = tlist) != 0) {
		tlist = tl->next;
		while ((tp = tl->tuples) != 0) {
			tl->tuples = tp->next;
			free(tp->data);
			free(tp);
		}
		free(tl);
	}
}