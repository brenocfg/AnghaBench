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
typedef  scalar_t__ uid_t ;
typedef  int /*<<< orphan*/  u_int ;
struct timespec {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct entry {int e_flags; } ;
typedef  int mode_t ;
typedef  int /*<<< orphan*/  gid_t ;
struct TYPE_2__ {char* name; int extsize; scalar_t__ uid; int mode; scalar_t__ rdev; int /*<<< orphan*/  ino; int /*<<< orphan*/  file_flags; int /*<<< orphan*/  gid; int /*<<< orphan*/  birthtime_nsec; int /*<<< orphan*/  birthtime_sec; int /*<<< orphan*/  atime_nsec; int /*<<< orphan*/  atime_sec; int /*<<< orphan*/  mtime_nsec; int /*<<< orphan*/  mtime_sec; int /*<<< orphan*/  action; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_FDCWD ; 
 int /*<<< orphan*/  AT_SYMLINK_NOFOLLOW ; 
 int EXTRACT ; 
 int FAIL ; 
 int GOOD ; 
#define  IFBLK 134 
#define  IFCHR 133 
#define  IFDIR 132 
#define  IFIFO 131 
#define  IFLNK 130 
 int IFMT ; 
#define  IFREG 129 
#define  IFSOCK 128 
 int /*<<< orphan*/  Nflag ; 
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  SXA_FD ; 
 int /*<<< orphan*/  SXA_FILE ; 
 int /*<<< orphan*/  SXA_LINK ; 
 int /*<<< orphan*/  SYMLINK ; 
 int /*<<< orphan*/  USING ; 
 int /*<<< orphan*/  chflags (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chmod (char*,int) ; 
 int /*<<< orphan*/  chown (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 TYPE_1__ curfile ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fchflags (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fchmod (int,int) ; 
 int /*<<< orphan*/  fchown (int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  futimens (int,struct timespec*) ; 
 int genliteraldir (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getfile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ getuid () ; 
 int /*<<< orphan*/  lchflags (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lchmod (char*,int) ; 
 int /*<<< orphan*/  lchown (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int linkit (char*,char*,int /*<<< orphan*/ ) ; 
 char* lnkbuf ; 
 struct entry* lookupname (char*) ; 
 int /*<<< orphan*/  mflag ; 
 int /*<<< orphan*/  mkfifo (char*,int) ; 
 int /*<<< orphan*/  mknod (char*,int,int) ; 
 int ofile ; 
 int open (char*,int,int) ; 
 int /*<<< orphan*/  panic (char*,char*) ; 
 int /*<<< orphan*/  pathlen ; 
 int /*<<< orphan*/  set_extattr (int,char*,char*,int,int /*<<< orphan*/ ) ; 
 char* setupextattr (int) ; 
 int /*<<< orphan*/  skipfile () ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uflag ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int /*<<< orphan*/  utimensat (int /*<<< orphan*/ ,char*,struct timespec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  xtrattr ; 
 int /*<<< orphan*/  xtrfile ; 
 int /*<<< orphan*/  xtrlnkfile ; 
 int /*<<< orphan*/  xtrlnkskip ; 
 int /*<<< orphan*/  xtrnull ; 
 int /*<<< orphan*/  xtrskip ; 

int
extractfile(char *name)
{
	u_int flags;
	uid_t uid;
	gid_t gid;
	mode_t mode;
	int extsize;
	struct timespec mtimep[2], ctimep[2];
	struct entry *ep;
	char *buf;

	curfile.name = name;
	curfile.action = USING;
	mtimep[0].tv_sec = curfile.atime_sec;
	mtimep[0].tv_nsec = curfile.atime_nsec;
	mtimep[1].tv_sec = curfile.mtime_sec;
	mtimep[1].tv_nsec = curfile.mtime_nsec;
	ctimep[0].tv_sec = curfile.atime_sec;
	ctimep[0].tv_nsec = curfile.atime_nsec;
	ctimep[1].tv_sec = curfile.birthtime_sec;
	ctimep[1].tv_nsec = curfile.birthtime_nsec;
	extsize = curfile.extsize;
	uid = getuid();
	if (uid == 0)
		uid = curfile.uid;
	gid = curfile.gid;
	mode = curfile.mode;
	flags = curfile.file_flags;
	switch (mode & IFMT) {

	default:
		fprintf(stderr, "%s: unknown file mode 0%o\n", name, mode);
		skipfile();
		return (FAIL);

	case IFSOCK:
		vprintf(stdout, "skipped socket %s\n", name);
		skipfile();
		return (GOOD);

	case IFDIR:
		if (mflag) {
			ep = lookupname(name);
			if (ep == NULL || ep->e_flags & EXTRACT)
				panic("unextracted directory %s\n", name);
			skipfile();
			return (GOOD);
		}
		vprintf(stdout, "extract file %s\n", name);
		return (genliteraldir(name, curfile.ino));

	case IFLNK:
		lnkbuf[0] = '\0';
		pathlen = 0;
		buf = setupextattr(extsize);
		getfile(xtrlnkfile, xtrattr, xtrlnkskip);
		if (pathlen == 0) {
			vprintf(stdout,
			    "%s: zero length symbolic link (ignored)\n", name);
			return (GOOD);
		}
		if (linkit(lnkbuf, name, SYMLINK) == GOOD) {
			if (extsize > 0)
				set_extattr(-1, name, buf, extsize, SXA_LINK);
			(void) lchown(name, uid, gid);
			(void) lchmod(name, mode);
			(void) utimensat(AT_FDCWD, name, ctimep,
			    AT_SYMLINK_NOFOLLOW);
			(void) utimensat(AT_FDCWD, name, mtimep,
			    AT_SYMLINK_NOFOLLOW);
			(void) lchflags(name, flags);
			return (GOOD);
		}
		return (FAIL);

	case IFIFO:
		vprintf(stdout, "extract fifo %s\n", name);
		if (Nflag) {
			skipfile();
			return (GOOD);
		}
		if (uflag)
			(void) unlink(name);
		if (mkfifo(name, 0600) < 0) {
			fprintf(stderr, "%s: cannot create fifo: %s\n",
			    name, strerror(errno));
			skipfile();
			return (FAIL);
		}
		if (extsize == 0) {
			skipfile();
		} else {
			buf = setupextattr(extsize);
			getfile(xtrnull, xtrattr, xtrnull);
			set_extattr(-1, name, buf, extsize, SXA_FILE);
		}
		(void) chown(name, uid, gid);
		(void) chmod(name, mode);
		(void) utimensat(AT_FDCWD, name, ctimep, 0);
		(void) utimensat(AT_FDCWD, name, mtimep, 0);
		(void) chflags(name, flags);
		return (GOOD);

	case IFCHR:
	case IFBLK:
		vprintf(stdout, "extract special file %s\n", name);
		if (Nflag) {
			skipfile();
			return (GOOD);
		}
		if (uflag)
			(void) unlink(name);
		if (mknod(name, (mode & (IFCHR | IFBLK)) | 0600,
		    (int)curfile.rdev) < 0) {
			fprintf(stderr, "%s: cannot create special file: %s\n",
			    name, strerror(errno));
			skipfile();
			return (FAIL);
		}
		if (extsize == 0) {
			skipfile();
		} else {
			buf = setupextattr(extsize);
			getfile(xtrnull, xtrattr, xtrnull);
			set_extattr(-1, name, buf, extsize, SXA_FILE);
		}
		(void) chown(name, uid, gid);
		(void) chmod(name, mode);
		(void) utimensat(AT_FDCWD, name, ctimep, 0);
		(void) utimensat(AT_FDCWD, name, mtimep, 0);
		(void) chflags(name, flags);
		return (GOOD);

	case IFREG:
		vprintf(stdout, "extract file %s\n", name);
		if (Nflag) {
			skipfile();
			return (GOOD);
		}
		if (uflag)
			(void) unlink(name);
		if ((ofile = open(name, O_WRONLY | O_CREAT | O_TRUNC,
		    0600)) < 0) {
			fprintf(stderr, "%s: cannot create file: %s\n",
			    name, strerror(errno));
			skipfile();
			return (FAIL);
		}
		buf = setupextattr(extsize);
		getfile(xtrfile, xtrattr, xtrskip);
		if (extsize > 0)
			set_extattr(ofile, name, buf, extsize, SXA_FD);
		(void) fchown(ofile, uid, gid);
		(void) fchmod(ofile, mode);
		(void) futimens(ofile, ctimep);
		(void) futimens(ofile, mtimep);
		(void) fchflags(ofile, flags);
		(void) close(ofile);
		return (GOOD);
	}
	/* NOTREACHED */
}