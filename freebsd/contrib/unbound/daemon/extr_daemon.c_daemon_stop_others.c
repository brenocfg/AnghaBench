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
struct daemon {int num; TYPE_1__** workers; } ;
struct TYPE_2__ {int /*<<< orphan*/  thr_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  log_assert (struct daemon*) ; 
 int /*<<< orphan*/  ub_thread_join (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  worker_cmd_quit ; 
 int /*<<< orphan*/  worker_send_cmd (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
daemon_stop_others(struct daemon* daemon)
{
	int i;
	log_assert(daemon);
	verbose(VERB_ALGO, "stop threads");
	/* skip i=0, is this thread */
	/* use i=0 buffer for sending cmds; because we are #0 */
	for(i=1; i<daemon->num; i++) {
		worker_send_cmd(daemon->workers[i], worker_cmd_quit);
	}
	/* wait for them to quit */
	for(i=1; i<daemon->num; i++) {
		/* join it to make sure its dead */
		verbose(VERB_ALGO, "join %d", i);
		ub_thread_join(daemon->workers[i]->thr_id);
		verbose(VERB_ALGO, "join success %d", i);
	}
}