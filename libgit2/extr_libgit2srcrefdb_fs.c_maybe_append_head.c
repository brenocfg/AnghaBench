#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  repo; } ;
typedef  TYPE_1__ refdb_fs_backend ;
typedef  int /*<<< orphan*/  old_id ;
typedef  int /*<<< orphan*/  git_signature ;
struct TYPE_14__ {scalar_t__ type; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ git_reference ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 char* GIT_HEAD_FILE ; 
 scalar_t__ GIT_REFERENCE_DIRECT ; 
 scalar_t__ GIT_REFERENCE_SYMBOLIC ; 
 int /*<<< orphan*/  git_reference_free (TYPE_2__*) ; 
 int git_reference_lookup (TYPE_2__**,int /*<<< orphan*/ ,char*) ; 
 char* git_reference_name (TYPE_2__*) ; 
 scalar_t__ git_reference_name_to_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* git_reference_symbolic_target (TYPE_2__*) ; 
 int /*<<< orphan*/  git_reference_target (TYPE_2__ const*) ; 
 scalar_t__ git_reference_type (TYPE_2__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int reflog_append (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,char const*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int maybe_append_head(refdb_fs_backend *backend, const git_reference *ref, const git_signature *who, const char *message)
{
	int error;
	git_oid old_id;
	git_reference *tmp = NULL, *head = NULL, *peeled = NULL;
	const char *name;

	if (ref->type == GIT_REFERENCE_SYMBOLIC)
		return 0;

	/* if we can't resolve, we use {0}*40 as old id */
	if (git_reference_name_to_id(&old_id, backend->repo, ref->name) < 0)
		memset(&old_id, 0, sizeof(old_id));

	if ((error = git_reference_lookup(&head, backend->repo, GIT_HEAD_FILE)) < 0)
		return error;

	if (git_reference_type(head) == GIT_REFERENCE_DIRECT)
		goto cleanup;

	if ((error = git_reference_lookup(&tmp, backend->repo, GIT_HEAD_FILE)) < 0)
		goto cleanup;

	/* Go down the symref chain until we find the branch */
	while (git_reference_type(tmp) == GIT_REFERENCE_SYMBOLIC) {
		error = git_reference_lookup(&peeled, backend->repo, git_reference_symbolic_target(tmp));
		if (error < 0)
			break;

		git_reference_free(tmp);
		tmp = peeled;
	}

	if (error == GIT_ENOTFOUND) {
		error = 0;
		name = git_reference_symbolic_target(tmp);
	} else if (error < 0) {
		goto cleanup;
	} else {
		name = git_reference_name(tmp);
	}

	if (strcmp(name, ref->name))
		goto cleanup;

	error = reflog_append(backend, head, &old_id, git_reference_target(ref), who, message);

cleanup:
	git_reference_free(tmp);
	git_reference_free(head);
	return error;
}