#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_odb ;
struct TYPE_14__ {int /*<<< orphan*/  tree_id; } ;
typedef  TYPE_1__ git_commit ;
struct TYPE_15__ {int /*<<< orphan*/  size; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_2__ git_buf ;
typedef  int /*<<< orphan*/  git_array_oid_t ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ARRAY_INIT ; 
 TYPE_2__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_1__*) ; 
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 int /*<<< orphan*/  GIT_OBJECT_COMMIT ; 
 int /*<<< orphan*/  commit_parent_from_commit ; 
 int commit_parse (TYPE_1__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_header_field (TYPE_2__*,char const*,char const*) ; 
 TYPE_1__* git__calloc (int,int) ; 
 int /*<<< orphan*/  git_array_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_2__*) ; 
 scalar_t__ git_buf_oom (TYPE_2__*) ; 
 int /*<<< orphan*/  git_buf_put (TYPE_2__*,char const*,int) ; 
 int /*<<< orphan*/  git_buf_puts (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  git_commit__free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int git_odb_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int git_repository_odb__weakptr (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 char* strstr (char const*,char*) ; 
 int validate_tree_and_parents (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int) ; 

int git_commit_create_with_signature(
	git_oid *out,
	git_repository *repo,
	const char *commit_content,
	const char *signature,
	const char *signature_field)
{
	git_odb *odb;
	int error = 0;
	const char *field;
	const char *header_end;
	git_buf commit = GIT_BUF_INIT;
	git_commit *parsed;
	git_array_oid_t parents = GIT_ARRAY_INIT;

	/* The first step is to verify that all the tree and parents exist */
	parsed = git__calloc(1, sizeof(git_commit));
	GIT_ERROR_CHECK_ALLOC(parsed);
	if ((error = commit_parse(parsed, commit_content, strlen(commit_content), 0)) < 0)
		goto cleanup;

	if ((error = validate_tree_and_parents(&parents, repo, &parsed->tree_id, commit_parent_from_commit, parsed, NULL, true)) < 0)
		goto cleanup;

	git_array_clear(parents);

	/* Then we start appending by identifying the end of the commit header */
	header_end = strstr(commit_content, "\n\n");
	if (!header_end) {
		git_error_set(GIT_ERROR_INVALID, "malformed commit contents");
		error = -1;
		goto cleanup;
	}

	/* The header ends after the first LF */
	header_end++;
	git_buf_put(&commit, commit_content, header_end - commit_content);

	if (signature != NULL) {
		field = signature_field ? signature_field : "gpgsig";
		format_header_field(&commit, field, signature);
	}

	git_buf_puts(&commit, header_end);

	if (git_buf_oom(&commit))
		return -1;

	if ((error = git_repository_odb__weakptr(&odb, repo)) < 0)
		goto cleanup;

	if ((error = git_odb_write(out, odb, commit.ptr, commit.size, GIT_OBJECT_COMMIT)) < 0)
		goto cleanup;

cleanup:
	git_commit__free(parsed);
	git_buf_dispose(&commit);
	return error;
}