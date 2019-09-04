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
struct TYPE_4__ {char* line; int /*<<< orphan*/  header; } ;
typedef  TYPE_1__ parse_test_case ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 TYPE_1__* failing_header_cases ; 
 int /*<<< orphan*/  git_oid__parse (int /*<<< orphan*/ *,char const**,char const*,int /*<<< orphan*/ ) ; 
 TYPE_1__* passing_header_cases ; 
 int strlen (char const*) ; 

void test_commit_parse__header(void)
{
	git_oid oid;

	parse_test_case *testcase;
	for (testcase = passing_header_cases; testcase->line != NULL; testcase++)
	{
		const char *line = testcase->line;
		const char *line_end = line + strlen(line);

		cl_git_pass(git_oid__parse(&oid, &line, line_end, testcase->header));
		cl_assert(line == line_end);
	}

	for (testcase = failing_header_cases; testcase->line != NULL; testcase++)
	{
		const char *line = testcase->line;
		const char *line_end = line + strlen(line);

		cl_git_fail(git_oid__parse(&oid, &line, line_end, testcase->header));
	}
}