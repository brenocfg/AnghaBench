#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* path; int /*<<< orphan*/  mode; } ;
typedef  TYPE_1__ git_index_entry ;
struct TYPE_7__ {int /*<<< orphan*/  pathspec; } ;
typedef  TYPE_2__ git_diff_generated ;

/* Variables and functions */
 int DIFF_FLAG_IS_SET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GIT_DIFF_DISABLE_PATHSPEC_MATCH ; 
 int /*<<< orphan*/  GIT_DIFF_IGNORE_CASE ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int git_pathspec__match (int /*<<< orphan*/ *,char*,int,int,char const**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool diff_pathspec_match(
	const char **matched_pathspec,
	git_diff_generated *diff,
	const git_index_entry *entry)
{
	bool disable_pathspec_match =
		DIFF_FLAG_IS_SET(diff, GIT_DIFF_DISABLE_PATHSPEC_MATCH);

	/* If we're disabling fnmatch, then the iterator has already applied
	 * the filters to the files for us and we don't have to do anything.
	 * However, this only applies to *files* - the iterator will include
	 * directories that we need to recurse into when not autoexpanding,
	 * so we still need to apply the pathspec match to directories.
	 */
	if ((S_ISLNK(entry->mode) || S_ISREG(entry->mode)) &&
		disable_pathspec_match) {
		*matched_pathspec = entry->path;
		return true;
	}

	return git_pathspec__match(
		&diff->pathspec, entry->path, disable_pathspec_match,
		DIFF_FLAG_IS_SET(diff, GIT_DIFF_IGNORE_CASE),
		matched_pathspec, NULL);
}