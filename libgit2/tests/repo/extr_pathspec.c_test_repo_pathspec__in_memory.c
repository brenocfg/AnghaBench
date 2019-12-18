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
struct TYPE_3__ {char** member_0; int /*<<< orphan*/  member_1; } ;
typedef  TYPE_1__ git_strarray ;
typedef  int /*<<< orphan*/  git_pathspec ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (char**) ; 
 int /*<<< orphan*/  GIT_PATHSPEC_IGNORE_CASE ; 
 int /*<<< orphan*/  GIT_PATHSPEC_NO_GLOB ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_pathspec_free (int /*<<< orphan*/ *) ; 
 int git_pathspec_matches_path (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_pathspec_new (int /*<<< orphan*/ **,TYPE_1__*) ; 

void test_repo_pathspec__in_memory(void)
{
	static char *strings[] = { "one", "two*", "!three*", "*four" };
	git_strarray s = { strings, ARRAY_SIZE(strings) };
	git_pathspec *ps;

	cl_git_pass(git_pathspec_new(&ps, &s));

	cl_assert(git_pathspec_matches_path(ps, 0, "one"));
	cl_assert(!git_pathspec_matches_path(ps, 0, "ONE"));
	cl_assert(git_pathspec_matches_path(ps, GIT_PATHSPEC_IGNORE_CASE, "ONE"));
	cl_assert(git_pathspec_matches_path(ps, 0, "two"));
	cl_assert(git_pathspec_matches_path(ps, 0, "two.txt"));
	cl_assert(!git_pathspec_matches_path(ps, 0, "three.txt"));
	cl_assert(git_pathspec_matches_path(ps, 0, "anything.four"));
	cl_assert(!git_pathspec_matches_path(ps, 0, "three.four"));
	cl_assert(!git_pathspec_matches_path(ps, 0, "nomatch"));
	cl_assert(!git_pathspec_matches_path(ps, GIT_PATHSPEC_NO_GLOB, "two"));
	cl_assert(git_pathspec_matches_path(ps, GIT_PATHSPEC_NO_GLOB, "two*"));
	cl_assert(!git_pathspec_matches_path(ps, GIT_PATHSPEC_NO_GLOB, "anyfour"));
	cl_assert(git_pathspec_matches_path(ps, GIT_PATHSPEC_NO_GLOB, "*four"));

	git_pathspec_free(ps);
}