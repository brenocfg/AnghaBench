#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uintmax_t ;
struct inotab {int t_size; int /*<<< orphan*/  t_seekpt; } ;
typedef  scalar_t__ ino_t ;
struct TYPE_5__ {int /*<<< orphan*/  name; scalar_t__ ino; } ;
struct TYPE_4__ {int /*<<< orphan*/  dd_fd; } ;

/* Variables and functions */
 int BUFSIZ ; 
 int FAIL ; 
 int GOOD ; 
 int MIN (int,int) ; 
 int /*<<< orphan*/  Nflag ; 
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  close (int) ; 
 TYPE_3__ curfile ; 
 TYPE_1__* dirp ; 
 int /*<<< orphan*/  done (int) ; 
 int dup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 struct inotab* inotablookup (scalar_t__) ; 
 int open (char*,int,int) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ,char*) ; 
 int read (int,char*,int) ; 
 int /*<<< orphan*/  rst_seekdir (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int write (int,char*,int) ; 

int
genliteraldir(char *name, ino_t ino)
{
	struct inotab *itp;
	int ofile, dp, i, size;
	char buf[BUFSIZ];

	itp = inotablookup(ino);
	if (itp == NULL)
		panic("Cannot find directory inode %ju named %s\n",
		    (uintmax_t)ino, name);
	if ((ofile = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0666)) < 0) {
		fprintf(stderr, "%s: ", name);
		(void) fflush(stderr);
		fprintf(stderr, "cannot create file: %s\n", strerror(errno));
		return (FAIL);
	}
	rst_seekdir(dirp, itp->t_seekpt, itp->t_seekpt);
	dp = dup(dirp->dd_fd);
	for (i = itp->t_size; i > 0; i -= BUFSIZ) {
		size = MIN(i, BUFSIZ);
		if (read(dp, buf, (int) size) == -1) {
			fprintf(stderr,
			    "write error extracting inode %ju, name %s\n",
			    (uintmax_t)curfile.ino, curfile.name);
			fprintf(stderr, "read: %s\n", strerror(errno));
			done(1);
		}
		if (!Nflag && write(ofile, buf, (int) size) == -1) {
			fprintf(stderr,
			    "write error extracting inode %ju, name %s\n",
			    (uintmax_t)curfile.ino, curfile.name);
			fprintf(stderr, "write: %s\n", strerror(errno));
			done(1);
		}
	}
	(void) close(dp);
	(void) close(ofile);
	return (GOOD);
}