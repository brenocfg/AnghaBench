#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  from; int /*<<< orphan*/  flags; int /*<<< orphan*/  to; } ;
typedef  TYPE_1__ git_revspec ;
typedef  int /*<<< orphan*/  git_repository ;

/* Variables and functions */
 int GIT_EINVALIDSPEC ; 
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 int /*<<< orphan*/  GIT_REVPARSE_MERGE_BASE ; 
 int /*<<< orphan*/  GIT_REVPARSE_RANGE ; 
 int /*<<< orphan*/  GIT_REVPARSE_SINGLE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git__free (void*) ; 
 int /*<<< orphan*/  git__strcmp (char const*,char*) ; 
 char* git__substrdup (char const*,int) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int git_revparse_single (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 
 char* strstr (char const*,char*) ; 

int git_revparse(
	git_revspec *revspec,
	git_repository *repo,
	const char *spec)
{
	const char *dotdot;
	int error = 0;

	assert(revspec && repo && spec);

	memset(revspec, 0x0, sizeof(*revspec));

	if ((dotdot = strstr(spec, "..")) != NULL) {
		char *lstr;
		const char *rstr;
		revspec->flags = GIT_REVPARSE_RANGE;

		/*
		 * Following git.git, don't allow '..' because it makes command line
		 * arguments which can be either paths or revisions ambiguous when the
		 * path is almost certainly intended. The empty range '...' is still
		 * allowed.
		 */
		if (!git__strcmp(spec, "..")) {
			git_error_set(GIT_ERROR_INVALID, "Invalid pattern '..'");
			return GIT_EINVALIDSPEC;
		}

		lstr = git__substrdup(spec, dotdot - spec);
		rstr = dotdot + 2;
		if (dotdot[2] == '.') {
			revspec->flags |= GIT_REVPARSE_MERGE_BASE;
			rstr++;
		}

		error = git_revparse_single(
			&revspec->from,
			repo,
			*lstr == '\0' ? "HEAD" : lstr);

		if (!error) {
			error = git_revparse_single(
				&revspec->to,
				repo,
				*rstr == '\0' ? "HEAD" : rstr);
		}

		git__free((void*)lstr);
	} else {
		revspec->flags = GIT_REVPARSE_SINGLE;
		error = git_revparse_single(&revspec->from, repo, spec);
	}

	return error;
}