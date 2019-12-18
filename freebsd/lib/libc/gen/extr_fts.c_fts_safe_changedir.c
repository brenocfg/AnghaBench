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
struct stat {scalar_t__ st_dev; scalar_t__ st_ino; } ;
struct TYPE_3__ {scalar_t__ fts_dev; scalar_t__ fts_ino; } ;
typedef  TYPE_1__ FTSENT ;
typedef  int /*<<< orphan*/  FTS ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  FTS_NOCHDIR ; 
 scalar_t__ ISSET (int /*<<< orphan*/ ) ; 
 int O_CLOEXEC ; 
 int O_DIRECTORY ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  _close (int) ; 
 scalar_t__ _fstat (int,struct stat*) ; 
 int _open (char*,int,int /*<<< orphan*/ ) ; 
 int errno ; 
 int fchdir (int) ; 

__attribute__((used)) static int
fts_safe_changedir(FTS *sp, FTSENT *p, int fd, char *path)
{
	int ret, oerrno, newfd;
	struct stat sb;

	newfd = fd;
	if (ISSET(FTS_NOCHDIR))
		return (0);
	if (fd < 0 && (newfd = _open(path, O_RDONLY | O_DIRECTORY |
	    O_CLOEXEC, 0)) < 0)
		return (-1);
	if (_fstat(newfd, &sb)) {
		ret = -1;
		goto bail;
	}
	if (p->fts_dev != sb.st_dev || p->fts_ino != sb.st_ino) {
		errno = ENOENT;		/* disinformation */
		ret = -1;
		goto bail;
	}
	ret = fchdir(newfd);
bail:
	oerrno = errno;
	if (fd < 0)
		(void)_close(newfd);
	errno = oerrno;
	return (ret);
}