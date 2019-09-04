#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  new_name; int /*<<< orphan*/  old_name; } ;
typedef  TYPE_2__ rename_cb_data ;
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_7__ {int /*<<< orphan*/  symbolic; } ;
struct TYPE_9__ {TYPE_1__ target; } ;
typedef  TYPE_3__ git_reference ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_REFERENCE ; 
 scalar_t__ GIT_REFERENCE_SYMBOLIC ; 
 int /*<<< orphan*/  git__free (char*) ; 
 scalar_t__ git__strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 char* git_path_dirname (char const*) ; 
 int git_reference__read_head (TYPE_3__**,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_reference_free (TYPE_3__*) ; 
 scalar_t__ git_reference_type (TYPE_3__*) ; 
 int git_repository_create_head (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int update_wt_heads(git_repository *repo, const char *path, void *payload)
{
	rename_cb_data *data = (rename_cb_data *) payload;
	git_reference *head = NULL;
	char *gitdir = NULL;
	int error;

	if ((error = git_reference__read_head(&head, repo, path)) < 0) {
		git_error_set(GIT_ERROR_REFERENCE, "could not read HEAD when renaming references");
		goto out;
	}

	if ((gitdir = git_path_dirname(path)) == NULL) {
		error = -1;
		goto out;
	}

	if (git_reference_type(head) != GIT_REFERENCE_SYMBOLIC ||
	    git__strcmp(head->target.symbolic, data->old_name) != 0) {
		error = 0;
		goto out;
	}

	/* Update HEAD it was pointing to the reference being renamed */
	if ((error = git_repository_create_head(gitdir, data->new_name)) < 0) {
		git_error_set(GIT_ERROR_REFERENCE, "failed to update HEAD after renaming reference");
		goto out;
	}

out:
	git_reference_free(head);
	git__free(gitdir);

	return error;
}