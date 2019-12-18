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
struct TYPE_2__ {scalar_t__ klass; int /*<<< orphan*/  message; } ;

/* Variables and functions */
 scalar_t__ GIT_ERROR_NOMEMORY ; 
 int /*<<< orphan*/  GIT_ERROR_REPOSITORY ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 TYPE_1__* git_error_last () ; 
 int /*<<< orphan*/  git_error_set_oom () ; 
 int /*<<< orphan*/  git_error_set_str (int /*<<< orphan*/ ,char*) ; 
 char* strstr (int /*<<< orphan*/ ,char*) ; 

void test_core_errors__public_api(void)
{
	char *str_in_error;

	git_error_clear();
	cl_assert(git_error_last() == NULL);

	git_error_set_oom();

	cl_assert(git_error_last() != NULL);
	cl_assert(git_error_last()->klass == GIT_ERROR_NOMEMORY);
	str_in_error = strstr(git_error_last()->message, "memory");
	cl_assert(str_in_error != NULL);

	git_error_clear();

	git_error_set_str(GIT_ERROR_REPOSITORY, "This is a test");

	cl_assert(git_error_last() != NULL);
	str_in_error = strstr(git_error_last()->message, "This is a test");
	cl_assert(str_in_error != NULL);

	git_error_clear();
	cl_assert(git_error_last() == NULL);
}