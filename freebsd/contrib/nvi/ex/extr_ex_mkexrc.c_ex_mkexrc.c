#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct stat {int dummy; } ;
struct TYPE_5__ {int argc; int /*<<< orphan*/  iflags; TYPE_1__** argv; } ;
struct TYPE_4__ {int /*<<< orphan*/  len; int /*<<< orphan*/  bp; } ;
typedef  int /*<<< orphan*/  SCR ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_2__ EXCMD ;

/* Variables and functions */
 int /*<<< orphan*/  E_C_FORCE ; 
 int /*<<< orphan*/  FL_ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INT2CHAR (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  M_ERR ; 
 int /*<<< orphan*/  M_INFO ; 
 int /*<<< orphan*/  M_SYSERR ; 
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  SEQ_ABBREV ; 
 int /*<<< orphan*/  SEQ_COMMAND ; 
 int /*<<< orphan*/  SEQ_INPUT ; 
 int S_IRGRP ; 
 int S_IROTH ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 char* _PATH_EXRC ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msgq_str (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*) ; 
 int open (char*,int,int) ; 
 scalar_t__ opts_save (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ seq_save (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_alt_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  stat (char*,struct stat*) ; 

int
ex_mkexrc(SCR *sp, EXCMD *cmdp)
{
	struct stat sb;
	FILE *fp;
	int fd, sverrno;
	char *fname;
	size_t flen;

	switch (cmdp->argc) {
	case 0:
		fname = _PATH_EXRC;
		break;
	case 1:
		INT2CHAR(sp, cmdp->argv[0]->bp, cmdp->argv[0]->len + 1, 
			    fname, flen);
		set_alt_name(sp, fname);
		break;
	default:
		abort();
	}

	if (!FL_ISSET(cmdp->iflags, E_C_FORCE) && !stat(fname, &sb)) {
		msgq_str(sp, M_ERR, fname,
		    "137|%s exists, not written; use ! to override");
		return (1);
	}

	/* Create with max permissions of rw-r--r--. */
	if ((fd = open(fname, O_CREAT | O_TRUNC | O_WRONLY,
	    S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0) {
		msgq_str(sp, M_SYSERR, fname, "%s");
		return (1);
	}

	if ((fp = fdopen(fd, "w")) == NULL) {
		sverrno = errno;
		(void)close(fd);
		goto e2;
	}

	if (seq_save(sp, fp, "abbreviate ", SEQ_ABBREV) || ferror(fp))
		goto e1;
	if (seq_save(sp, fp, "map ", SEQ_COMMAND) || ferror(fp))
		goto e1;
	if (seq_save(sp, fp, "map! ", SEQ_INPUT) || ferror(fp))
		goto e1;
	if (opts_save(sp, fp) || ferror(fp))
		goto e1;
	if (fclose(fp)) {
		sverrno = errno;
		goto e2;
	}

	msgq_str(sp, M_INFO, fname, "138|New exrc file: %s");
	return (0);

e1:	sverrno = errno;
	(void)fclose(fp);
e2:	errno = sverrno;
	msgq_str(sp, M_SYSERR, fname, "%s");
	return (1);
}