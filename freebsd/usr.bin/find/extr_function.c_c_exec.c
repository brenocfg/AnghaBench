#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int flags; int /*<<< orphan*/  name; } ;
struct TYPE_8__ {int flags; int e_ppos; int e_pbnum; int e_pnummax; long e_psizemax; int e_pbsize; char** e_argv; char** e_orig; int* e_len; int e_psize; struct TYPE_8__* e_next; } ;
typedef  TYPE_1__ PLAN ;
typedef  TYPE_2__ OPTION ;

/* Variables and functions */
 int FTS_NOCHDIR ; 
 int F_EXECDIR ; 
 int F_EXECPLUS ; 
 int MAXPATHLEN ; 
 long _POSIX_ARG_MAX ; 
 int /*<<< orphan*/  _SC_ARG_MAX ; 
 char** environ ; 
 int /*<<< orphan*/  err (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int ftsoptions ; 
 int isoutput ; 
 TYPE_1__* lastexecplus ; 
 void* malloc (int) ; 
 TYPE_1__* palloc (TYPE_2__*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char*) ; 
 long sysconf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*) ; 

PLAN *
c_exec(OPTION *option, char ***argvp)
{
	PLAN *new;			/* node returned */
	long argmax;
	int cnt, i;
	char **argv, **ap, **ep, *p;

	/* This would defeat -execdir's intended security. */
	if (option->flags & F_EXECDIR && ftsoptions & FTS_NOCHDIR)
		errx(1, "%s: forbidden when the current directory cannot be opened",
		    "-execdir");

	/* XXX - was in c_execdir, but seems unnecessary!?
	ftsoptions &= ~FTS_NOSTAT;
	*/
	isoutput = 1;

	/* XXX - this is a change from the previous coding */
	new = palloc(option);

	for (ap = argv = *argvp;; ++ap) {
		if (!*ap)
			errx(1,
			    "%s: no terminating \";\" or \"+\"", option->name);
		if (**ap == ';')
			break;
		if (**ap == '+' && ap != argv && strcmp(*(ap - 1), "{}") == 0) {
			new->flags |= F_EXECPLUS;
			break;
		}
	}

	if (ap == argv)
		errx(1, "%s: no command specified", option->name);

	cnt = ap - *argvp + 1;
	if (new->flags & F_EXECPLUS) {
		new->e_ppos = new->e_pbnum = cnt - 2;
		if ((argmax = sysconf(_SC_ARG_MAX)) == -1) {
			warn("sysconf(_SC_ARG_MAX)");
			argmax = _POSIX_ARG_MAX;
		}
		argmax -= 1024;
		for (ep = environ; *ep != NULL; ep++)
			argmax -= strlen(*ep) + 1 + sizeof(*ep);
		argmax -= 1 + sizeof(*ep);
		/*
		 * Ensure that -execdir ... {} + does not mix files
		 * from different directories in one invocation.
		 * Files from the same directory should be handled
		 * in one invocation but there is no code for it.
		 */
		new->e_pnummax = new->flags & F_EXECDIR ? 1 : argmax / 16;
		argmax -= sizeof(char *) * new->e_pnummax;
		if (argmax <= 0)
			errx(1, "no space for arguments");
		new->e_psizemax = argmax;
		new->e_pbsize = 0;
		cnt += new->e_pnummax + 1;
		new->e_next = lastexecplus;
		lastexecplus = new;
	}
	if ((new->e_argv = malloc(cnt * sizeof(char *))) == NULL)
		err(1, NULL);
	if ((new->e_orig = malloc(cnt * sizeof(char *))) == NULL)
		err(1, NULL);
	if ((new->e_len = malloc(cnt * sizeof(int))) == NULL)
		err(1, NULL);

	for (argv = *argvp, cnt = 0; argv < ap; ++argv, ++cnt) {
		new->e_orig[cnt] = *argv;
		if (new->flags & F_EXECPLUS)
			new->e_pbsize += strlen(*argv) + 1;
		for (p = *argv; *p; ++p)
			if (!(new->flags & F_EXECPLUS) && p[0] == '{' &&
			    p[1] == '}') {
				if ((new->e_argv[cnt] =
				    malloc(MAXPATHLEN)) == NULL)
					err(1, NULL);
				new->e_len[cnt] = MAXPATHLEN;
				break;
			}
		if (!*p) {
			new->e_argv[cnt] = *argv;
			new->e_len[cnt] = 0;
		}
	}
	if (new->flags & F_EXECPLUS) {
		new->e_psize = new->e_pbsize;
		cnt--;
		for (i = 0; i < new->e_pnummax; i++) {
			new->e_argv[cnt] = NULL;
			new->e_len[cnt] = 0;
			cnt++;
		}
		argv = ap;
		goto done;
	}
	new->e_argv[cnt] = new->e_orig[cnt] = NULL;

done:	*argvp = argv + 1;
	return new;
}