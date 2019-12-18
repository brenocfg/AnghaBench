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
or_squish(PLAN *plan)
{
	PLAN *next;		/* next node being processed */
	PLAN *tail;		/* pointer to tail of result plan */
	PLAN *result;		/* pointer to head of result plan */

	tail = result = next = NULL;

	while ((next = yanknode(&plan)) != NULL) {
		/*
		 * if we encounter a ( expression ) then look for or's in
		 * the expr subplan.
		 */
		if (next->execute == f_expr)
			next->p_data[0] = or_squish(next->p_data[0]);

		/* if we encounter a not then look for or's in the subplan */
		if (next->execute == f_not)
			next->p_data[0] = or_squish(next->p_data[0]);

		/*
		 * if we encounter an or, then place our collected plan in the
		 * or's first subplan and then recursively collect the
		 * remaining stuff into the second subplan and return the or.
		 */
		if (next->execute == f_or) {
			if (result == NULL)
				errx(1, "-o: no expression before -o");
			next->p_data[0] = result;
			next->p_data[1] = or_squish(plan);
			if (next->p_data[1] == NULL)
				errx(1, "-o: no expression after -o");
			return (next);
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