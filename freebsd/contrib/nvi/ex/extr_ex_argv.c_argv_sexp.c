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
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  SCR ;
typedef  int /*<<< orphan*/  FILE ;
typedef  char CHAR_T ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_SPACE_GOTOW (int /*<<< orphan*/ *,char*,size_t,size_t) ; 
 int EOF ; 
 int GETC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INT2CHAR (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  M_ERR ; 
 int /*<<< orphan*/  M_SYSERR ; 
 scalar_t__ O_ISSET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  O_SECURE ; 
 int /*<<< orphan*/  O_SHELL ; 
 char* O_STR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int STDERR_FILENO ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  STRLEN (char*) ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  cmdskip (char) ; 
 int /*<<< orphan*/  dup2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  execl (char*,char*,char*,char*,char*) ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msgq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msgq_str (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ pipe (int*) ; 
 scalar_t__ proc_wait (int /*<<< orphan*/ *,long,char*,int,int /*<<< orphan*/ ) ; 
 char* strrchr (char*,char) ; 
 scalar_t__ vfork () ; 

__attribute__((used)) static int
argv_sexp(SCR *sp, CHAR_T **bpp, size_t *blenp, size_t *lenp)
{
	enum { SEXP_ERR, SEXP_EXPANSION_ERR, SEXP_OK } rval;
	FILE *ifp;
	pid_t pid;
	size_t blen, len;
	int ch, std_output[2];
	CHAR_T *bp, *p;
	char *sh, *sh_path;
	char *np;
	size_t nlen;

	/* Secure means no shell access. */
	if (O_ISSET(sp, O_SECURE)) {
		msgq(sp, M_ERR,
"289|Shell expansions not supported when the secure edit option is set");
		return (1);
	}

	sh_path = O_STR(sp, O_SHELL);
	if ((sh = strrchr(sh_path, '/')) == NULL)
		sh = sh_path;
	else
		++sh;

	/* Local copies of the buffer variables. */
	bp = *bpp;
	blen = *blenp;

	/*
	 * There are two different processes running through this code, named
	 * the utility (the shell) and the parent. The utility reads standard
	 * input and writes standard output and standard error output.  The
	 * parent writes to the utility, reads its standard output and ignores
	 * its standard error output.  Historically, the standard error output
	 * was discarded by vi, as it produces a lot of noise when file patterns
	 * don't match.
	 *
	 * The parent reads std_output[0], and the utility writes std_output[1].
	 */
	ifp = NULL;
	std_output[0] = std_output[1] = -1;
	if (pipe(std_output) < 0) {
		msgq(sp, M_SYSERR, "pipe");
		return (1);
	}
	if ((ifp = fdopen(std_output[0], "r")) == NULL) {
		msgq(sp, M_SYSERR, "fdopen");
		goto err;
	}

	/*
	 * Do the minimal amount of work possible, the shell is going to run
	 * briefly and then exit.  We sincerely hope.
	 */
	switch (pid = vfork()) {
	case -1:			/* Error. */
		msgq(sp, M_SYSERR, "vfork");
err:		if (ifp != NULL)
			(void)fclose(ifp);
		else if (std_output[0] != -1)
			close(std_output[0]);
		if (std_output[1] != -1)
			close(std_output[0]);
		return (1);
	case 0:				/* Utility. */
		/* Redirect stdout to the write end of the pipe. */
		(void)dup2(std_output[1], STDOUT_FILENO);

		/* Close the utility's file descriptors. */
		(void)close(std_output[0]);
		(void)close(std_output[1]);
		(void)close(STDERR_FILENO);

		/*
		 * XXX
		 * Assume that all shells have -c.
		 */
		INT2CHAR(sp, bp, STRLEN(bp)+1, np, nlen);
		execl(sh_path, sh, "-c", np, (char *)NULL);
		msgq_str(sp, M_SYSERR, sh_path, "118|Error: execl: %s");
		_exit(127);
	default:			/* Parent. */
		/* Close the pipe ends the parent won't use. */
		(void)close(std_output[1]);
		break;
	}

	/*
	 * Copy process standard output into a buffer.
	 *
	 * !!!
	 * Historic vi apparently discarded leading \n and \r's from
	 * the shell output stream.  We don't on the grounds that any
	 * shell that does that is broken.
	 */
	for (p = bp, len = 0, ch = EOF;
	    (ch = GETC(ifp)) != EOF; *p++ = ch, blen-=sizeof(CHAR_T), ++len)
		if (blen < 5) {
			ADD_SPACE_GOTOW(sp, bp, *blenp, *blenp * 2);
			p = bp + len;
			blen = *blenp - len;
		}

	/* Delete the final newline, nul terminate the string. */
	if (p > bp && (p[-1] == '\n' || p[-1] == '\r')) {
		--p;
		--len;
	}
	*p = '\0';
	*lenp = len;
	*bpp = bp;		/* *blenp is already updated. */

	if (ferror(ifp))
		goto ioerr;
	if (fclose(ifp)) {
ioerr:		msgq_str(sp, M_ERR, sh, "119|I/O error: %s");
alloc_err:	rval = SEXP_ERR;
	} else
		rval = SEXP_OK;

	/*
	 * Wait for the process.  If the shell process fails (e.g., "echo $q"
	 * where q wasn't a defined variable) or if the returned string has
	 * no characters or only blank characters, (e.g., "echo $5"), complain
	 * that the shell expansion failed.  We can't know for certain that's
	 * the error, but it's a good guess, and it matches historic practice.
	 * This won't catch "echo foo_$5", but that's not a common error and
	 * historic vi didn't catch it either.
	 */
	if (proc_wait(sp, (long)pid, sh, 1, 0))
		rval = SEXP_EXPANSION_ERR;

	for (p = bp; len; ++p, --len)
		if (!cmdskip(*p))
			break;
	if (len == 0)
		rval = SEXP_EXPANSION_ERR;

	if (rval == SEXP_EXPANSION_ERR)
		msgq(sp, M_ERR, "304|Shell expansion failed");

	return (rval == SEXP_OK ? 0 : 1);
}