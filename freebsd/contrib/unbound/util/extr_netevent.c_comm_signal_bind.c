#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct internal_signal {struct internal_signal* next; int /*<<< orphan*/ * ev; } ;
struct comm_signal {struct internal_signal* ev_signal; TYPE_2__* base; } ;
struct TYPE_4__ {TYPE_1__* eb; } ;
struct TYPE_3__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  comm_signal_callback ; 
 int /*<<< orphan*/  free (struct internal_signal*) ; 
 int /*<<< orphan*/  log_assert (struct comm_signal*) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  ub_event_free (int /*<<< orphan*/ *) ; 
 scalar_t__ ub_signal_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ub_signal_new (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct comm_signal*) ; 

int 
comm_signal_bind(struct comm_signal* comsig, int sig)
{
	struct internal_signal* entry = (struct internal_signal*)calloc(1, 
		sizeof(struct internal_signal));
	if(!entry) {
		log_err("malloc failed");
		return 0;
	}
	log_assert(comsig);
	/* add signal event */
	entry->ev = ub_signal_new(comsig->base->eb->base, sig,
		comm_signal_callback, comsig);
	if(entry->ev == NULL) {
		log_err("Could not create signal event");
		free(entry);
		return 0;
	}
	if(ub_signal_add(entry->ev, NULL) != 0) {
		log_err("Could not add signal handler");
		ub_event_free(entry->ev);
		free(entry);
		return 0;
	}
	/* link into list */
	entry->next = comsig->ev_signal;
	comsig->ev_signal = entry;
	return 1;
}