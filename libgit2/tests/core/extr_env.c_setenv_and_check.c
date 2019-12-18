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

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char const*,char*) ; 
 char* cl_getenv (char const*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_setenv (char const*,char const*) ; 
 int /*<<< orphan*/  git__free (char*) ; 

__attribute__((used)) static void setenv_and_check(const char *name, const char *value)
{
	char *check;

	cl_git_pass(cl_setenv(name, value));
	check = cl_getenv(name);

	if (value)
		cl_assert_equal_s(value, check);
	else
		cl_assert(check == NULL);

	git__free(check);
}