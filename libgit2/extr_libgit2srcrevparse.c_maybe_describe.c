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
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_object ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 scalar_t__ build_regex (int /*<<< orphan*/ *,char*) ; 
 int maybe_abbrev (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*) ; 
 int regexec (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regfree (int /*<<< orphan*/ *) ; 
 char* strstr (char const*,char*) ; 

__attribute__((used)) static int maybe_describe(git_object**out, git_repository *repo, const char *spec)
{
	const char *substr;
	int error;
	regex_t regex;

	substr = strstr(spec, "-g");

	if (substr == NULL)
		return GIT_ENOTFOUND;

	if (build_regex(&regex, ".+-[0-9]+-g[0-9a-fA-F]+") < 0)
		return -1;

	error = regexec(&regex, spec, 0, NULL, 0);
	regfree(&regex);

	if (error)
		return GIT_ENOTFOUND;

	return maybe_abbrev(out, repo, substr+2);
}