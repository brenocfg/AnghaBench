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
typedef  int /*<<< orphan*/  uid_t ;
struct stat {scalar_t__ st_gid; } ;
typedef  unsigned int gid_t ;

/* Variables and functions */
 int O_BINARY ; 
 int O_CREAT ; 
 int _alt_gid ; 
 scalar_t__ _default_gid ; 
 int _invalid_gid ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  failure (char*) ; 
 scalar_t__ fchown (int,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 int /*<<< orphan*/  getuid () ; 
 int open (char*,int,int) ; 

__attribute__((used)) static void
searchgid(void)
{
	static int   _searched = 0;
	uid_t uid = getuid();
	gid_t gid = 0;
	unsigned int n;
	struct stat st;
	int fd;

	/* If we've already looked this up, we're done. */
	if (_searched)
		return;
	_searched = 1;

	/* Create a file on disk in the current default dir. */
	fd = open("test_gid", O_CREAT | O_BINARY, 0664);
	failure("Couldn't create a file for gid testing.");
	assert(fd > 0);

	/* See what GID it ended up with.  This is our "valid" GID. */
	assert(fstat(fd, &st) == 0);
	_default_gid = st.st_gid;

	/* Find a GID for which fchown() fails.  This is our "invalid" GID. */
	_invalid_gid = -1;
	/* This loop stops when we wrap the gid or examine 10,000 gids. */
	for (gid = 1, n = 1; gid == n && n < 10000 ; n++, gid++) {
		if (fchown(fd, uid, gid) != 0) {
			_invalid_gid = gid;
			break;
		}
	}

	/*
	 * Find a GID for which fchown() succeeds, but which isn't the
	 * default.  This is the "alternate" gid.
	 */
	_alt_gid = -1;
	for (gid = 0, n = 0; gid == n && n < 10000 ; n++, gid++) {
		/* _alt_gid must be different than _default_gid */
		if (gid == (gid_t)_default_gid)
			continue;
		if (fchown(fd, uid, gid) == 0) {
			_alt_gid = gid;
			break;
		}
	}
	close(fd);
}