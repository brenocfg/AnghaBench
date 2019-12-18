#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_signature ;
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_7__ {int /*<<< orphan*/  oid; } ;
struct TYPE_8__ {TYPE_1__ target; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ git_reference ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_commit ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  commit_type (int /*<<< orphan*/ *) ; 
 int ensure_is_an_updatable_direct_reference (TYPE_2__*) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int git_buf_printf (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * git_commit_committer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int git_commit_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_commit_summary (int /*<<< orphan*/ *) ; 
 int git_reference__update_terminal (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_free (TYPE_2__*) ; 
 int reference__create (TYPE_2__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int git_reference__update_for_commit(
	git_repository *repo,
	git_reference *ref,
	const char *ref_name,
	const git_oid *id,
	const char *operation)
{
	git_reference *ref_new = NULL;
	git_commit *commit = NULL;
	git_buf reflog_msg = GIT_BUF_INIT;
	const git_signature *who;
	int error;

	if ((error = git_commit_lookup(&commit, repo, id)) < 0 ||
		(error = git_buf_printf(&reflog_msg, "%s%s: %s",
			operation ? operation : "commit",
			commit_type(commit),
			git_commit_summary(commit))) < 0)
		goto done;

	who = git_commit_committer(commit);

	if (ref) {
		if ((error = ensure_is_an_updatable_direct_reference(ref)) < 0)
			return error;

		error = reference__create(&ref_new, repo, ref->name, id, NULL, 1, who,
					  git_buf_cstr(&reflog_msg), &ref->target.oid, NULL);
	}
	else
		error = git_reference__update_terminal(
			repo, ref_name, id, who, git_buf_cstr(&reflog_msg));

done:
	git_reference_free(ref_new);
	git_buf_dispose(&reflog_msg);
	git_commit_free(commit);
	return error;
}