#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_4__ {int /*<<< orphan*/  size; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_OBJECT_BLOB ; 
 int /*<<< orphan*/  cl_assert_equal_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_is_env_set (char*) ; 
 int /*<<< orphan*/  cl_skip () ; 
 int /*<<< orphan*/  git_buf_puts (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  git_odb_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  odb ; 

void test_odb_largefiles__write_from_memory(void)
{
	git_oid expected, oid;
	git_buf buf = GIT_BUF_INIT;
	size_t i;

#ifndef GIT_ARCH_64
	cl_skip();
#endif

	if (!cl_is_env_set("GITTEST_INVASIVE_FS_SIZE") ||
		!cl_is_env_set("GITTEST_INVASIVE_MEMORY") ||
		!cl_is_env_set("GITTEST_SLOW"))
		cl_skip();

	for (i = 0; i < (3041*126103); i++)
		cl_git_pass(git_buf_puts(&buf, "Hello, world.\n"));

	git_oid_fromstr(&expected, "3fb56989cca483b21ba7cb0a6edb229d10e1c26c");
	cl_git_pass(git_odb_write(&oid, odb, buf.ptr, buf.size, GIT_OBJECT_BLOB));

	cl_assert_equal_oid(&expected, &oid);
}