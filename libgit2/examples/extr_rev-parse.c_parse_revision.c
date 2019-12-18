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
struct parse_state {int /*<<< orphan*/  spec; } ;
typedef  int /*<<< orphan*/  str ;
struct TYPE_3__ {int flags; int /*<<< orphan*/  from; int /*<<< orphan*/  to; } ;
typedef  TYPE_1__ git_revspec ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_OID_HEXSZ ; 
 int GIT_REVPARSE_MERGE_BASE ; 
 int GIT_REVPARSE_RANGE ; 
 int GIT_REVPARSE_SINGLE ; 
 int /*<<< orphan*/  check_lg2 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_merge_base (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * git_object_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_tostr (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_revparse (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static int parse_revision(git_repository *repo, struct parse_state *ps)
{
	git_revspec rs;
	char str[GIT_OID_HEXSZ + 1];

	check_lg2(git_revparse(&rs, repo, ps->spec), "Could not parse", ps->spec);

	if ((rs.flags & GIT_REVPARSE_SINGLE) != 0) {
		git_oid_tostr(str, sizeof(str), git_object_id(rs.from));
		printf("%s\n", str);
		git_object_free(rs.from);
	}
	else if ((rs.flags & GIT_REVPARSE_RANGE) != 0) {
		git_oid_tostr(str, sizeof(str), git_object_id(rs.to));
		printf("%s\n", str);
		git_object_free(rs.to);

		if ((rs.flags & GIT_REVPARSE_MERGE_BASE) != 0) {
			git_oid base;
			check_lg2(git_merge_base(&base, repo,
						git_object_id(rs.from), git_object_id(rs.to)),
					"Could not find merge base", ps->spec);

			git_oid_tostr(str, sizeof(str), &base);
			printf("%s\n", str);
		}

		git_oid_tostr(str, sizeof(str), git_object_id(rs.from));
		printf("^%s\n", str);
		git_object_free(rs.from);
	}
	else {
		fatal("Invalid results from git_revparse", ps->spec);
	}

	return 0;
}