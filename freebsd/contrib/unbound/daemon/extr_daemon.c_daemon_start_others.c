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
struct TYPE_2__ {int /*<<< orphan*/  cmd; int /*<<< orphan*/  thr_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  log_assert (struct daemon*) ; 
 int /*<<< orphan*/  thread_start ; 
 int /*<<< orphan*/  tube_close_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ub_thread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
daemon_start_others(struct daemon* daemon)
{
	int i;
	log_assert(daemon);
	verbose(VERB_ALGO, "start threads");
	/* skip i=0, is this thread */
	for(i=1; i<daemon->num; i++) {
		ub_thread_create(&daemon->workers[i]->thr_id,
			thread_start, daemon->workers[i]);
#ifdef THREADS_DISABLED
		/* close pipe end of child */
		tube_close_read(daemon->workers[i]->cmd);
#endif /* no threads */
	}
}