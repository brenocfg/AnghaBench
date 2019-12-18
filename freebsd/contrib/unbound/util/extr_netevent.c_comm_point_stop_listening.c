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
struct comm_point {TYPE_1__* ev; int /*<<< orphan*/  fd; } ;
struct TYPE_2__ {int /*<<< orphan*/  ev; } ;

/* Variables and functions */
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  log_err (char*) ; 
 scalar_t__ ub_event_del (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void 
comm_point_stop_listening(struct comm_point* c)
{
	verbose(VERB_ALGO, "comm point stop listening %d", c->fd);
	if(ub_event_del(c->ev->ev) != 0) {
		log_err("event_del error to stoplisten");
	}
}