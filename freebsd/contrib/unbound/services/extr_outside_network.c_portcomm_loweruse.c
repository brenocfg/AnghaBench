#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct port_if {size_t inuse; size_t avail_total; TYPE_1__** out; int /*<<< orphan*/ * avail_ports; } ;
struct port_comm {scalar_t__ num_outstanding; size_t index; struct port_comm* next; int /*<<< orphan*/  number; struct port_if* pif; int /*<<< orphan*/  cp; } ;
struct outside_network {struct port_comm* unused_fds; } ;
struct TYPE_2__ {size_t index; } ;

/* Variables and functions */
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  comm_point_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_assert (int) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
portcomm_loweruse(struct outside_network* outnet, struct port_comm* pc)
{
	struct port_if* pif;
	pc->num_outstanding--;
	if(pc->num_outstanding > 0) {
		return;
	}
	/* close it and replace in unused list */
	verbose(VERB_ALGO, "close of port %d", pc->number);
	comm_point_close(pc->cp);
	pif = pc->pif;
	log_assert(pif->inuse > 0);
	pif->avail_ports[pif->avail_total - pif->inuse] = pc->number;
	pif->inuse--;
	pif->out[pc->index] = pif->out[pif->inuse];
	pif->out[pc->index]->index = pc->index;
	pc->next = outnet->unused_fds;
	outnet->unused_fds = pc;
}