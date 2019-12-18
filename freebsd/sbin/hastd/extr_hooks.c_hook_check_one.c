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
struct hookproc {int /*<<< orphan*/  hp_comm; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 scalar_t__ WIFSIGNALED (int) ; 
 int WTERMSIG (int) ; 
 struct hookproc* hook_find (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hook_free (struct hookproc*) ; 
 int /*<<< orphan*/  hook_remove (struct hookproc*) ; 
 int /*<<< orphan*/  hookprocs_lock ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pjdlog_debug (int,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  pjdlog_error (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void
hook_check_one(pid_t pid, int status)
{
	struct hookproc *hp;

	mtx_lock(&hookprocs_lock);
	hp = hook_find(pid);
	if (hp == NULL) {
		mtx_unlock(&hookprocs_lock);
		pjdlog_debug(1, "Unknown process pid=%u", pid);
		return;
	}
	hook_remove(hp);
	mtx_unlock(&hookprocs_lock);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
		pjdlog_debug(1, "Hook exited gracefully (pid=%u, cmd=[%s]).",
		    pid, hp->hp_comm);
	} else if (WIFSIGNALED(status)) {
		pjdlog_error("Hook was killed (pid=%u, signal=%d, cmd=[%s]).",
		    pid, WTERMSIG(status), hp->hp_comm);
	} else {
		pjdlog_error("Hook exited ungracefully (pid=%u, exitcode=%d, cmd=[%s]).",
		    pid, WIFEXITED(status) ? WEXITSTATUS(status) : -1,
		    hp->hp_comm);
	}
	hook_free(hp);
}