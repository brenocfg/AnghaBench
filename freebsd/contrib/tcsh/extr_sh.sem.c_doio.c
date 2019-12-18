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
struct command {unsigned long t_dflg; scalar_t__ t_drit; scalar_t__ t_dlef; } ;
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_SYSTEM ; 
 unsigned long F_APPEND ; 
 int /*<<< orphan*/  F_GETFL ; 
 unsigned long F_NOINTERRUPT ; 
 unsigned long F_OVERWRITE ; 
 unsigned long F_PIPEIN ; 
 unsigned long F_PIPEOUT ; 
 unsigned long F_READ ; 
 unsigned long F_REPEAT ; 
 int /*<<< orphan*/  F_SETFL ; 
 unsigned long F_STDERR ; 
 int /*<<< orphan*/  L_XTND ; 
 int OLDSTD ; 
 int O_APPEND ; 
 int O_LARGEFILE ; 
 int O_RDONLY ; 
 int O_WRONLY ; 
 int SHDIAG ; 
 int SHIN ; 
 int SHOUT ; 
 int /*<<< orphan*/  TCSH_IGNORE (int /*<<< orphan*/ ) ; 
 char* _PATH_DEVNULL ; 
 int /*<<< orphan*/  chkclob (char*) ; 
 int /*<<< orphan*/  cleanup_push (char*,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *)) ; 
 int /*<<< orphan*/  cleanup_until (char*) ; 
 int /*<<< orphan*/  close_on_exec (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dcopy (int,int) ; 
 int didfds ; 
 int /*<<< orphan*/  dmove (int,int) ; 
 int /*<<< orphan*/  dup (int) ; 
 int /*<<< orphan*/  errno ; 
 int fcntl (int,int /*<<< orphan*/ ,...) ; 
 scalar_t__ is1atty ; 
 scalar_t__ is2atty ; 
 scalar_t__ isatty (int) ; 
 scalar_t__ isdiagatty ; 
 scalar_t__ isoutatty ; 
 int /*<<< orphan*/  lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ no_clobber ; 
 int /*<<< orphan*/  short2str (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * splicepipe (struct command*,scalar_t__) ; 
 int /*<<< orphan*/  stderror (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 char* strsave (int /*<<< orphan*/ ) ; 
 int tpgrp ; 
 int /*<<< orphan*/  xclose (int) ; 
 int xcreat (char*,int) ; 
 int /*<<< orphan*/  xfree (int /*<<< orphan*/ *) ; 
 int xopen (char*,int) ; 

__attribute__((used)) static void
doio(struct command *t, int *pipein, int *pipeout)
{
    int fd;
    Char *cp;
    unsigned long flags = t->t_dflg;

    if (didfds || (flags & F_REPEAT))
	return;
    if ((flags & F_READ) == 0) {/* F_READ already done */
	if (t->t_dlef) {
	    char *tmp;

	    /*
	     * so < /dev/std{in,out,err} work
	     */
	    (void) dcopy(SHIN, 0);
	    (void) dcopy(SHOUT, 1);
	    (void) dcopy(SHDIAG, 2);
	    cp = splicepipe(t, t->t_dlef);
	    tmp = strsave(short2str(cp));
	    xfree(cp);
	    cleanup_push(tmp, xfree);
	    if ((fd = xopen(tmp, O_RDONLY|O_LARGEFILE)) < 0)
		stderror(ERR_SYSTEM, tmp, strerror(errno));
	    cleanup_until(tmp);
	    /* allow input files larger than 2Gb  */
#ifndef WINNT_NATIVE
	    (void) fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_LARGEFILE);
#endif /*!WINNT_NATIVE*/
	    (void) dmove(fd, 0);
	}
	else if (flags & F_PIPEIN) {
	    xclose(0);
	    TCSH_IGNORE(dup(pipein[0]));
	    xclose(pipein[0]);
	    xclose(pipein[1]);
	}
	else if ((flags & F_NOINTERRUPT) && tpgrp == -1) {
	    xclose(0);
	    (void) xopen(_PATH_DEVNULL, O_RDONLY|O_LARGEFILE);
	}
	else {
	    xclose(0);
	    TCSH_IGNORE(dup(OLDSTD));
#if defined(CLOSE_ON_EXEC) && defined(CLEX_DUPS)
	    /*
	     * PWP: Unlike Bezerkeley 4.3, FIONCLEX for Pyramid is preserved
	     * across dup()s, so we have to UNSET it here or else we get a
	     * command with NO stdin, stdout, or stderr at all (a bad thing
	     * indeed)
	     */
	    (void) close_on_exec(0, 0);
#endif /* CLOSE_ON_EXEC && CLEX_DUPS */
	}
    }
    if (t->t_drit) {
	char *tmp;

	cp = splicepipe(t, t->t_drit);
	tmp = strsave(short2str(cp));
	xfree(cp);
	cleanup_push(tmp, xfree);
	/*
	 * so > /dev/std{out,err} work
	 */
	(void) dcopy(SHOUT, 1);
	(void) dcopy(SHDIAG, 2);
	if ((flags & F_APPEND) != 0) {
#ifdef O_APPEND
	    fd = xopen(tmp, O_WRONLY|O_APPEND|O_LARGEFILE);
#else /* !O_APPEND */
	    fd = xopen(tmp, O_WRONLY|O_LARGEFILE);
	    (void) lseek(fd, (off_t) 0, L_XTND);
#endif /* O_APPEND */
	}
	else
	    fd = 0;
	if ((flags & F_APPEND) == 0 || fd == -1) {
	    if (!(flags & F_OVERWRITE) && no_clobber) {
		if (flags & F_APPEND)
		    stderror(ERR_SYSTEM, tmp, strerror(errno));
		chkclob(tmp);
	    }
	    if ((fd = xcreat(tmp, 0666)) < 0)
		stderror(ERR_SYSTEM, tmp, strerror(errno));
	    /* allow input files larger than 2Gb  */
#ifndef WINNT_NATIVE
	    (void) fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_LARGEFILE);
#endif /*!WINNT_NATIVE*/
	}
	cleanup_until(tmp);
	(void) dmove(fd, 1);
	is1atty = isatty(1);
    }
    else if (flags & F_PIPEOUT) {
	xclose(1);
	TCSH_IGNORE(dup(pipeout[1]));
	is1atty = 0;
    }
    else {
	xclose(1);
	TCSH_IGNORE(dup(SHOUT));
	is1atty = isoutatty;
# if defined(CLOSE_ON_EXEC) && defined(CLEX_DUPS)
	(void) close_on_exec(1, 0);
# endif /* CLOSE_ON_EXEC && CLEX_DUPS */
    }

    xclose(2);
    if (flags & F_STDERR) {
	TCSH_IGNORE(dup(1));
	is2atty = is1atty;
    }
    else {
	TCSH_IGNORE(dup(SHDIAG));
	is2atty = isdiagatty;
# if defined(CLOSE_ON_EXEC) && defined(CLEX_DUPS)
	(void) close_on_exec(2, 0);
# endif /* CLOSE_ON_EXEC && CLEX_DUPS */
    }
    didfds = 1;
}