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
struct internal_signal {int /*<<< orphan*/  ev; struct internal_signal* next; struct internal_signal* ev_signal; } ;
struct comm_signal {int /*<<< orphan*/  ev; struct comm_signal* next; struct comm_signal* ev_signal; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct internal_signal*) ; 
 int /*<<< orphan*/  ub_event_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ub_signal_del (int /*<<< orphan*/ ) ; 

void 
comm_signal_delete(struct comm_signal* comsig)
{
	struct internal_signal* p, *np;
	if(!comsig)
		return;
	p=comsig->ev_signal;
	while(p) {
		np = p->next;
		ub_signal_del(p->ev);
		ub_event_free(p->ev);
		free(p);
		p = np;
	}
	free(comsig);
}