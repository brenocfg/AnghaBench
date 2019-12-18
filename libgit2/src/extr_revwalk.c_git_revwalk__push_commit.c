#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ insert_by_date; scalar_t__ uninteresting; scalar_t__ from_glob; } ;
typedef  TYPE_1__ git_revwalk__push_options ;
struct TYPE_11__ {int limited; int did_hide; int did_push; int /*<<< orphan*/ * user_input; int /*<<< orphan*/  repo; } ;
typedef  TYPE_2__ git_revwalk ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object ;
struct TYPE_12__ {scalar_t__ uninteresting; } ;
typedef  TYPE_3__ git_commit_list_node ;
typedef  int /*<<< orphan*/  git_commit_list ;

/* Variables and functions */
 int GIT_EINVALIDSPEC ; 
 int GIT_ENOTFOUND ; 
 int GIT_EPEEL ; 
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 int /*<<< orphan*/  GIT_OBJECT_ANY ; 
 int /*<<< orphan*/  GIT_OBJECT_COMMIT ; 
 int /*<<< orphan*/ * git_commit_list_insert (TYPE_3__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * git_commit_list_insert_by_date (TYPE_3__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_error_set_oom () ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_id (int /*<<< orphan*/ *) ; 
 int git_object_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int git_object_peel (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* git_revwalk__commit_lookup (TYPE_2__*,int /*<<< orphan*/ *) ; 

int git_revwalk__push_commit(git_revwalk *walk, const git_oid *oid, const git_revwalk__push_options *opts)
{
	git_oid commit_id;
	int error;
	git_object *obj, *oobj;
	git_commit_list_node *commit;
	git_commit_list *list;

	if ((error = git_object_lookup(&oobj, walk->repo, oid, GIT_OBJECT_ANY)) < 0)
		return error;

	error = git_object_peel(&obj, oobj, GIT_OBJECT_COMMIT);
	git_object_free(oobj);

	if (error == GIT_ENOTFOUND || error == GIT_EINVALIDSPEC || error == GIT_EPEEL) {
		/* If this comes from e.g. push_glob("tags"), ignore this */
		if (opts->from_glob)
			return 0;

		git_error_set(GIT_ERROR_INVALID, "object is not a committish");
		return -1;
	}
	if (error < 0)
		return error;

	git_oid_cpy(&commit_id, git_object_id(obj));
	git_object_free(obj);

	commit = git_revwalk__commit_lookup(walk, &commit_id);
	if (commit == NULL)
		return -1; /* error already reported by failed lookup */

	/* A previous hide already told us we don't want this commit  */
	if (commit->uninteresting)
		return 0;

	if (opts->uninteresting) {
		walk->limited = 1;
		walk->did_hide = 1;
	} else {
		walk->did_push = 1;
	}

	commit->uninteresting = opts->uninteresting;
	list = walk->user_input;
	if ((opts->insert_by_date &&
	    git_commit_list_insert_by_date(commit, &list) == NULL) ||
	    git_commit_list_insert(commit, &list) == NULL) {
		git_error_set_oom();
		return -1;
	}

	walk->user_input = list;

	return 0;
}