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
struct timeval {int dummy; } ;
struct stat {int dummy; } ;
typedef  int /*<<< orphan*/  atf_tc_t ;

/* Variables and functions */
 int /*<<< orphan*/  AFILE ; 
 int /*<<< orphan*/  ATF_REQUIRE_ERRNO (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EROFS ; 
 int /*<<< orphan*/  FSTEST_ENTER () ; 
 int /*<<< orphan*/  FSTEST_EXIT () ; 
 int /*<<< orphan*/  FSTYPE_MSDOS (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  RL (int) ; 
 int rump_sys_chmod (int /*<<< orphan*/ ,int) ; 
 int rump_sys_chown (int /*<<< orphan*/ ,int,int) ; 
 int rump_sys_close (int) ; 
 int rump_sys_fchmod (int,int) ; 
 int rump_sys_fchown (int,int,int) ; 
 int rump_sys_futimes (int,struct timeval*) ; 
 int rump_sys_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rump_sys_stat (int /*<<< orphan*/ ,struct stat*) ; 
 int rump_sys_utimes (int /*<<< orphan*/ ,struct timeval*) ; 

__attribute__((used)) static void
attrs(const atf_tc_t *tc, const char *mp)
{
	struct timeval sometvs[2];
	struct stat sb;
	int fd;

	FSTEST_ENTER();

	RL(rump_sys_stat(AFILE, &sb));

	ATF_REQUIRE_ERRNO(EROFS, rump_sys_chmod(AFILE, 0775) == -1);
	if (!FSTYPE_MSDOS(tc))
		ATF_REQUIRE_ERRNO(EROFS, rump_sys_chown(AFILE, 1, 1) == -1);
	ATF_REQUIRE_ERRNO(EROFS, rump_sys_utimes(AFILE, sometvs) == -1);

	RL(fd = rump_sys_open(AFILE, O_RDONLY));
	ATF_REQUIRE_ERRNO(EROFS, rump_sys_fchmod(fd, 0775) == -1);
	if (!FSTYPE_MSDOS(tc))
		ATF_REQUIRE_ERRNO(EROFS, rump_sys_fchown(fd, 1, 1) == -1);
	ATF_REQUIRE_ERRNO(EROFS, rump_sys_futimes(fd, sometvs) == -1);
	RL(rump_sys_close(fd));

	FSTEST_EXIT();
}