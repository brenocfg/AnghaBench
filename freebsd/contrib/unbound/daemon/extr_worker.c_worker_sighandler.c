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
struct worker {int need_to_exit; int /*<<< orphan*/  base; } ;

/* Variables and functions */
#define  SIGHUP 131 
#define  SIGINT 130 
#define  SIGQUIT 129 
#define  SIGTERM 128 
 int /*<<< orphan*/  comm_base_exit (int /*<<< orphan*/ ) ; 

void 
worker_sighandler(int sig, void* arg)
{
	/* note that log, print, syscalls here give race conditions. 
	 * And cause hangups if the log-lock is held by the application. */
	struct worker* worker = (struct worker*)arg;
	switch(sig) {
#ifdef SIGHUP
		case SIGHUP:
			comm_base_exit(worker->base);
			break;
#endif
		case SIGINT:
			worker->need_to_exit = 1;
			comm_base_exit(worker->base);
			break;
#ifdef SIGQUIT
		case SIGQUIT:
			worker->need_to_exit = 1;
			comm_base_exit(worker->base);
			break;
#endif
		case SIGTERM:
			worker->need_to_exit = 1;
			comm_base_exit(worker->base);
			break;
		default:
			/* unknown signal, ignored */
			break;
	}
}