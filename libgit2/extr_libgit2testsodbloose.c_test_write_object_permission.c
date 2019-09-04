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
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_odb_backend ;
typedef  int /*<<< orphan*/  git_odb ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_OBJECT_BLOB ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_odb_add_backend (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  git_odb_backend_loose (int /*<<< orphan*/ **,char*,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  git_odb_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_odb_new (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  git_odb_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_stat (char*,struct stat*) ; 
 int p_umask (int) ; 

void test_write_object_permission(
	mode_t dir_mode, mode_t file_mode,
	mode_t expected_dir_mode, mode_t expected_file_mode)
{
	git_odb *odb;
	git_odb_backend *backend;
	git_oid oid;
	struct stat statbuf;
	mode_t mask, os_mask;

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

	cl_git_pass(git_odb_new(&odb));
	cl_git_pass(git_odb_backend_loose(&backend, "test-objects", -1, 0, dir_mode, file_mode));
	cl_git_pass(git_odb_add_backend(odb, backend, 1));
	cl_git_pass(git_odb_write(&oid, odb, "Test data\n", 10, GIT_OBJECT_BLOB));

	cl_git_pass(p_stat("test-objects/67", &statbuf));
	cl_assert_equal_i(statbuf.st_mode & os_mask, (expected_dir_mode & ~mask) & os_mask);

	cl_git_pass(p_stat("test-objects/67/b808feb36201507a77f85e6d898f0a2836e4a5", &statbuf));
	cl_assert_equal_i(statbuf.st_mode & os_mask, (expected_file_mode & ~mask) & os_mask);

	git_odb_free(odb);
}