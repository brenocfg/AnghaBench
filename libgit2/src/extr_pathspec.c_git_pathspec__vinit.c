#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_vector ;
struct TYPE_9__ {size_t count; char** strings; } ;
typedef  TYPE_1__ git_strarray ;
typedef  int /*<<< orphan*/  git_pool ;
struct TYPE_10__ {int flags; } ;
typedef  TYPE_2__ git_attr_fnmatch ;

/* Variables and functions */
 int GIT_ATTR_FNMATCH_ALLOWNEG ; 
 int GIT_ATTR_FNMATCH_ALLOWSPACE ; 
 int GIT_ENOTFOUND ; 
 TYPE_2__* git__calloc (int,int) ; 
 int /*<<< orphan*/  git__free (TYPE_2__*) ; 
 int git_attr_fnmatch__parse (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**) ; 
 scalar_t__ git_pathspec_is_empty (TYPE_1__ const*) ; 
 scalar_t__ git_vector_init (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ git_vector_insert (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int git_pathspec__vinit(
	git_vector *vspec, const git_strarray *strspec, git_pool *strpool)
{
	size_t i;

	memset(vspec, 0, sizeof(*vspec));

	if (git_pathspec_is_empty(strspec))
		return 0;

	if (git_vector_init(vspec, strspec->count, NULL) < 0)
		return -1;

	for (i = 0; i < strspec->count; ++i) {
		int ret;
		const char *pattern = strspec->strings[i];
		git_attr_fnmatch *match = git__calloc(1, sizeof(git_attr_fnmatch));
		if (!match)
			return -1;

		match->flags = GIT_ATTR_FNMATCH_ALLOWSPACE | GIT_ATTR_FNMATCH_ALLOWNEG;

		ret = git_attr_fnmatch__parse(match, strpool, NULL, &pattern);
		if (ret == GIT_ENOTFOUND) {
			git__free(match);
			continue;
		} else if (ret < 0) {
			git__free(match);
			return ret;
		}

		if (git_vector_insert(vspec, match) < 0)
			return -1;
	}

	return 0;
}