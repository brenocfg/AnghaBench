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
typedef  int /*<<< orphan*/  atf_tc_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE_ERRNO (int /*<<< orphan*/ ,int) ; 
 scalar_t__ E2BIG ; 
 scalar_t__ EOPNOTSUPP ; 
 int /*<<< orphan*/  ESTALE ; 
 int /*<<< orphan*/  FNAME ; 
 scalar_t__ FSTYPE_LFS (int /*<<< orphan*/  const*) ; 
 int O_CREAT ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int O_RDWR ; 
 int /*<<< orphan*/  RL (int) ; 
 int /*<<< orphan*/  atf_tc_expect_fail (char*) ; 
 int /*<<< orphan*/  atf_tc_expect_pass () ; 
 int /*<<< orphan*/  atf_tc_fail_errno (char*) ; 
 int /*<<< orphan*/  atf_tc_skip (char*) ; 
 scalar_t__ errno ; 
 void* malloc (size_t) ; 
 int rump_sys_chdir (char const*) ; 
 int rump_sys_close (int) ; 
 int rump_sys_fhopen (void*,size_t,int /*<<< orphan*/ ) ; 
 int rump_sys_getfh (int /*<<< orphan*/ ,void*,size_t*) ; 
 int rump_sys_open (int /*<<< orphan*/ ,int,int) ; 
 int rump_sys_unlink (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tfhremove(const atf_tc_t *tc, const char *path)
{
	size_t fhsize;
	void *fhp;
	int fd;

	RL(rump_sys_chdir(path));
	RL(fd = rump_sys_open(FNAME, O_RDWR | O_CREAT, 0777));
	RL(rump_sys_close(fd));

	fhsize = 0;
	if (rump_sys_getfh(FNAME, NULL, &fhsize) == -1) {
		if (errno == EOPNOTSUPP) {
			atf_tc_skip("file handles not supported");
		} else if (errno != E2BIG) {
			atf_tc_fail_errno("getfh size");
		}
	}

	fhp = malloc(fhsize);
	RL(rump_sys_getfh(FNAME, fhp, &fhsize));
	RL(rump_sys_unlink(FNAME));

	if (FSTYPE_LFS(tc))
		atf_tc_expect_fail("fhopen() for removed file succeeds "
		    "(PR kern/43745)");
	ATF_REQUIRE_ERRNO(ESTALE, rump_sys_fhopen(fhp, fhsize, O_RDONLY) == -1);
	atf_tc_expect_pass();

	RL(rump_sys_chdir("/"));
}