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
typedef  int /*<<< orphan*/  git_regexp ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object ;
typedef  int /*<<< orphan*/  git_commit ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 int GIT_ITEROVER ; 
 int /*<<< orphan*/  GIT_OBJECT_COMMIT ; 
 int /*<<< orphan*/  git_commit_message (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int git_object_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_regexp_match (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int git_revwalk_next (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_revwalk_repository (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int walk_and_search(git_object **out, git_revwalk *walk, git_regexp *regex)
{
	int error;
	git_oid oid;
	git_object *obj;

	while (!(error = git_revwalk_next(&oid, walk))) {

		error = git_object_lookup(&obj, git_revwalk_repository(walk), &oid, GIT_OBJECT_COMMIT);
		if ((error < 0) && (error != GIT_ENOTFOUND))
			return -1;

		if (!git_regexp_match(regex, git_commit_message((git_commit*)obj))) {
			*out = obj;
			return 0;
		}

		git_object_free(obj);
	}

	if (error < 0 && error == GIT_ITEROVER)
		error = GIT_ENOTFOUND;

	return error;
}