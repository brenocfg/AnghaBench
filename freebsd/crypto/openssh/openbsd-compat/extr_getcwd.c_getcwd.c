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
struct dirent {scalar_t__ d_fileno; int d_namlen; int /*<<< orphan*/  d_name; } ;
typedef  scalar_t__ ino_t ;
typedef  scalar_t__ dev_t ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ERANGE ; 
 scalar_t__ ISDOT (struct dirent*) ; 
 int MAXNAMLEN ; 
 size_t MAXPATHLEN ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dirfd (int /*<<< orphan*/ *) ; 
 int errno ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ fstat (int /*<<< orphan*/ ,struct stat*) ; 
 scalar_t__ lstat (char*,struct stat*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 char* realloc (char*,size_t) ; 
 scalar_t__ stat (char*,struct stat*) ; 

char *
getcwd(char *pt, size_t size)
{
	struct dirent *dp;
	DIR *dir = NULL;
	dev_t dev;
	ino_t ino;
	int first;
	char *bpt, *bup;
	struct stat s;
	dev_t root_dev;
	ino_t root_ino;
	size_t ptsize, upsize;
	int save_errno;
	char *ept, *eup, *up;

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
		ept = pt + size;
	} else {
		if ((pt = malloc(ptsize = MAXPATHLEN)) == NULL)
			return (NULL);
		ept = pt + ptsize;
	}
	bpt = ept - 1;
	*bpt = '\0';

	/*
	 * Allocate bytes for the string of "../"'s.
	 * Should always be enough (it's 340 levels).  If it's not, allocate
	 * as necessary.  Special * case the first stat, it's ".", not "..".
	 */
	if ((up = malloc(upsize = MAXPATHLEN)) == NULL)
		goto err;
	eup = up + upsize;
	bup = up;
	up[0] = '.';
	up[1] = '\0';

	/* Save root values, so know when to stop. */
	if (stat("/", &s))
		goto err;
	root_dev = s.st_dev;
	root_ino = s.st_ino;

	errno = 0;			/* XXX readdir has no error return. */

	for (first = 1;; first = 0) {
		/* Stat the current level. */
		if (lstat(up, &s))
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
			memmove(pt, bpt, ept - bpt);
			free(up);
			return (pt);
		}

		/*
		 * Build pointer to the parent directory, allocating memory
		 * as necessary.  Max length is 3 for "../", the largest
		 * possible component name, plus a trailing NUL.
		 */
		if (bup + 3  + MAXNAMLEN + 1 >= eup) {
			char *nup;

			if ((nup = realloc(up, upsize *= 2)) == NULL)
				goto err;
			bup = nup + (bup - up);
			up = nup;
			eup = up + upsize;
		}
		*bup++ = '.';
		*bup++ = '.';
		*bup = '\0';

		/* Open and stat parent directory. */
		if (!(dir = opendir(up)) || fstat(dirfd(dir), &s))
			goto err;

		/* Add trailing slash for next directory. */
		*bup++ = '/';

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
				memcpy(bup, dp->d_name, dp->d_namlen + 1);

				/* Save the first error for later. */
				if (lstat(up, &s)) {
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
		if (bpt - pt < dp->d_namlen + (first ? 1 : 2)) {
			size_t len;
			char *npt;

			if (!ptsize) {
				errno = ERANGE;
				goto err;
			}
			len = ept - bpt;
			if ((npt = realloc(pt, ptsize *= 2)) == NULL)
				goto err;
			bpt = npt + (bpt - pt);
			pt = npt;
			ept = pt + ptsize;
			memmove(ept - len, bpt, len);
			bpt = ept - len;
		}
		if (!first)
			*--bpt = '/';
		bpt -= dp->d_namlen;
		memcpy(bpt, dp->d_name, dp->d_namlen);
		(void)closedir(dir);

		/* Truncate any file name. */
		*bup = '\0';
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
	free(up);
	if (dir)
		(void)closedir(dir);

	errno = save_errno;

	return (NULL);
}