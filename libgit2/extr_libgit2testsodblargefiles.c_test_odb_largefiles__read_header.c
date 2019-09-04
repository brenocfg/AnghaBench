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
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_OBJECT_BLOB ; 
 int /*<<< orphan*/  LARGEFILE_SIZE ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_sz (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_is_env_set (char*) ; 
 int /*<<< orphan*/  cl_skip () ; 
 int /*<<< orphan*/  git_odb_read_header (size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  odb ; 
 int /*<<< orphan*/  writefile (int /*<<< orphan*/ *) ; 

void test_odb_largefiles__read_header(void)
{
	git_oid oid;
	size_t len;
	git_object_t type;

#ifndef GIT_ARCH_64
	cl_skip();
#endif

	if (!cl_is_env_set("GITTEST_INVASIVE_FS_SIZE") ||
		!cl_is_env_set("GITTEST_SLOW"))
		cl_skip();

	writefile(&oid);
	cl_git_pass(git_odb_read_header(&len, &type, odb, &oid));

	cl_assert_equal_sz(LARGEFILE_SIZE, len);
	cl_assert_equal_i(GIT_OBJECT_BLOB, type);
}