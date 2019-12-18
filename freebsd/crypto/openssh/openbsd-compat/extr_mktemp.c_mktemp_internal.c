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
struct stat {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEXIST ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOENT ; 
 unsigned int INT_MAX ; 
#define  MKTEMP_DIR 130 
#define  MKTEMP_FILE 129 
#define  MKTEMP_NAME 128 
 unsigned int NUM_CHARS ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int O_RDWR ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 int S_IXUSR ; 
 char* TEMPCHARS ; 
 unsigned int arc4random_uniform (unsigned int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  lstat (char*,struct stat*) ; 
 int /*<<< orphan*/  mkdir (char*,int) ; 
 int open (char*,int,int) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static int
mktemp_internal(char *path, int slen, int mode)
{
	char *start, *cp, *ep;
	const char *tempchars = TEMPCHARS;
	unsigned int r, tries;
	struct stat sb;
	size_t len;
	int fd;

	len = strlen(path);
	if (len == 0 || slen < 0 || (size_t)slen >= len) {
		errno = EINVAL;
		return(-1);
	}
	ep = path + len - slen;

	tries = 1;
	for (start = ep; start > path && start[-1] == 'X'; start--) {
		if (tries < INT_MAX / NUM_CHARS)
			tries *= NUM_CHARS;
	}
	tries *= 2;

	do {
		for (cp = start; cp != ep; cp++) {
			r = arc4random_uniform(NUM_CHARS);
			*cp = tempchars[r];
		}

		switch (mode) {
		case MKTEMP_NAME:
			if (lstat(path, &sb) != 0)
				return(errno == ENOENT ? 0 : -1);
			break;
		case MKTEMP_FILE:
			fd = open(path, O_CREAT|O_EXCL|O_RDWR, S_IRUSR|S_IWUSR);
			if (fd != -1 || errno != EEXIST)
				return(fd);
			break;
		case MKTEMP_DIR:
			if (mkdir(path, S_IRUSR|S_IWUSR|S_IXUSR) == 0)
				return(0);
			if (errno != EEXIST)
				return(-1);
			break;
		}
	} while (--tries);

	errno = EEXIST;
	return(-1);
}