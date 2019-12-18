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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct worker {int /*<<< orphan*/  cmd; } ;
struct ub_stats_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  fatal_exit (char*,...) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (struct ub_stats_info*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  server_stats_compile (struct worker*,struct ub_stats_info*,int) ; 
 int /*<<< orphan*/  tube_read_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ **,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  worker_cmd_stats ; 
 int /*<<< orphan*/  worker_cmd_stats_noreset ; 
 int /*<<< orphan*/  worker_send_cmd (struct worker*,int /*<<< orphan*/ ) ; 

void server_stats_obtain(struct worker* worker, struct worker* who,
	struct ub_stats_info* s, int reset)
{
	uint8_t *reply = NULL;
	uint32_t len = 0;
	if(worker == who) {
		/* just fill it in */
		server_stats_compile(worker, s, reset);
		return;
	}
	/* communicate over tube */
	verbose(VERB_ALGO, "write stats cmd");
	if(reset)
		worker_send_cmd(who, worker_cmd_stats);
	else 	worker_send_cmd(who, worker_cmd_stats_noreset);
	verbose(VERB_ALGO, "wait for stats reply");
	if(!tube_read_msg(worker->cmd, &reply, &len, 0))
		fatal_exit("failed to read stats over cmd channel");
	if(len != (uint32_t)sizeof(*s))
		fatal_exit("stats on cmd channel wrong length %d %d",
			(int)len, (int)sizeof(*s));
	memcpy(s, reply, (size_t)len);
	free(reply);
}