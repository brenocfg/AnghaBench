#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ execute; struct TYPE_6__* next; struct TYPE_6__** p_data; } ;
typedef  TYPE_1__ PLAN ;

/* Variables and functions */
 int /*<<< orphan*/  errx (int,char*) ; 
 scalar_t__ f_expr ; 
 scalar_t__ f_not ; 
 scalar_t__ f_or ; 
 TYPE_1__* yanknode (TYPE_1__**) ; 

PLAN *
not_squish(PLAN *plan)
{
	PLAN *next;		/* next node being processed */
	PLAN *node;		/* temporary node used in f_not processing */
	PLAN *tail;		/* pointer to tail of result plan */
	PLAN *result;		/* pointer to head of result plan */

	tail = result = NULL;

	while ((next = yanknode(&plan))) {
		/*
		 * if we encounter a ( expression ) then look for nots in
		 * the expr subplan.
		 */
		if (next->execute == f_expr)
			next->p_data[0] = not_squish(next->p_data[0]);

		/*
		 * if we encounter a not, then snag the next node and place
		 * it in the not's subplan.  As an optimization we compress
		 * several not's to zero or one not.
		 */
		if (next->execute == f_not) {
			int notlevel = 1;

			node = yanknode(&plan);
			while (node != NULL && node->execute == f_not) {
				++notlevel;
				node = yanknode(&plan);
			}
			if (node == NULL)
				errx(1, "!: no following expression");
			if (node->execute == f_or)
				errx(1, "!: nothing between ! and -o");
			/*
			 * If we encounter ! ( expr ) then look for nots in
			 * the expr subplan.
			 */
			if (node->execute == f_expr)
				node->p_data[0] = not_squish(node->p_data[0]);
			if (notlevel % 2 != 1)
				next = node;
			else
				next->p_data[0] = node;
		}

		/* add the node to our result plan */
		if (result == NULL)
			tail = result = next;
		else {
			tail->next = next;
			tail = next;
		}
		tail->next = NULL;
	}
	return (result);
}