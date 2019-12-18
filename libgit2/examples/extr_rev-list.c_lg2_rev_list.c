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
typedef  int /*<<< orphan*/  git_revwalk ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int GIT_OID_HEXSZ ; 
 int /*<<< orphan*/  check_lg2 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fmt (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_revwalk_new (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_revwalk_next (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  revwalk_parseopts (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char**) ; 

int lg2_rev_list(git_repository *repo, int argc, char **argv)
{
	git_revwalk *walk;
	git_oid oid;
	char buf[GIT_OID_HEXSZ+1];

	check_lg2(git_revwalk_new(&walk, repo), "allocating revwalk", NULL);
	check_lg2(revwalk_parseopts(repo, walk, argc-1, argv+1), "parsing options", NULL);

	while (!git_revwalk_next(&oid, walk)) {
		git_oid_fmt(buf, &oid);
		buf[GIT_OID_HEXSZ] = '\0';
		printf("%s\n", buf);
	}

	return 0;
}