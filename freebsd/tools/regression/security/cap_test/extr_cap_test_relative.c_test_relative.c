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
typedef  int cap_rights_t ;

/* Variables and functions */
 int /*<<< orphan*/  AT_FDCWD ; 
 int CAP_ALL ; 
 int CAP_LOOKUP ; 
 int CAP_MASK_VALID ; 
 int CAP_READ ; 
 int CAP_SEEK ; 
 int CAP_WRITE ; 
 int /*<<< orphan*/  CHECK_CAPMODE (int (*) (int,char*,int /*<<< orphan*/ ),int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_NOTCAPABLE (int (*) (int,char*,int /*<<< orphan*/ ),int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_RIGHTS (int,int) ; 
 int /*<<< orphan*/  CHECK_SYSCALL_SUCCEEDS (int (*) (int,char*,int /*<<< orphan*/ ),int,...) ; 
 int /*<<< orphan*/  MAKE_CAPABILITY (int,int,int) ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int PASSED ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int cap_enter () ; 
 int /*<<< orphan*/  cap_getrights ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int openat (int,char*,int /*<<< orphan*/ ) ; 

int
test_relative(void)
{
	int success = PASSED;
	int fd, etc, etc_cap, etc_cap_ro, etc_cap_base, etc_cap_all;
	cap_rights_t baserights = CAP_READ | CAP_WRITE | CAP_SEEK | CAP_LOOKUP;
	cap_rights_t rights;

	REQUIRE(etc = open("/etc/", O_RDONLY));
	CHECK_SYSCALL_SUCCEEDS(cap_getrights, etc, &rights);
	CHECK_RIGHTS(rights, CAP_ALL);

	MAKE_CAPABILITY(etc_cap, etc, CAP_READ);
	MAKE_CAPABILITY(etc_cap_ro, etc, CAP_READ | CAP_LOOKUP);
	MAKE_CAPABILITY(etc_cap_base, etc, baserights);
	MAKE_CAPABILITY(etc_cap_all, etc, CAP_MASK_VALID);

	/*
	 * openat(2) with regular file descriptors in non-capability mode
	 * should Just Work (tm).
	 */
	CHECK_SYSCALL_SUCCEEDS(openat, etc, "/etc/passwd", O_RDONLY);
	CHECK_SYSCALL_SUCCEEDS(openat, AT_FDCWD, "/etc/passwd", O_RDONLY);
	CHECK_SYSCALL_SUCCEEDS(openat, etc, "passwd", O_RDONLY);
	CHECK_SYSCALL_SUCCEEDS(openat, etc, "../etc/passwd", O_RDONLY);

	/*
	 * Lookups relative to capabilities should be strictly relative.
	 *
	 * When not in capability mode, we don't actually require CAP_LOOKUP.
	 */
	CHECK_SYSCALL_SUCCEEDS(openat, etc_cap_ro, "passwd", O_RDONLY);
	CHECK_SYSCALL_SUCCEEDS(openat, etc_cap_base, "passwd", O_RDONLY);
	CHECK_SYSCALL_SUCCEEDS(openat, etc_cap_all, "passwd", O_RDONLY);

	CHECK_NOTCAPABLE(openat, etc_cap_ro, "../etc/passwd", O_RDONLY);
	CHECK_NOTCAPABLE(openat, etc_cap_base, "../etc/passwd", O_RDONLY);

	/*
	 * This requires discussion: do we treat a capability with
	 * CAP_MASK_VALID *exactly* like a non-capability file descriptor
	 * (currently, the implementation says yes)?
	 */
	CHECK_SYSCALL_SUCCEEDS(openat, etc_cap_all, "../etc/passwd", O_RDONLY);

	/*
	 * A file opened relative to a capability should itself be a capability.
	 */
	CHECK_SYSCALL_SUCCEEDS(cap_getrights, etc_cap_base, &rights);

	REQUIRE(fd = openat(etc_cap_base, "passwd", O_RDONLY));
	CHECK_SYSCALL_SUCCEEDS(cap_getrights, fd, &rights);
	CHECK_RIGHTS(rights, baserights);

	/*
	 * Enter capability mode; now ALL lookups are strictly relative.
	 */
	REQUIRE(cap_enter());

	/*
	 * Relative lookups on regular files or capabilities with CAP_LOOKUP
	 * ought to succeed.
	 */
	CHECK_SYSCALL_SUCCEEDS(openat, etc, "passwd", O_RDONLY);
	CHECK_SYSCALL_SUCCEEDS(openat, etc_cap_ro, "passwd", O_RDONLY);
	CHECK_SYSCALL_SUCCEEDS(openat, etc_cap_base, "passwd", O_RDONLY);
	CHECK_SYSCALL_SUCCEEDS(openat, etc_cap_all, "passwd", O_RDONLY);

	/*
	 * Lookup relative to capabilities without CAP_LOOKUP should fail.
	 */
	CHECK_NOTCAPABLE(openat, etc_cap, "passwd", O_RDONLY);

	/*
	 * Absolute lookups should fail.
	 */
	CHECK_CAPMODE(openat, AT_FDCWD, "/etc/passwd", O_RDONLY);
	CHECK_NOTCAPABLE(openat, etc, "/etc/passwd", O_RDONLY);

	/*
	 * Lookups containing '..' should fail in capability mode.
	 */
	CHECK_NOTCAPABLE(openat, etc, "../etc/passwd", O_RDONLY);
	CHECK_NOTCAPABLE(openat, etc_cap_ro, "../etc/passwd", O_RDONLY);
	CHECK_NOTCAPABLE(openat, etc_cap_base, "../etc/passwd", O_RDONLY);

	REQUIRE(fd = openat(etc, "passwd", O_RDONLY));
	CHECK_SYSCALL_SUCCEEDS(cap_getrights, fd, &rights);

	/*
	 * A file opened relative to a capability should itself be a capability.
	 */
	REQUIRE(fd = openat(etc_cap_base, "passwd", O_RDONLY));
	CHECK_SYSCALL_SUCCEEDS(cap_getrights, fd, &rights);
	CHECK_RIGHTS(rights, baserights);

	return success;
}