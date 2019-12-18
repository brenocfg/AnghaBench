#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct timeval {int tv_sec; int tv_usec; } ;
struct TYPE_6__ {int tv_sec; int tv_nsec; } ;
struct TYPE_5__ {int tv_sec; int tv_nsec; } ;
struct stat {int st_uid; int st_gid; int st_mode; TYPE_2__ st_mtimespec; TYPE_1__ st_atimespec; } ;
typedef  int /*<<< orphan*/  atf_tc_t ;
struct TYPE_8__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_7__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;

/* Variables and functions */
 int ACCESSPERMS ; 
 int /*<<< orphan*/  CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FSTEST_ENTER () ; 
 int /*<<< orphan*/  FSTEST_EXIT () ; 
 scalar_t__ FSTYPE_EXT2FS (int /*<<< orphan*/  const*) ; 
 scalar_t__ FSTYPE_MSDOS (int /*<<< orphan*/  const*) ; 
 scalar_t__ FSTYPE_SYSVBFS (int /*<<< orphan*/  const*) ; 
 scalar_t__ FSTYPE_V7FS (int /*<<< orphan*/  const*) ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int /*<<< orphan*/  RL (int) ; 
 int /*<<< orphan*/  TESTFILE ; 
 int rump_sys_chmod (int /*<<< orphan*/ ,int) ; 
 int rump_sys_chown (int /*<<< orphan*/ ,int,int) ; 
 int rump_sys_close (int) ; 
 int rump_sys_open (int /*<<< orphan*/ ,int,int) ; 
 int rump_sys_stat (int /*<<< orphan*/ ,struct stat*) ; 
 int rump_sys_utimes (int /*<<< orphan*/ ,struct timeval*) ; 
 TYPE_4__ st_atimespec ; 
 int /*<<< orphan*/  st_gid ; 
 int /*<<< orphan*/  st_mode ; 
 TYPE_3__ st_mtimespec ; 
 int /*<<< orphan*/  st_uid ; 

__attribute__((used)) static void
attrs(const atf_tc_t *tc, const char *mp)
{
	struct stat sb, sb2;
	struct timeval tv[2];
	int fd;

	FSTEST_ENTER();
	RL(fd = rump_sys_open(TESTFILE, O_RDWR | O_CREAT, 0755));
	RL(rump_sys_close(fd));
	RL(rump_sys_stat(TESTFILE, &sb));
	if (!(FSTYPE_MSDOS(tc) || FSTYPE_SYSVBFS(tc))) {
		RL(rump_sys_chown(TESTFILE, 1, 2));
		sb.st_uid = 1;
		sb.st_gid = 2;
		RL(rump_sys_chmod(TESTFILE, 0123));
		sb.st_mode = (sb.st_mode & ~ACCESSPERMS) | 0123;
	}

	tv[0].tv_sec = 1000000000; /* need something >1980 for msdosfs */
	tv[0].tv_usec = 1;
	tv[1].tv_sec = 1000000002; /* need even seconds for msdosfs */
	tv[1].tv_usec = 3;
	RL(rump_sys_utimes(TESTFILE, tv));
	RL(rump_sys_utimes(TESTFILE, tv)); /* XXX: utimes & birthtime */
	sb.st_atimespec.tv_sec = 1000000000;
	sb.st_atimespec.tv_nsec = 1000;
	sb.st_mtimespec.tv_sec = 1000000002;
	sb.st_mtimespec.tv_nsec = 3000;

	RL(rump_sys_stat(TESTFILE, &sb2));
#define CHECK(a) ATF_REQUIRE_EQ(sb.a, sb2.a)
	if (!(FSTYPE_MSDOS(tc) || FSTYPE_SYSVBFS(tc))) {
		CHECK(st_uid);
		CHECK(st_gid);
		CHECK(st_mode);
	}
	if (!FSTYPE_MSDOS(tc)) {
		/* msdosfs has only access date, not time */
		CHECK(st_atimespec.tv_sec);
	}
	CHECK(st_mtimespec.tv_sec);
	if (!(FSTYPE_EXT2FS(tc) || FSTYPE_MSDOS(tc) ||
	      FSTYPE_SYSVBFS(tc) || FSTYPE_V7FS(tc))) {
		CHECK(st_atimespec.tv_nsec);
		CHECK(st_mtimespec.tv_nsec);
	}
#undef  CHECK

	FSTEST_EXIT();
}