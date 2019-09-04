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
typedef  int uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  pathspec; } ;
typedef  TYPE_1__ git_pathspec ;

/* Variables and functions */
 int GIT_PATHSPEC_IGNORE_CASE ; 
 int GIT_PATHSPEC_NO_GLOB ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ git_pathspec__match (int /*<<< orphan*/ *,char const*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int git_pathspec_matches_path(
	const git_pathspec *ps, uint32_t flags, const char *path)
{
	bool no_fnmatch = (flags & GIT_PATHSPEC_NO_GLOB) != 0;
	bool casefold =  (flags & GIT_PATHSPEC_IGNORE_CASE) != 0;

	assert(ps && path);

	return (0 != git_pathspec__match(
		&ps->pathspec, path, no_fnmatch, casefold, NULL, NULL));
}