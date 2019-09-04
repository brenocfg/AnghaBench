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
typedef  int /*<<< orphan*/  regex_t ;

/* Variables and functions */
 int GIT_EINVALIDSPEC ; 
 int /*<<< orphan*/  GIT_ERROR_REGEX ; 
 int /*<<< orphan*/  REG_EXTENDED ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int git_error_set_regex (int /*<<< orphan*/ *,int) ; 
 int p_regcomp (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int build_regex(regex_t *regex, const char *pattern)
{
	int error;

	if (*pattern == '\0') {
		git_error_set(GIT_ERROR_REGEX, "empty pattern");
		return GIT_EINVALIDSPEC;
	}

	error = p_regcomp(regex, pattern, REG_EXTENDED);
	if (!error)
		return 0;

	error = git_error_set_regex(regex, error);

	regfree(regex);

	return error;
}