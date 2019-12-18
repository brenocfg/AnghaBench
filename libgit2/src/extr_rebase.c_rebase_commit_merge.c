#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_signature ;
typedef  int /*<<< orphan*/  git_reference ;
struct TYPE_8__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ git_rebase_operation ;
struct TYPE_9__ {int /*<<< orphan*/  repo; int /*<<< orphan*/  current; int /*<<< orphan*/  operations; } ;
typedef  TYPE_2__ git_rebase ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object ;
typedef  int /*<<< orphan*/  git_index ;
typedef  int /*<<< orphan*/  git_commit ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_EUNMERGED ; 
 int /*<<< orphan*/  GIT_OBJECT_COMMIT ; 
 int GIT_OID_HEXSZ ; 
 int O_APPEND ; 
 int O_CREAT ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  REWRITTEN_FILE ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 TYPE_1__* git_array_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_commit_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fmt (char*,int /*<<< orphan*/ *) ; 
 int git_reference__update_for_commit (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int git_reference_peel (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int git_repository_head (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int rebase_commit__create (int /*<<< orphan*/ **,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,char const*,char const*) ; 
 int rebase_ensure_not_dirty (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int rebase_setupfile (TYPE_2__*,int /*<<< orphan*/ ,int,char*,int,char*,int,char*) ; 

__attribute__((used)) static int rebase_commit_merge(
	git_oid *commit_id,
	git_rebase *rebase,
	const git_signature *author,
	const git_signature *committer,
	const char *message_encoding,
	const char *message)
{
	git_rebase_operation *operation;
	git_reference *head = NULL;
	git_commit *head_commit = NULL, *commit = NULL;
	git_index *index = NULL;
	char old_idstr[GIT_OID_HEXSZ], new_idstr[GIT_OID_HEXSZ];
	int error;

	operation = git_array_get(rebase->operations, rebase->current);
	assert(operation);

	if ((error = rebase_ensure_not_dirty(rebase->repo, false, true, GIT_EUNMERGED)) < 0 ||
		(error = git_repository_head(&head, rebase->repo)) < 0 ||
		(error = git_reference_peel((git_object **)&head_commit, head, GIT_OBJECT_COMMIT)) < 0 ||
		(error = git_repository_index(&index, rebase->repo)) < 0 ||
		(error = rebase_commit__create(&commit, rebase, index, head_commit,
			author, committer, message_encoding, message)) < 0 ||
		(error = git_reference__update_for_commit(
			rebase->repo, NULL, "HEAD", git_commit_id(commit), "rebase")) < 0)
		goto done;

	git_oid_fmt(old_idstr, &operation->id);
	git_oid_fmt(new_idstr, git_commit_id(commit));

	if ((error = rebase_setupfile(rebase, REWRITTEN_FILE, O_CREAT|O_WRONLY|O_APPEND,
		"%.*s %.*s\n", GIT_OID_HEXSZ, old_idstr, GIT_OID_HEXSZ, new_idstr)) < 0)
		goto done;

	git_oid_cpy(commit_id, git_commit_id(commit));

done:
	git_index_free(index);
	git_reference_free(head);
	git_commit_free(head_commit);
	git_commit_free(commit);
	return error;
}