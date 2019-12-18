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
struct stat {int st_mode; scalar_t__ st_uid; } ;
struct dirent {int /*<<< orphan*/  d_name; } ;
typedef  int off_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_6__ {int argc; TYPE_1__** argv; } ;
struct TYPE_5__ {int len; int /*<<< orphan*/  bp; } ;
typedef  int /*<<< orphan*/  SCR ;
typedef  TYPE_2__ EXCMD ;
typedef  int /*<<< orphan*/  DIR ;
typedef  char CHAR_T ;

/* Variables and functions */
 int /*<<< orphan*/  CHAR2INT (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*,size_t) ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  FREE_SPACE (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  GET_SPACE_GOTOC (int /*<<< orphan*/ *,char*,size_t,int) ; 
 int /*<<< orphan*/  INT2CHAR (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,size_t) ; 
 int /*<<< orphan*/  M_ERR ; 
 int /*<<< orphan*/  M_SYSERR ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int O_RDONLY ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int S_IRGRP ; 
 int S_IROTH ; 
 int S_IRUSR ; 
 int /*<<< orphan*/  S_ISREG (int) ; 
 int S_IWGRP ; 
 int S_IWOTH ; 
 int S_IWUSR ; 
 scalar_t__ argv_exp2 (int /*<<< orphan*/ *,TYPE_2__*,char*,size_t) ; 
 scalar_t__ close (int) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  ex_cinit (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ getuid () ; 
 int /*<<< orphan*/  msgq_str (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*) ; 
 int open (char*,int,int) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 int read (int,char*,int) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,int) ; 
 int sscanf (int /*<<< orphan*/ ,char*,int*) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  unlink (char*) ; 
 char* v_wstrdup (int /*<<< orphan*/ *,char*,size_t) ; 
 int write (int,char*,int) ; 

__attribute__((used)) static int
file_backup(
	SCR *sp,
	char *name,
	char *bname)
{
	struct dirent *dp;
	struct stat sb;
	DIR *dirp;
	EXCMD cmd;
	off_t off;
	size_t blen;
	int flags, maxnum, nr, num, nw, rfd, wfd, version;
	char *bp, *estr, *p, *pct, *slash, *t, *wfname, buf[8192];
	CHAR_T *wp;
	size_t wlen;
	size_t nlen;
	char *d = NULL;

	rfd = wfd = -1;
	bp = estr = wfname = NULL;

	/*
	 * Open the current file for reading.  Do this first, so that
	 * we don't exec a shell before the most likely failure point.
	 * If it doesn't exist, it's okay, there's just nothing to back
	 * up.
	 */
	errno = 0;
	if ((rfd = open(name, O_RDONLY, 0)) < 0) {
		if (errno == ENOENT)
			return (0);
		estr = name;
		goto err;
	}

	/*
	 * If the name starts with an 'N' character, add a version number
	 * to the name.  Strip the leading N from the string passed to the
	 * expansion routines, for no particular reason.  It would be nice
	 * to permit users to put the version number anywhere in the backup
	 * name, but there isn't a special character that we can use in the
	 * name, and giving a new character a special meaning leads to ugly
	 * hacks both here and in the supporting ex routines.
	 *
	 * Shell and file name expand the option's value.
	 */
	ex_cinit(sp, &cmd, 0, 0, 0, 0, 0);
	if (bname[0] == 'N') {
		version = 1;
		++bname;
	} else
		version = 0;
	CHAR2INT(sp, bname, strlen(bname), wp, wlen);
	if ((wp = v_wstrdup(sp, wp, wlen)) == NULL)
		return (1);
	if (argv_exp2(sp, &cmd, wp, wlen)) {
		free(wp);
		return (1);
	}
	free(wp);

	/*
	 *  0 args: impossible.
	 *  1 args: use it.
	 * >1 args: object, too many args.
	 */
	if (cmd.argc != 1) {
		msgq_str(sp, M_ERR, bname,
		    "258|%s expanded into too many file names");
		(void)close(rfd);
		return (1);
	}

	/*
	 * If appending a version number, read through the directory, looking
	 * for file names that match the name followed by a number.  Make all
	 * of the other % characters in name literal, so the user doesn't get
	 * surprised and sscanf doesn't drop core indirecting through pointers
	 * that don't exist.  If any such files are found, increment its number
	 * by one.
	 */
	if (version) {
		GET_SPACE_GOTOC(sp, bp, blen, cmd.argv[0]->len * 2 + 50);
		INT2CHAR(sp, cmd.argv[0]->bp, cmd.argv[0]->len + 1,
			 p, nlen); 
		d = strdup(p);
		p = d;
		for (t = bp, slash = NULL;
		     p[0] != '\0'; *t++ = *p++)
			if (p[0] == '%') {
				if (p[1] != '%')
					*t++ = '%';
			} else if (p[0] == '/')
				slash = t;
		pct = t;
		*t++ = '%';
		*t++ = 'd';
		*t = '\0';

		if (slash == NULL) {
			dirp = opendir(".");
			p = bp;
		} else {
			*slash = '\0';
			dirp = opendir(bp);
			*slash = '/';
			p = slash + 1;
		}
		if (dirp == NULL) {
			INT2CHAR(sp, cmd.argv[0]->bp, cmd.argv[0]->len + 1,
				estr, nlen);
			goto err;
		}

		for (maxnum = 0; (dp = readdir(dirp)) != NULL;)
			if (sscanf(dp->d_name, p, &num) == 1 && num > maxnum)
				maxnum = num;
		(void)closedir(dirp);

		/* Format the backup file name. */
		(void)snprintf(pct, blen - (pct - bp), "%d", maxnum + 1);
		wfname = bp;
	} else {
		bp = NULL;
		INT2CHAR(sp, cmd.argv[0]->bp, cmd.argv[0]->len + 1,
			wfname, nlen);
	}
	
	/* Open the backup file, avoiding lurkers. */
	if (stat(wfname, &sb) == 0) {
		if (!S_ISREG(sb.st_mode)) {
			msgq_str(sp, M_ERR, bname,
			    "259|%s: not a regular file");
			goto err;
		}
		if (sb.st_uid != getuid()) {
			msgq_str(sp, M_ERR, bname, "260|%s: not owned by you");
			goto err;
		}
		if (sb.st_mode & (S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)) {
			msgq_str(sp, M_ERR, bname,
			   "261|%s: accessible by a user other than the owner");
			goto err;
		}
		flags = O_TRUNC;
	} else
		flags = O_CREAT | O_EXCL;
	if ((wfd = open(wfname, flags | O_WRONLY, S_IRUSR | S_IWUSR)) < 0) {
		estr = bname;
		goto err;
	}

	/* Copy the file's current contents to its backup value. */
	while ((nr = read(rfd, buf, sizeof(buf))) > 0)
		for (off = 0; nr != 0; nr -= nw, off += nw)
			if ((nw = write(wfd, buf + off, nr)) < 0) {
				estr = wfname;
				goto err;
			}
	if (nr < 0) {
		estr = name;
		goto err;
	}

	if (close(rfd)) {
		estr = name;
		goto err;
	}
	if (close(wfd)) {
		estr = wfname;
		goto err;
	}
	if (bp != NULL)
		FREE_SPACE(sp, bp, blen);
	return (0);

alloc_err:
err:	if (rfd != -1)
		(void)close(rfd);
	if (wfd != -1) {
		(void)unlink(wfname);
		(void)close(wfd);
	}
	if (estr)
		msgq_str(sp, M_SYSERR, estr, "%s");
	if (d != NULL)
		free(d);
	if (bp != NULL)
		FREE_SPACE(sp, bp, blen);
	return (1);
}