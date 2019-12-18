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
 scalar_t__ E2BIG ; 
 scalar_t__ EOPNOTSUPP ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  RL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_tc_fail_errno (char*) ; 
 int /*<<< orphan*/  atf_tc_skip (char*) ; 
 scalar_t__ errno ; 
 void* malloc (size_t) ; 
 int /*<<< orphan*/  printf (char*,unsigned long) ; 
 int /*<<< orphan*/  rump_sys_chdir (char const*) ; 
 int /*<<< orphan*/  rump_sys_close (int) ; 
 int rump_sys_fhopen (void*,size_t,int /*<<< orphan*/ ) ; 
 int rump_sys_getfh (char*,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  srandom (unsigned long) ; 
 int /*<<< orphan*/  tests_makegarbage (void*,size_t) ; 
 unsigned long time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
tfhinval(const atf_tc_t *tc, const char *path)
{
	size_t fhsize;
	void *fhp;
	unsigned long seed;
	int fd;

	srandom(seed = time(NULL));
	printf("RNG seed %lu\n", seed);

	RL(rump_sys_chdir(path));
	fhsize = 0;
	if (rump_sys_getfh(".", NULL, &fhsize) == -1) {
		if (errno == EOPNOTSUPP) {
			atf_tc_skip("file handles not supported");
		} else if (errno != E2BIG) {
			atf_tc_fail_errno("getfh size");
		}
	}

	fhp = malloc(fhsize);
	tests_makegarbage(fhp, fhsize);
	fd = rump_sys_fhopen(fhp, fhsize, O_RDWR);
	if (fd != -1)
		rump_sys_close(fd);

	RL(rump_sys_chdir("/"));
}