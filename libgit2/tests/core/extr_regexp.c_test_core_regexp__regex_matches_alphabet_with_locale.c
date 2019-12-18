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
 int /*<<< orphan*/  LC_COLLATE ; 
 int /*<<< orphan*/  LC_CTYPE ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_skip () ; 
 int /*<<< orphan*/  git_regexp_compile (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_regexp_match (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  regex ; 
 int /*<<< orphan*/  try_set_locale (int /*<<< orphan*/ ) ; 

void test_core_regexp__regex_matches_alphabet_with_locale(void)
{
	char c, str[2];

#ifdef GIT_WIN32
	cl_skip();
#endif

	try_set_locale(LC_COLLATE);
	try_set_locale(LC_CTYPE);

	cl_git_pass(git_regexp_compile(&regex, "[[:alpha:]]", 0));

	str[1] = '\0';
	for (c = 'a'; c <= 'z'; c++) {
	    str[0] = c;
	    cl_git_pass(git_regexp_match(&regex, str));
	}
	for (c = 'A'; c <= 'Z'; c++) {
	    str[0] = c;
	    cl_git_pass(git_regexp_match(&regex, str));
	}
}