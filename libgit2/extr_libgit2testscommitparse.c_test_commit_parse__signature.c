#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int offset; scalar_t__ time; } ;
struct git_signature {int /*<<< orphan*/  email; int /*<<< orphan*/  name; int /*<<< orphan*/  member_0; TYPE_1__ when; } ;
struct TYPE_7__ {char* string; int offset; scalar_t__ time; int /*<<< orphan*/  email; int /*<<< orphan*/  name; int /*<<< orphan*/  header; } ;
typedef  TYPE_2__ passing_signature_test_case ;
typedef  struct git_signature git_signature ;
struct TYPE_8__ {char* string; int /*<<< orphan*/  header; } ;
typedef  TYPE_3__ failing_signature_test_case ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 TYPE_3__* failing_signature_cases ; 
 int /*<<< orphan*/  git__free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_signature__parse (struct git_signature*,char const**,char const*,int /*<<< orphan*/ ,char) ; 
 TYPE_2__* passing_signature_cases ; 
 size_t strlen (char*) ; 

void test_commit_parse__signature(void)
{
	passing_signature_test_case *passcase;
	failing_signature_test_case *failcase;

	for (passcase = passing_signature_cases; passcase->string != NULL; passcase++)
	{
		const char *str = passcase->string;
		size_t len = strlen(passcase->string);
		struct git_signature person = {0};

		cl_git_pass(git_signature__parse(&person, &str, str + len, passcase->header, '\n'));
		cl_assert_equal_s(passcase->name, person.name);
		cl_assert_equal_s(passcase->email, person.email);
		cl_assert_equal_i((int)passcase->time, (int)person.when.time);
		cl_assert_equal_i(passcase->offset, person.when.offset);
		git__free(person.name); git__free(person.email);
	}

	for (failcase = failing_signature_cases; failcase->string != NULL; failcase++)
	{
		const char *str = failcase->string;
		size_t len = strlen(failcase->string);
		git_signature person = {0};
		cl_git_fail(git_signature__parse(&person, &str, str + len, failcase->header, '\n'));
		git__free(person.name); git__free(person.email);
	}
}