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
 int /*<<< orphan*/  ATF_REQUIRE (char*) ; 
 int /*<<< orphan*/  ATF_REQUIRE_ERRNO (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ENAMETOOLONG ; 
 int /*<<< orphan*/  RL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RLF (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  USES_SYMLINKS ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memset (char*,char,size_t) ; 
 int /*<<< orphan*/  rump_sys_chdir (char const*) ; 
 int rump_sys_symlink (char*,char*) ; 
 int /*<<< orphan*/  rump_sys_unlink (char*) ; 

__attribute__((used)) static void
symlink_len(const atf_tc_t *tc, const char *mp, size_t len)
{
	char *buf;
	int r;

	USES_SYMLINKS;

	RLF(rump_sys_chdir(mp), "%s", mp);

	buf = malloc(len + 1);
	ATF_REQUIRE(buf);
	memset(buf, 'a', len);
	buf[len] = '\0';
	r = rump_sys_symlink(buf, "afile");
	if (r == -1) {
		ATF_REQUIRE_ERRNO(ENAMETOOLONG, r);
	} else {
		RL(rump_sys_unlink("afile"));
	}
	free(buf);

	RL(rump_sys_chdir("/"));
}