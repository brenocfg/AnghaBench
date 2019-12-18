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
struct stat {scalar_t__ st_dev; scalar_t__ st_ino; } ;
struct dirent {scalar_t__ d_fileno; char* d_name; int d_namlen; } ;
typedef  scalar_t__ ino_t ;
typedef  scalar_t__ dev_t ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  AT_FDCWD ; 
 int /*<<< orphan*/  AT_SYMLINK_NOFOLLOW ; 
 int EINVAL ; 
 int ENOENT ; 
 int ERANGE ; 
 scalar_t__ ISDOT (struct dirent*) ; 
 int O_CLOEXEC ; 
 int O_RDONLY ; 
 size_t PATH_MAX ; 
 scalar_t__ __getcwd (char*,int) ; 
 int /*<<< orphan*/  _close (int) ; 
 int /*<<< orphan*/  _dirfd (int /*<<< orphan*/ *) ; 
 scalar_t__ _fstat (int /*<<< orphan*/ ,struct stat*) ; 
 int _openat (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  bcopy (char*,char*,size_t) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int errno ; 
 int /*<<< orphan*/ * fdopendir (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ fstatat (int /*<<< orphan*/ ,char*,struct stat*,int /*<<< orphan*/ ) ; 
 scalar_t__ lstat (char*,struct stat*) ; 
 char* malloc (size_t) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 char* reallocf (char*,size_t) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int strlen (char*) ; 

char *
getcwd(char *pt, size_t size)
{
	struct dirent *dp;
	DIR *dir = NULL;
	dev_t dev;
	ino_t ino;
	int first;
	char *bpt;
	struct stat s;
	dev_t root_dev;
	ino_t root_ino;
	size_t ptsize;
	int save_errno;
	char *ept, c;
	int fd;

	/*
	 * If no buffer specified by the user, allocate one as necessary.
	 * If a buffer is specified, the size has to be non-zero.  The path
	 * is built from the end of the buffer backwards.
	 */
	if (pt) {
		ptsize = 0;
		if (!size) {
			errno = EINVAL;
			return (NULL);
		}
		if (size == 1) {
			errno = ERANGE;
			return (NULL);
		}
		ept = pt + size;
	} else {
		if ((pt = malloc(ptsize = PATH_MAX)) == NULL)
			return (NULL);
		ept = pt + ptsize;
	}
	if (__getcwd(pt, ept - pt) == 0) {
		if (*pt != '/') {
			bpt = pt;
			ept = pt + strlen(pt) - 1;
			while (bpt < ept) {
				c = *bpt;
				*bpt++ = *ept;
				*ept-- = c;
			}
		}
		return (pt);
	}
	bpt = ept - 1;
	*bpt = '\0';

	/* Save root values, so know when to stop. */
	if (stat("/", &s))
		goto err;
	root_dev = s.st_dev;
	root_ino = s.st_ino;

	errno = 0;			/* XXX readdir has no error return. */

	for (first = 1;; first = 0) {
		/* Stat the current level. */
		if (dir != NULL ? _fstat(_dirfd(dir), &s) : lstat(".", &s))
			goto err;

		/* Save current node values. */
		ino = s.st_ino;
		dev = s.st_dev;

		/* Check for reaching root. */
		if (root_dev == dev && root_ino == ino) {
			*--bpt = '/';
			/*
			 * It's unclear that it's a requirement to copy the
			 * path to the beginning of the buffer, but it's always
			 * been that way and stuff would probably break.
			 */
			bcopy(bpt, pt, ept - bpt);
			if (dir)
				(void) closedir(dir);
			return (pt);
		}

		/* Open and stat parent directory. */
		fd = _openat(dir != NULL ? _dirfd(dir) : AT_FDCWD,
				"..", O_RDONLY | O_CLOEXEC);
		if (fd == -1)
			goto err;
		if (dir)
			(void) closedir(dir);
		if (!(dir = fdopendir(fd)) || _fstat(_dirfd(dir), &s)) {
			_close(fd);
			goto err;
		}

		/*
		 * If it's a mount point, have to stat each element because
		 * the inode number in the directory is for the entry in the
		 * parent directory, not the inode number of the mounted file.
		 */
		save_errno = 0;
		if (s.st_dev == dev) {
			for (;;) {
				if (!(dp = readdir(dir)))
					goto notfound;
				if (dp->d_fileno == ino)
					break;
			}
		} else
			for (;;) {
				if (!(dp = readdir(dir)))
					goto notfound;
				if (ISDOT(dp))
					continue;

				/* Save the first error for later. */
				if (fstatat(_dirfd(dir), dp->d_name, &s,
				    AT_SYMLINK_NOFOLLOW)) {
					if (!save_errno)
						save_errno = errno;
					errno = 0;
					continue;
				}
				if (s.st_dev == dev && s.st_ino == ino)
					break;
			}

		/*
		 * Check for length of the current name, preceding slash,
		 * leading slash.
		 */
		while (bpt - pt < dp->d_namlen + (first ? 1 : 2)) {
			size_t len, off;

			if (!ptsize) {
				errno = ERANGE;
				goto err;
			}
			off = bpt - pt;
			len = ept - bpt;
			if ((pt = reallocf(pt, ptsize *= 2)) == NULL)
				goto err;
			bpt = pt + off;
			ept = pt + ptsize;
			bcopy(bpt, ept - len, len);
			bpt = ept - len;
		}
		if (!first)
			*--bpt = '/';
		bpt -= dp->d_namlen;
		bcopy(dp->d_name, bpt, dp->d_namlen);
	}

notfound:
	/*
	 * If readdir set errno, use it, not any saved error; otherwise,
	 * didn't find the current directory in its parent directory, set
	 * errno to ENOENT.
	 */
	if (!errno)
		errno = save_errno ? save_errno : ENOENT;
	/* FALLTHROUGH */
err:
	save_errno = errno;

	if (ptsize)
		free(pt);
	if (dir)
		(void) closedir(dir);

	errno = save_errno;
	return (NULL);
}