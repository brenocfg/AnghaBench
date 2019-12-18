#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {TYPE_1__* (* create ) (TYPE_2__*,char***) ;} ;
struct TYPE_20__ {struct TYPE_20__* next; } ;
typedef  TYPE_1__ PLAN ;
typedef  TYPE_2__ OPTION ;

/* Variables and functions */
 TYPE_1__* find_create (char***) ; 
 int /*<<< orphan*/  isoutput ; 
 TYPE_2__* lookup_option (char*) ; 
 TYPE_1__* not_squish (TYPE_1__*) ; 
 TYPE_1__* or_squish (TYPE_1__*) ; 
 TYPE_1__* paren_squish (TYPE_1__*) ; 
 TYPE_1__* stub1 (TYPE_2__*,char***) ; 
 TYPE_1__* stub2 (TYPE_2__*,char***) ; 
 TYPE_1__* stub3 (TYPE_2__*,char***) ; 
 TYPE_1__* stub4 (TYPE_2__*,char***) ; 

PLAN *
find_formplan(char *argv[])
{
	PLAN *plan, *tail, *new;

	/*
	 * for each argument in the command line, determine what kind of node
	 * it is, create the appropriate node type and add the new plan node
	 * to the end of the existing plan.  The resulting plan is a linked
	 * list of plan nodes.  For example, the string:
	 *
	 *	% find . -name foo -newer bar -print
	 *
	 * results in the plan:
	 *
	 *	[-name foo]--> [-newer bar]--> [-print]
	 *
	 * in this diagram, `[-name foo]' represents the plan node generated
	 * by c_name() with an argument of foo and `-->' represents the
	 * plan->next pointer.
	 */
	for (plan = tail = NULL; *argv;) {
		if (!(new = find_create(&argv)))
			continue;
		if (plan == NULL)
			tail = plan = new;
		else {
			tail->next = new;
			tail = new;
		}
	}

	/*
	 * if the user didn't specify one of -print, -ok or -exec, then -print
	 * is assumed so we bracket the current expression with parens, if
	 * necessary, and add a -print node on the end.
	 */
	if (!isoutput) {
		OPTION *p;
		char **argv1 = 0;

		if (plan == NULL) {
			p = lookup_option("-print");
			new = (p->create)(p, &argv1);
			tail = plan = new;
		} else {
			p = lookup_option("(");
			new = (p->create)(p, &argv1);
			new->next = plan;
			plan = new;
			p = lookup_option(")");
			new = (p->create)(p, &argv1);
			tail->next = new;
			tail = new;
			p = lookup_option("-print");
			new = (p->create)(p, &argv1);
			tail->next = new;
			tail = new;
		}
	}

	/*
	 * the command line has been completely processed into a search plan
	 * except for the (, ), !, and -o operators.  Rearrange the plan so
	 * that the portions of the plan which are affected by the operators
	 * are moved into operator nodes themselves.  For example:
	 *
	 *	[!]--> [-name foo]--> [-print]
	 *
	 * becomes
	 *
	 *	[! [-name foo] ]--> [-print]
	 *
	 * and
	 *
	 *	[(]--> [-depth]--> [-name foo]--> [)]--> [-print]
	 *
	 * becomes
	 *
	 *	[expr [-depth]-->[-name foo] ]--> [-print]
	 *
	 * operators are handled in order of precedence.
	 */

	plan = paren_squish(plan);		/* ()'s */
	plan = not_squish(plan);		/* !'s */
	plan = or_squish(plan);			/* -o's */
	return (plan);
}