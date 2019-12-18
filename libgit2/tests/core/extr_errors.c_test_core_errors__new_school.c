#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct stat {int dummy; } ;
typedef  int /*<<< orphan*/  st ;
struct TYPE_2__ {scalar_t__ klass; int /*<<< orphan*/  message; } ;

/* Variables and functions */
 scalar_t__ GIT_ERROR_NOMEMORY ; 
 int /*<<< orphan*/  GIT_ERROR_OS ; 
 int /*<<< orphan*/  GIT_ERROR_REPOSITORY ; 
 int /*<<< orphan*/  GIT_UNUSED (struct stat) ; 
 scalar_t__ GetProcessId (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 scalar_t__ git__prefixcmp (char*,char*) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 TYPE_1__* git_error_last () ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_error_set_oom () ; 
 int /*<<< orphan*/  memset (struct stat*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ p_lstat (char*,struct stat*) ; 
 scalar_t__ strlen (char*) ; 
 char* strstr (int /*<<< orphan*/ ,char*) ; 

void test_core_errors__new_school(void)
{
	char *str_in_error;

	git_error_clear();
	cl_assert(git_error_last() == NULL);

	git_error_set_oom(); /* internal fn */

	cl_assert(git_error_last() != NULL);
	cl_assert(git_error_last()->klass == GIT_ERROR_NOMEMORY);
	str_in_error = strstr(git_error_last()->message, "memory");
	cl_assert(str_in_error != NULL);

	git_error_clear();

	git_error_set(GIT_ERROR_REPOSITORY, "This is a test"); /* internal fn */

	cl_assert(git_error_last() != NULL);
	str_in_error = strstr(git_error_last()->message, "This is a test");
	cl_assert(str_in_error != NULL);

	git_error_clear();
	cl_assert(git_error_last() == NULL);

	do {
		struct stat st;
		memset(&st, 0, sizeof(st));
		cl_assert(p_lstat("this_file_does_not_exist", &st) < 0);
		GIT_UNUSED(st);
	} while (false);
	git_error_set(GIT_ERROR_OS, "stat failed"); /* internal fn */

	cl_assert(git_error_last() != NULL);
	str_in_error = strstr(git_error_last()->message, "stat failed");
	cl_assert(str_in_error != NULL);
	cl_assert(git__prefixcmp(str_in_error, "stat failed: ") == 0);
	cl_assert(strlen(str_in_error) > strlen("stat failed: "));

#ifdef GIT_WIN32
	git_error_clear();

	/* The MSDN docs use this to generate a sample error */
	cl_assert(GetProcessId(NULL) == 0);
	git_error_set(GIT_ERROR_OS, "GetProcessId failed"); /* internal fn */

	cl_assert(git_error_last() != NULL);
	str_in_error = strstr(git_error_last()->message, "GetProcessId failed");
	cl_assert(str_in_error != NULL);
	cl_assert(git__prefixcmp(str_in_error, "GetProcessId failed: ") == 0);
	cl_assert(strlen(str_in_error) > strlen("GetProcessId failed: "));
#endif

	git_error_clear();
}