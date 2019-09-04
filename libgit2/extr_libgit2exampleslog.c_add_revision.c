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
struct log_state {int /*<<< orphan*/  repo; } ;
struct TYPE_3__ {int flags; int /*<<< orphan*/ * from; int /*<<< orphan*/ * to; } ;
typedef  TYPE_1__ git_revspec ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_OBJECT_COMMIT ; 
 int GIT_REVPARSE_MERGE_BASE ; 
 int GIT_REVPARSE_SINGLE ; 
 int /*<<< orphan*/  check_lg2 (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  git_merge_base (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_object_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ git_revparse (TYPE_1__*,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ git_revparse_single (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  push_rev (struct log_state*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int add_revision(struct log_state *s, const char *revstr)
{
	git_revspec revs;
	int hide = 0;

	if (!revstr) {
		push_rev(s, NULL, hide);
		return 0;
	}

	if (*revstr == '^') {
		revs.flags = GIT_REVPARSE_SINGLE;
		hide = !hide;

		if (git_revparse_single(&revs.from, s->repo, revstr + 1) < 0)
			return -1;
	} else if (git_revparse(&revs, s->repo, revstr) < 0)
		return -1;

	if ((revs.flags & GIT_REVPARSE_SINGLE) != 0)
		push_rev(s, revs.from, hide);
	else {
		push_rev(s, revs.to, hide);

		if ((revs.flags & GIT_REVPARSE_MERGE_BASE) != 0) {
			git_oid base;
			check_lg2(git_merge_base(&base, s->repo,
				git_object_id(revs.from), git_object_id(revs.to)),
				"Could not find merge base", revstr);
			check_lg2(
				git_object_lookup(&revs.to, s->repo, &base, GIT_OBJECT_COMMIT),
				"Could not find merge base commit", NULL);

			push_rev(s, revs.to, hide);
		}

		push_rev(s, revs.from, !hide);
	}

	return 0;
}