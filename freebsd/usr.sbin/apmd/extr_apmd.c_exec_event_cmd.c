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
struct event_config {scalar_t__ rejectable; int /*<<< orphan*/  cmdlist; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  event_cmd_reject_act (int /*<<< orphan*/ *) ; 
 int exec_run_cmd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 

int
exec_event_cmd(struct event_config *ev)
{
	int status = 0;

	status = exec_run_cmd(ev->cmdlist);
	if (status && ev->rejectable) {
		syslog(LOG_ERR, "canceled");
		event_cmd_reject_act(NULL);
	}
	return status;
}