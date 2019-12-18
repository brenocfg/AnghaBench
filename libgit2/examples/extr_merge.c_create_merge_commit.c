#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int annotated_count; char** heads; int /*<<< orphan*/ ** annotated; } ;
typedef  TYPE_1__ merge_options ;
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_signature ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object ;
typedef  int /*<<< orphan*/  git_index ;
typedef  int /*<<< orphan*/  git_commit ;
typedef  int /*<<< orphan*/  git_annotated_commit ;
struct TYPE_5__ {int /*<<< orphan*/ * message; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_OBJECT_COMMIT ; 
 char* MERGE_COMMIT_MSG ; 
 int /*<<< orphan*/ ** calloc (int,int) ; 
 int /*<<< orphan*/  check_lg2 (int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  git_annotated_commit_id (int /*<<< orphan*/ *) ; 
 int git_branch_name (char const**,int /*<<< orphan*/ *) ; 
 int git_commit_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  git_commit_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* git_error_last () ; 
 int git_index_write_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* git_oid_tostr_s (int /*<<< orphan*/ ) ; 
 int git_reference_dwim (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_reference_name (int /*<<< orphan*/ *) ; 
 int git_reference_peel (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int git_repository_head (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_state_cleanup (int /*<<< orphan*/ *) ; 
 int git_signature_now (int /*<<< orphan*/ **,char*,char*) ; 
 int git_tree_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* malloc (size_t) ; 
 scalar_t__ resolve_refish (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*) ; 
 void* snprintf (char*,size_t,char*,char*,char const*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int create_merge_commit(git_repository *repo, git_index *index, merge_options *opts)
{
	git_oid tree_oid, commit_oid;
	git_tree *tree;
	git_signature *sign;
	git_reference *merge_ref = NULL;
	git_annotated_commit *merge_commit;
	git_reference *head_ref;
	git_commit **parents = calloc(opts->annotated_count + 1, sizeof(git_commit *));
	const char *msg_target = NULL;
	size_t msglen = 0;
	char *msg;
	size_t i;
	int err;

	/* Grab our needed references */
	check_lg2(git_repository_head(&head_ref, repo), "failed to get repo HEAD", NULL);
	if (resolve_refish(&merge_commit, repo, opts->heads[0])) {
		fprintf(stderr, "failed to resolve refish %s", opts->heads[0]);
		free(parents);
		return -1;
	}

	/* Maybe that's a ref, so DWIM it */
	err = git_reference_dwim(&merge_ref, repo, opts->heads[0]);
	check_lg2(err, "failed to DWIM reference", git_error_last()->message);

	/* Grab a signature */
	check_lg2(git_signature_now(&sign, "Me", "me@example.com"), "failed to create signature", NULL);

#define MERGE_COMMIT_MSG "Merge %s '%s'"
	/* Prepare a standard merge commit message */
	if (merge_ref != NULL) {
		check_lg2(git_branch_name(&msg_target, merge_ref), "failed to get branch name of merged ref", NULL);
	} else {
		msg_target = git_oid_tostr_s(git_annotated_commit_id(merge_commit));
	}

	msglen = snprintf(NULL, 0, MERGE_COMMIT_MSG, (merge_ref ? "branch" : "commit"), msg_target);
	if (msglen > 0) msglen++;
	msg = malloc(msglen);
	err = snprintf(msg, msglen, MERGE_COMMIT_MSG, (merge_ref ? "branch" : "commit"), msg_target);

	/* This is only to silence the compiler */
	if (err < 0) goto cleanup;

	/* Setup our parent commits */
	err = git_reference_peel((git_object **)&parents[0], head_ref, GIT_OBJECT_COMMIT);
	check_lg2(err, "failed to peel head reference", NULL);
	for (i = 0; i < opts->annotated_count; i++) {
		git_commit_lookup(&parents[i + 1], repo, git_annotated_commit_id(opts->annotated[i]));
	}

	/* Prepare our commit tree */
	check_lg2(git_index_write_tree(&tree_oid, index), "failed to write merged tree", NULL);
	check_lg2(git_tree_lookup(&tree, repo, &tree_oid), "failed to lookup tree", NULL);

	/* Commit time ! */
	err = git_commit_create(&commit_oid,
	                        repo, git_reference_name(head_ref),
	                        sign, sign,
	                        NULL, msg,
	                        tree,
	                        opts->annotated_count + 1, (const git_commit **)parents);
	check_lg2(err, "failed to create commit", NULL);

	/* We're done merging, cleanup the repository state */
	git_repository_state_cleanup(repo);

cleanup:
	free(parents);
	return err;
}