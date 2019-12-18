#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* dname; int to_fd; int from_fd; void* from_fp; void* to_fp; int /*<<< orphan*/  pid; } ;
typedef  int /*<<< orphan*/  SCR ;
typedef  TYPE_1__ CSC ;

/* Variables and functions */
 int /*<<< orphan*/  CSCOPE_CMD_FMT ; 
 int /*<<< orphan*/  M_SYSERR ; 
 int /*<<< orphan*/  STDERR_FILENO ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  _PATH_BSHELL ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  asprintf (char**,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dup2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  execl (int /*<<< orphan*/ ,char*,char*,char*,char*) ; 
 void* fdopen (int,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  msgq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msgq_str (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ pipe (int*) ; 
 char* quote (char*) ; 
 int /*<<< orphan*/  vfork () ; 

__attribute__((used)) static int
run_cscope(SCR *sp, CSC *csc, char *dbname)
{
	int to_cs[2], from_cs[2];
	char *cmd;

	/*
	 * Cscope reads from to_cs[0] and writes to from_cs[1]; vi reads from
	 * from_cs[0] and writes to to_cs[1].
	 */
	to_cs[0] = to_cs[1] = from_cs[0] = from_cs[1] = -1;
	if (pipe(to_cs) < 0 || pipe(from_cs) < 0) {
		msgq(sp, M_SYSERR, "pipe");
		goto err;
	}
	switch (csc->pid = vfork()) {
		char *dn, *dbn;
	case -1:
		msgq(sp, M_SYSERR, "vfork");
err:		if (to_cs[0] != -1)
			(void)close(to_cs[0]);
		if (to_cs[1] != -1)
			(void)close(to_cs[1]);
		if (from_cs[0] != -1)
			(void)close(from_cs[0]);
		if (from_cs[1] != -1)
			(void)close(from_cs[1]);
		return (1);
	case 0:				/* child: run cscope. */
		(void)dup2(to_cs[0], STDIN_FILENO);
		(void)dup2(from_cs[1], STDOUT_FILENO);
		(void)dup2(from_cs[1], STDERR_FILENO);

		/* Close unused file descriptors. */
		(void)close(to_cs[1]);
		(void)close(from_cs[0]);

		/* Run the cscope command. */
#define	CSCOPE_CMD_FMT		"cd %s && exec cscope -dl -f %s"
		if ((dn = quote(csc->dname)) == NULL)
			goto nomem;
		if ((dbn = quote(dbname)) == NULL) {
			free(dn);
			goto nomem;
		}
		(void)asprintf(&cmd, CSCOPE_CMD_FMT, dn, dbn);
		free(dbn);
		free(dn);
		if (cmd == NULL) {
nomem:			msgq(sp, M_SYSERR, NULL);
			_exit (1);
		}
		(void)execl(_PATH_BSHELL, "sh", "-c", cmd, (char *)NULL);
		msgq_str(sp, M_SYSERR, cmd, "execl: %s");
		free(cmd);
		_exit (127);
		/* NOTREACHED */
	default:			/* parent. */
		/* Close unused file descriptors. */
		(void)close(to_cs[0]);
		(void)close(from_cs[1]);

		/*
		 * Save the file descriptors for later duplication, and
		 * reopen as streams.
		 */
		csc->to_fd = to_cs[1];
		csc->to_fp = fdopen(to_cs[1], "w");
		csc->from_fd = from_cs[0];
		csc->from_fp = fdopen(from_cs[0], "r");
		break;
	}
	return (0);
}