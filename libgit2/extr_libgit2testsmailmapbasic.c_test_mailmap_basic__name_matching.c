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
 int /*<<< orphan*/  cl_assert_equal_s (char const*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_mailmap_resolve (char const**,char const**,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  mailmap ; 

void test_mailmap_basic__name_matching(void)
{
	const char *name;
	const char *email;
	cl_git_pass(git_mailmap_resolve(
		&name, &email, mailmap, "Other Name", "yetanotheremail@foo.com"));

	cl_assert_equal_s(name, "Other Name");
	cl_assert_equal_s(email, "email@foo.com");

	cl_git_pass(git_mailmap_resolve(
		&name, &email, mailmap,
		"Other Name That Doesn't Match", "yetanotheremail@foo.com"));
	cl_assert_equal_s(name, "Other Name That Doesn't Match");
	cl_assert_equal_s(email, "yetanotheremail@foo.com");
}