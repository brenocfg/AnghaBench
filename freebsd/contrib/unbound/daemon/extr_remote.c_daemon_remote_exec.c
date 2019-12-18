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
typedef  int /*<<< orphan*/  uint32_t ;
struct worker {int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  execute_cmd (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,struct worker*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  tube_read_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,char*) ; 

void 
daemon_remote_exec(struct worker* worker)
{
	/* read the cmd string */
	uint8_t* msg = NULL;
	uint32_t len = 0;
	if(!tube_read_msg(worker->cmd, &msg, &len, 0)) {
		log_err("daemon_remote_exec: tube_read_msg failed");
		return;
	}
	verbose(VERB_ALGO, "remote exec distributed: %s", (char*)msg);
	execute_cmd(NULL, NULL, (char*)msg, worker);
	free(msg);
}