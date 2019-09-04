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
struct stat {int st_mode; } ;
typedef  int mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  _packbuilder ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_packbuilder_write (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_stat (char*,struct stat*) ; 
 int p_umask (int) ; 
 int /*<<< orphan*/  seed_packbuilder () ; 

__attribute__((used)) static void test_write_pack_permission(mode_t given, mode_t expected)
{
	struct stat statbuf;
	mode_t mask, os_mask;

	seed_packbuilder();

	git_packbuilder_write(_packbuilder, ".", given, NULL, NULL);

	/* Windows does not return group/user bits from stat,
	* files are never executable.
	*/
#ifdef GIT_WIN32
	os_mask = 0600;
#else
	os_mask = 0777;
#endif

	mask = p_umask(0);
	p_umask(mask);

	cl_git_pass(p_stat("pack-7f5fa362c664d68ba7221259be1cbd187434b2f0.idx", &statbuf));
	cl_assert_equal_i(statbuf.st_mode & os_mask, (expected & ~mask) & os_mask);

	cl_git_pass(p_stat("pack-7f5fa362c664d68ba7221259be1cbd187434b2f0.pack", &statbuf));
	cl_assert_equal_i(statbuf.st_mode & os_mask, (expected & ~mask) & os_mask);
}