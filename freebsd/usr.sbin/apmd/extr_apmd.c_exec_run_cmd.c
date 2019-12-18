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
struct event_cmd {int name; TYPE_1__* op; struct event_cmd* next; } ;
struct TYPE_2__ {int (* act ) (struct event_cmd*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  LOG_NOTICE ; 
 int /*<<< orphan*/  assert (int (*) (struct event_cmd*)) ; 
 int stub1 (struct event_cmd*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ verbose ; 

int
exec_run_cmd(struct event_cmd *p)
{
	int status = 0;

	for (; p; p = p->next) {
		assert(p->op->act);
		if (verbose)
			syslog(LOG_INFO, "action: %s", p->name);
		status = p->op->act(p);
		if (status) {
			syslog(LOG_NOTICE, "command finished with %d\n", status);
			break;
		}
	}
	return status;
}