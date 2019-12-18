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
typedef  scalar_t__ pid_t ;
struct TYPE_2__ {int /*<<< orphan*/  client_pid; int /*<<< orphan*/ ** sync_fd; } ;

/* Variables and functions */
 int EXIT_SUCCESS ; 
 size_t SYNC_CLIENT ; 
 size_t SYNC_RECV ; 
 size_t SYNC_SEND ; 
 size_t SYNC_SERVER ; 
 scalar_t__ WCOREDUMP (int) ; 
 int WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 scalar_t__ WIFSIGNALED (int) ; 
 int /*<<< orphan*/  WTERMSIG (int) ; 
 scalar_t__ close (int /*<<< orphan*/ ) ; 
 TYPE_1__ uc_cfg ; 
 int /*<<< orphan*/  uc_dbgmsg (char*) ; 
 int /*<<< orphan*/  uc_logmsg (char*) ; 
 int /*<<< orphan*/  uc_logmsgx (char*,...) ; 
 scalar_t__ waitpid (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

int
uc_client_wait(void)
{
	int status;
	pid_t pid;

	uc_dbgmsg("waiting for client");

	if (close(uc_cfg.sync_fd[SYNC_SERVER][SYNC_RECV]) < 0 ||
	    close(uc_cfg.sync_fd[SYNC_CLIENT][SYNC_SEND]) < 0) {
		uc_logmsg("client_wait: close");
		return (-1);
	}

	pid = waitpid(uc_cfg.client_pid, &status, 0);
	if (pid == (pid_t)-1) {
		uc_logmsg("client_wait: waitpid");
		return (-1);
	}

	if (WIFEXITED(status)) {
		if (WEXITSTATUS(status) != EXIT_SUCCESS) {
			uc_logmsgx("client exit status is %d",
			    WEXITSTATUS(status));
			return (-WEXITSTATUS(status));
		}
	} else {
		if (WIFSIGNALED(status))
			uc_logmsgx("abnormal termination of client, signal %d%s",
			    WTERMSIG(status), WCOREDUMP(status) ?
			    " (core file generated)" : "");
		else
			uc_logmsgx("termination of client, unknown status");
		return (-1);
	}

	return (0);
}