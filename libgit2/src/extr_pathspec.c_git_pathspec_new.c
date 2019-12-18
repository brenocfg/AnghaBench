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
typedef  int /*<<< orphan*/  git_strarray ;
typedef  int /*<<< orphan*/  git_pathspec ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GIT_REFCOUNT_INC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git__free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git__malloc (int) ; 
 int git_pathspec__init (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

int git_pathspec_new(git_pathspec **out, const git_strarray *pathspec)
{
	int error = 0;
	git_pathspec *ps = git__malloc(sizeof(git_pathspec));
	GIT_ERROR_CHECK_ALLOC(ps);

	if ((error = git_pathspec__init(ps, pathspec)) < 0) {
		git__free(ps);
		return error;
	}

	GIT_REFCOUNT_INC(ps);
	*out = ps;
	return 0;
}