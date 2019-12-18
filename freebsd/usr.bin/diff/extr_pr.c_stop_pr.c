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
struct pr {scalar_t__ ostdout; scalar_t__ kq; TYPE_1__* e; } ;
struct TYPE_2__ {int data; } ;

/* Variables and functions */
 scalar_t__ STDOUT_FILENO ; 
 scalar_t__ WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 scalar_t__ WIFSIGNALED (int) ; 
 int /*<<< orphan*/  WTERMSIG (int) ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  dup2 (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct pr*) ; 
 int kevent (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdout ; 

void
stop_pr(struct pr *pr)
{
	int wstatus;

	if (pr == NULL)
		return;

	fflush(stdout);
	if (pr->ostdout != STDOUT_FILENO) {
		close(STDOUT_FILENO);
		dup2(pr->ostdout, STDOUT_FILENO);
		close(pr->ostdout);
	}
	if (kevent(pr->kq, NULL, 0, pr->e, 1, NULL) == -1)
		err(2, "kevent");
	wstatus = pr->e[0].data;
	close(pr->kq);
	free(pr);
	if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) != 0)
		errx(2, "pr exited abnormally");
	else if (WIFSIGNALED(wstatus))
		errx(2, "pr killed by signal %d",
		    WTERMSIG(wstatus));
}