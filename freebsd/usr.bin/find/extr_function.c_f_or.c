#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int (* execute ) (TYPE_1__*,int /*<<< orphan*/ *) ;struct TYPE_5__* next; struct TYPE_5__** p_data; } ;
typedef  TYPE_1__ PLAN ;
typedef  int /*<<< orphan*/  FTSENT ;

/* Variables and functions */
 int stub1 (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int stub2 (TYPE_1__*,int /*<<< orphan*/ *) ; 

int
f_or(PLAN *plan, FTSENT *entry)
{
	PLAN *p;
	int state = 0;

	for (p = plan->p_data[0];
	    p && (state = (p->execute)(p, entry)); p = p->next);

	if (state)
		return 1;

	for (p = plan->p_data[1];
	    p && (state = (p->execute)(p, entry)); p = p->next);
	return state;
}