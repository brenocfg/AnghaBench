#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_pool ;
struct TYPE_3__ {int length; int /*<<< orphan*/  pattern; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ git_attr_fnmatch ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ATTR_FNMATCH_MATCH_ALL ; 
 int /*<<< orphan*/  git_pool_strndup (int /*<<< orphan*/ *,char const*,int) ; 

__attribute__((used)) static bool parse_optimized_patterns(
	git_attr_fnmatch *spec,
	git_pool *pool,
	const char *pattern)
{
	if (!pattern[1] && (pattern[0] == '*' || pattern[0] == '.')) {
		spec->flags = GIT_ATTR_FNMATCH_MATCH_ALL;
		spec->pattern = git_pool_strndup(pool, pattern, 1);
		spec->length = 1;

		return true;
	}

	return false;
}