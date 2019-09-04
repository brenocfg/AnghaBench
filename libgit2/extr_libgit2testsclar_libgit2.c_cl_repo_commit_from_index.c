#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_time_t ;
struct TYPE_8__ {scalar_t__ email; scalar_t__ name; } ;
typedef  TYPE_1__ git_signature ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object ;
typedef  int /*<<< orphan*/  git_index ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  CL_COMMIT_EMAIL ; 
 int /*<<< orphan*/  CL_COMMIT_MSG ; 
 int /*<<< orphan*/  CL_COMMIT_NAME ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_commit_create_v (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_write_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_tostr (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 char* git_reference_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_revparse_ext (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_signature_free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_signature_new (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_signature_now (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ ) ; 

void cl_repo_commit_from_index(
	git_oid *out,
	git_repository *repo,
	git_signature *sig,
	git_time_t time,
	const char *msg)
{
	git_index *index;
	git_oid commit_id, tree_id;
	git_object *parent = NULL;
	git_reference *ref = NULL;
	git_tree *tree = NULL;
	char buf[128];
	int free_sig = (sig == NULL);

	/* it is fine if looking up HEAD fails - we make this the first commit */
	git_revparse_ext(&parent, &ref, repo, "HEAD");

	/* write the index content as a tree */
	cl_git_pass(git_repository_index(&index, repo));
	cl_git_pass(git_index_write_tree(&tree_id, index));
	cl_git_pass(git_index_write(index));
	git_index_free(index);

	cl_git_pass(git_tree_lookup(&tree, repo, &tree_id));

	if (sig)
		cl_assert(sig->name && sig->email);
	else if (!time)
		cl_git_pass(git_signature_now(&sig, CL_COMMIT_NAME, CL_COMMIT_EMAIL));
	else
		cl_git_pass(git_signature_new(
			&sig, CL_COMMIT_NAME, CL_COMMIT_EMAIL, time, 0));

	if (!msg) {
		strcpy(buf, CL_COMMIT_MSG);
		git_oid_tostr(buf + strlen(CL_COMMIT_MSG),
			sizeof(buf) - strlen(CL_COMMIT_MSG), &tree_id);
		msg = buf;
	}

	cl_git_pass(git_commit_create_v(
		&commit_id, repo, ref ? git_reference_name(ref) : "HEAD",
		sig, sig, NULL, msg, tree, parent ? 1 : 0, parent));

	if (out)
		git_oid_cpy(out, &commit_id);

	git_object_free(parent);
	git_reference_free(ref);
	if (free_sig)
		git_signature_free(sig);
	git_tree_free(tree);
}