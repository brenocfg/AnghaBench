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
struct stat {unsigned long st_ino; int /*<<< orphan*/  st_dev; } ;
struct dirent {unsigned long d_ino; char* d_name; } ;
typedef  int /*<<< orphan*/  nextpathbuf ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  CGETS (int,int,char*) ; 
 scalar_t__ DEV_DEV_COMPARE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ENOENT ; 
 scalar_t__ ISDOT (char*) ; 
 scalar_t__ ISDOTDOT (char*) ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int errno ; 
 int lstat (char*,struct stat*) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int stat (char*,struct stat*) ; 
 int /*<<< orphan*/  strerror (int) ; 
 int /*<<< orphan*/  strncpy (char*,char*,size_t) ; 
 char* strnrcpy (char*,char*,int) ; 
 int /*<<< orphan*/  xsnprintf (char*,size_t,int /*<<< orphan*/ ,char*,...) ; 

char *
xgetcwd(char *pathname, size_t pathlen)
{
    DIR    *dp;
    struct dirent *d;

    struct stat st_root, st_cur, st_next, st_dotdot;
    char    pathbuf[MAXPATHLEN], nextpathbuf[MAXPATHLEN * 2];
    char   *pathptr, *nextpathptr, *cur_name_add;
    int	   save_errno = 0;

    /* find the inode of root */
    if (stat("/", &st_root) == -1) {
	(void) xsnprintf(pathname, pathlen, CGETS(23, 23, 
			"getcwd: Cannot stat \"/\" (%s)"),
			strerror(errno));
	return NULL;
    }
    pathbuf[MAXPATHLEN - 1] = '\0';
    pathptr = &pathbuf[MAXPATHLEN - 1];
    nextpathbuf[MAXPATHLEN - 1] = '\0';
    cur_name_add = nextpathptr = &nextpathbuf[MAXPATHLEN - 1];

    /* find the inode of the current directory */
    if (lstat(".", &st_cur) == -1) {
	(void) xsnprintf(pathname, pathlen, CGETS(23, 24,
			 "getcwd: Cannot stat \".\" (%s)"),
			 strerror(errno));
	return NULL;
    }
    nextpathptr = strnrcpy(nextpathptr, "../", nextpathptr - nextpathbuf);

    /* Descend to root */
    for (;;) {

	/* look if we found root yet */
	if (st_cur.st_ino == st_root.st_ino &&
	    DEV_DEV_COMPARE(st_cur.st_dev, st_root.st_dev)) {
	    (void) strncpy(pathname, *pathptr != '/' ? "/" : pathptr, pathlen);
	    pathname[pathlen - 1] = '\0';
	    return pathname;
	}

	/* open the parent directory */
	if (stat(nextpathptr, &st_dotdot) == -1) {
	    (void) xsnprintf(pathname, pathlen, CGETS(23, 25,
			     "getcwd: Cannot stat directory \"%s\" (%s)"),
			     nextpathptr, strerror(errno));
	    return NULL;
	}
	if ((dp = opendir(nextpathptr)) == NULL) {
	    (void) xsnprintf(pathname, pathlen, CGETS(23, 26,
			     "getcwd: Cannot open directory \"%s\" (%s)"),
			     nextpathptr, strerror(errno));
	    return NULL;
	}

	/* look in the parent for the entry with the same inode */
	if (DEV_DEV_COMPARE(st_dotdot.st_dev, st_cur.st_dev)) {
	    /* Parent has same device. No need to stat every member */
	    for (d = readdir(dp); d != NULL; d = readdir(dp)) {
#ifdef __clipper__
		if (((unsigned long)d->d_ino & 0xffff) == st_cur.st_ino)
		    break;
#else
		if (d->d_ino == st_cur.st_ino)
		    break;
#endif
	    }
	}
	else {
	    /* 
	     * Parent has a different device. This is a mount point so we 
	     * need to stat every member 
	     */
	    for (d = readdir(dp); d != NULL; d = readdir(dp)) {
		if (ISDOT(d->d_name) || ISDOTDOT(d->d_name))
		    continue;
		(void)strncpy(cur_name_add, d->d_name,
		    (size_t) (&nextpathbuf[sizeof(nextpathbuf) - 1] - cur_name_add));
		if (lstat(nextpathptr, &st_next) == -1) {
		    /*
		     * We might not be able to stat() some path components
		     * if we are using afs, but this is not an error as
		     * long as we find the one we need; we also save the
		     * first error to report it if we don't finally succeed.
		     */
		    if (save_errno == 0)
			save_errno = errno;
		    continue;
		}
		/* check if we found it yet */
		if (st_next.st_ino == st_cur.st_ino &&
		    DEV_DEV_COMPARE(st_next.st_dev, st_cur.st_dev)) 
		    break;
	    }
	}
	if (d == NULL) {
	    (void) xsnprintf(pathname, pathlen, CGETS(23, 27,
			     "getcwd: Cannot find \".\" in \"..\" (%s)"),
			     strerror(save_errno ? save_errno : ENOENT));
	    closedir(dp);
	    return NULL;
	}
	else
	    save_errno = 0;
	st_cur = st_dotdot;
	pathptr = strnrcpy(pathptr, d->d_name, pathptr - pathbuf);
	pathptr = strnrcpy(pathptr, "/", pathptr - pathbuf);
	nextpathptr = strnrcpy(nextpathptr, "../", nextpathptr - nextpathbuf);
	*cur_name_add = '\0';
	closedir(dp);
    }
}