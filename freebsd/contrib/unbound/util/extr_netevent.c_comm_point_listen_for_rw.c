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
struct comm_point {int /*<<< orphan*/  timeout; TYPE_1__* ev; int /*<<< orphan*/  fd; } ;
struct TYPE_2__ {int /*<<< orphan*/  ev; } ;

/* Variables and functions */
 int UB_EV_READ ; 
 int UB_EV_WRITE ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  log_err (char*) ; 
 scalar_t__ ub_event_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ub_event_add_bits (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ub_event_del (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ub_event_del_bits (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 

void comm_point_listen_for_rw(struct comm_point* c, int rd, int wr)
{
	verbose(VERB_ALGO, "comm point listen_for_rw %d %d", c->fd, wr);
	if(ub_event_del(c->ev->ev) != 0) {
		log_err("event_del error to cplf");
	}
	ub_event_del_bits(c->ev->ev, UB_EV_READ|UB_EV_WRITE);
	if(rd) ub_event_add_bits(c->ev->ev, UB_EV_READ);
	if(wr) ub_event_add_bits(c->ev->ev, UB_EV_WRITE);
	if(ub_event_add(c->ev->ev, c->timeout) != 0) {
		log_err("event_add failed. in cplf.");
	}
}