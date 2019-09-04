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
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_odb ;
struct TYPE_8__ {int /*<<< orphan*/  size; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 int /*<<< orphan*/  GIT_OBJECT_COMMIT ; 
 int /*<<< orphan*/  format_header_field (TYPE_1__*,char const*,char const*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 scalar_t__ git_buf_oom (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_put (TYPE_1__*,char const*,int) ; 
 int /*<<< orphan*/  git_buf_puts (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int git_odb_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int git_repository_odb__weakptr (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 char* strstr (char const*,char*) ; 

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

	/* We start by identifying the end of the commit header */
	header_end = strstr(commit_content, "\n\n");
	if (!header_end) {
		git_error_set(GIT_ERROR_INVALID, "malformed commit contents");
		return -1;
	}

	field = signature_field ? signature_field : "gpgsig";

	/* The header ends after the first LF */
	header_end++;
	git_buf_put(&commit, commit_content, header_end - commit_content);
	format_header_field(&commit, field, signature);
	git_buf_puts(&commit, header_end);

	if (git_buf_oom(&commit))
		return -1;

	if ((error = git_repository_odb__weakptr(&odb, repo)) < 0)
		goto cleanup;

	if ((error = git_odb_write(out, odb, commit.ptr, commit.size, GIT_OBJECT_COMMIT)) < 0)
		goto cleanup;

cleanup:
	git_buf_dispose(&commit);
	return error;
}