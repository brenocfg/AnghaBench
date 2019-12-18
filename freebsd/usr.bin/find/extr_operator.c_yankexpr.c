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
 scalar_t__ f_closeparen ; 
 scalar_t__ f_expr ; 
 scalar_t__ f_openparen ; 
 TYPE_1__* yanknode (TYPE_1__**) ; 

__attribute__((used)) static PLAN *
yankexpr(PLAN **planp)
{
	PLAN *next;		/* temp node holding subexpression results */
	PLAN *node;		/* pointer to returned node or expression */
	PLAN *tail;		/* pointer to tail of subplan */
	PLAN *subplan;		/* pointer to head of ( ) expression */

	/* first pull the top node from the plan */
	if ((node = yanknode(planp)) == NULL)
		return (NULL);

	/*
	 * If the node is an '(' then we recursively slurp up expressions
	 * until we find its associated ')'.  If it's a closing paren we
	 * just return it and unwind our recursion; all other nodes are
	 * complete expressions, so just return them.
	 */
	if (node->execute == f_openparen)
		for (tail = subplan = NULL;;) {
			if ((next = yankexpr(planp)) == NULL)
				errx(1, "(: missing closing ')'");
			/*
			 * If we find a closing ')' we store the collected
			 * subplan in our '(' node and convert the node to
			 * a f_expr.  The ')' we found is ignored.  Otherwise,
			 * we just continue to add whatever we get to our
			 * subplan.
			 */
			if (next->execute == f_closeparen) {
				if (subplan == NULL)
					errx(1, "(): empty inner expression");
				node->p_data[0] = subplan;
				node->execute = f_expr;
				break;
			} else {
				if (subplan == NULL)
					tail = subplan = next;
				else {
					tail->next = next;
					tail = next;
				}
				tail->next = NULL;
			}
		}
	return (node);
}