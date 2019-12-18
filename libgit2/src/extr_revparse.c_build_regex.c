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
typedef  int /*<<< orphan*/  git_regexp ;

/* Variables and functions */
 int GIT_EINVALIDSPEC ; 
 int /*<<< orphan*/  GIT_ERROR_REGEX ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int git_regexp_compile (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_regexp_dispose (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int build_regex(git_regexp *regex, const char *pattern)
{
	int error;

	if (*pattern == '\0') {
		git_error_set(GIT_ERROR_REGEX, "empty pattern");
		return GIT_EINVALIDSPEC;
	}

	error = git_regexp_compile(regex, pattern, 0);
	if (!error)
		return 0;

	git_regexp_dispose(regex);

	return error;
}