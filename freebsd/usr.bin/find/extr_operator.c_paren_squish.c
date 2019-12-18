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
struct TYPE_6__ {scalar_t__ execute; struct TYPE_6__* next; } ;
typedef  TYPE_1__ PLAN ;

/* Variables and functions */
 int /*<<< orphan*/  errx (int,char*) ; 
 scalar_t__ f_closeparen ; 
 TYPE_1__* yankexpr (TYPE_1__**) ; 

PLAN *
paren_squish(PLAN *plan)
{
	PLAN *expr;		/* pointer to next expression */
	PLAN *tail;		/* pointer to tail of result plan */
	PLAN *result;		/* pointer to head of result plan */

	result = tail = NULL;

	/*
	 * the basic idea is to have yankexpr do all our work and just
	 * collect its results together.
	 */
	while ((expr = yankexpr(&plan)) != NULL) {
		/*
		 * if we find an unclaimed ')' it means there is a missing
		 * '(' someplace.
		 */
		if (expr->execute == f_closeparen)
			errx(1, "): no beginning '('");

		/* add the expression to our result plan */
		if (result == NULL)
			tail = result = expr;
		else {
			tail->next = expr;
			tail = expr;
		}
		tail->next = NULL;
	}
	return (result);
}