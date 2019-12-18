#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int pid_t ;
struct TYPE_6__ {char* fts_path; } ;
struct TYPE_5__ {int flags; size_t e_ppos; size_t e_pbnum; scalar_t__* e_len; scalar_t__ e_psize; size_t e_pnummax; scalar_t__ e_psizemax; scalar_t__ e_pbsize; int /*<<< orphan*/ ** e_argv; int /*<<< orphan*/ * e_orig; } ;
typedef  TYPE_1__ PLAN ;
typedef  TYPE_2__ FTSENT ;

/* Variables and functions */
 int FTS_NOCHDIR ; 
 int F_EXECDIR ; 
 int F_EXECPLUS ; 
 int F_NEEDOK ; 
 int /*<<< orphan*/  WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  brace_subst (int /*<<< orphan*/ ,int /*<<< orphan*/ **,char*,scalar_t__) ; 
 int /*<<< orphan*/  dotfd ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  execvp (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int exitstatus ; 
 int /*<<< orphan*/  fchdir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int fork () ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int ftsoptions ; 
 int /*<<< orphan*/  queryuser (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/ * strdup (char*) ; 
 scalar_t__ strlen (char*) ; 
 char* strrchr (char*,char) ; 
 int waitpid (int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*,...) ; 

int
f_exec(PLAN *plan, FTSENT *entry)
{
	int cnt;
	pid_t pid;
	int status;
	char *file;

	if (entry == NULL && plan->flags & F_EXECPLUS) {
		if (plan->e_ppos == plan->e_pbnum)
			return (1);
		plan->e_argv[plan->e_ppos] = NULL;
		goto doexec;
	}

	/* XXX - if file/dir ends in '/' this will not work -- can it? */
	if ((plan->flags & F_EXECDIR) && \
	    (file = strrchr(entry->fts_path, '/')))
		file++;
	else
		file = entry->fts_path;

	if (plan->flags & F_EXECPLUS) {
		if ((plan->e_argv[plan->e_ppos] = strdup(file)) == NULL)
			err(1, NULL);
		plan->e_len[plan->e_ppos] = strlen(file);
		plan->e_psize += plan->e_len[plan->e_ppos];
		if (++plan->e_ppos < plan->e_pnummax &&
		    plan->e_psize < plan->e_psizemax)
			return (1);
		plan->e_argv[plan->e_ppos] = NULL;
	} else {
		for (cnt = 0; plan->e_argv[cnt]; ++cnt)
			if (plan->e_len[cnt])
				brace_subst(plan->e_orig[cnt],
				    &plan->e_argv[cnt], file,
				    plan->e_len[cnt]);
	}

doexec:	if ((plan->flags & F_NEEDOK) && !queryuser(plan->e_argv))
		return 0;

	/* make sure find output is interspersed correctly with subprocesses */
	fflush(stdout);
	fflush(stderr);

	switch (pid = fork()) {
	case -1:
		err(1, "fork");
		/* NOTREACHED */
	case 0:
		/* change dir back from where we started */
		if (!(plan->flags & F_EXECDIR) &&
		    !(ftsoptions & FTS_NOCHDIR) && fchdir(dotfd)) {
			warn("chdir");
			_exit(1);
		}
		execvp(plan->e_argv[0], plan->e_argv);
		warn("%s", plan->e_argv[0]);
		_exit(1);
	}
	if (plan->flags & F_EXECPLUS) {
		while (--plan->e_ppos >= plan->e_pbnum)
			free(plan->e_argv[plan->e_ppos]);
		plan->e_ppos = plan->e_pbnum;
		plan->e_psize = plan->e_pbsize;
	}
	pid = waitpid(pid, &status, 0);
	if (pid != -1 && WIFEXITED(status) && !WEXITSTATUS(status))
		return (1);
	if (plan->flags & F_EXECPLUS) {
		exitstatus = 1;
		return (1);
	}
	return (0);
}