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
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_HEAD_FILE ; 
 int /*<<< orphan*/  GIT_OBJECT_ANY ; 
 int /*<<< orphan*/  GIT_OBJECT_COMMIT ; 
 int /*<<< orphan*/  assert (int) ; 
 int checkout_message (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_id (int /*<<< orphan*/ *) ; 
 int git_object_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int git_object_peel (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* git_oid_tostr_s (int /*<<< orphan*/ ) ; 
 int git_reference_create (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int detach(git_repository *repo, const git_oid *id, const char *new)
{
	int error;
	git_buf log_message = GIT_BUF_INIT;
	git_object *object = NULL, *peeled = NULL;
	git_reference *new_head = NULL, *current = NULL;

	assert(repo && id);

	if ((error = git_reference_lookup(&current, repo, GIT_HEAD_FILE)) < 0)
		return error;

	if ((error = git_object_lookup(&object, repo, id, GIT_OBJECT_ANY)) < 0)
		goto cleanup;

	if ((error = git_object_peel(&peeled, object, GIT_OBJECT_COMMIT)) < 0)
		goto cleanup;

	if (new == NULL)
		new = git_oid_tostr_s(git_object_id(peeled));

	if ((error = checkout_message(&log_message, current, new)) < 0)
		goto cleanup;

	error = git_reference_create(&new_head, repo, GIT_HEAD_FILE, git_object_id(peeled), true, git_buf_cstr(&log_message));

cleanup:
	git_buf_dispose(&log_message);
	git_object_free(object);
	git_object_free(peeled);
	git_reference_free(current);
	git_reference_free(new_head);
	return error;
}