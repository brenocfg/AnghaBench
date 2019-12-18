#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_3__ {int start; int end; } ;
typedef  TYPE_1__ git_regmatch ;
typedef  int /*<<< orphan*/  git_regexp ;
typedef  int /*<<< orphan*/  git_reflog_entry ;
typedef  int /*<<< orphan*/  git_reflog ;
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_object ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int GIT_EINVALIDSPEC ; 
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_HEAD_FILE ; 
 scalar_t__ build_regex (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 scalar_t__ git_buf_put (int /*<<< orphan*/ *,char const*,int) ; 
 int git_reference_dwim (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 scalar_t__ git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * git_reflog_entry_byindex (int /*<<< orphan*/ *,size_t) ; 
 char* git_reflog_entry_message (int /*<<< orphan*/  const*) ; 
 size_t git_reflog_entrycount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reflog_free (int /*<<< orphan*/ *) ; 
 scalar_t__ git_reflog_read (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_regexp_dispose (int /*<<< orphan*/ *) ; 
 scalar_t__ git_regexp_search (int /*<<< orphan*/ *,char const*,int,TYPE_1__*) ; 
 int maybe_abbrev (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int retrieve_previously_checked_out_branch_or_revision(git_object **out, git_reference **base_ref, git_repository *repo, const char *identifier, size_t position)
{
	git_reference *ref = NULL;
	git_reflog *reflog = NULL;
	git_regexp preg;
	int error = -1;
	size_t i, numentries, cur;
	const git_reflog_entry *entry;
	const char *msg;
	git_buf buf = GIT_BUF_INIT;

	cur = position;

	if (*identifier != '\0' || *base_ref != NULL)
		return GIT_EINVALIDSPEC;

	if (build_regex(&preg, "checkout: moving from (.*) to .*") < 0)
		return -1;

	if (git_reference_lookup(&ref, repo, GIT_HEAD_FILE) < 0)
		goto cleanup;

	if (git_reflog_read(&reflog, repo, GIT_HEAD_FILE) < 0)
		goto cleanup;

	numentries  = git_reflog_entrycount(reflog);

	for (i = 0; i < numentries; i++) {
		git_regmatch regexmatches[2];

		entry = git_reflog_entry_byindex(reflog, i);
		msg = git_reflog_entry_message(entry);
		if (!msg)
			continue;

		if (git_regexp_search(&preg, msg, 2, regexmatches) < 0)
			continue;

		cur--;

		if (cur > 0)
			continue;

		if ((git_buf_put(&buf, msg+regexmatches[1].start, regexmatches[1].end - regexmatches[1].start)) < 0)
			goto cleanup;

		if ((error = git_reference_dwim(base_ref, repo, git_buf_cstr(&buf))) == 0)
			goto cleanup;

		if (error < 0 && error != GIT_ENOTFOUND)
			goto cleanup;

		error = maybe_abbrev(out, repo, git_buf_cstr(&buf));

		goto cleanup;
	}

	error = GIT_ENOTFOUND;

cleanup:
	git_reference_free(ref);
	git_buf_dispose(&buf);
	git_regexp_dispose(&preg);
	git_reflog_free(reflog);
	return error;
}