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
struct rmid_read {int evtid; int first; scalar_t__ val; struct rdt_domain* d; struct rdtgroup* rgrp; } ;
struct rdtgroup {int dummy; } ;
struct rdt_domain {int /*<<< orphan*/  cpu_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  mon_event_count ; 
 int /*<<< orphan*/  smp_call_function_any (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct rmid_read*,int) ; 

void mon_event_read(struct rmid_read *rr, struct rdt_domain *d,
		    struct rdtgroup *rdtgrp, int evtid, int first)
{
	/*
	 * setup the parameters to send to the IPI to read the data.
	 */
	rr->rgrp = rdtgrp;
	rr->evtid = evtid;
	rr->d = d;
	rr->val = 0;
	rr->first = first;

	smp_call_function_any(&d->cpu_mask, mon_event_count, rr, 1);
}