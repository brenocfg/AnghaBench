#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct merge_index_entry {int /*<<< orphan*/  oid_str; int /*<<< orphan*/  path; } ;
struct TYPE_4__ {int /*<<< orphan*/  workdir; } ;
typedef  TYPE_1__ git_repository ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  dircount ; 
 int /*<<< orphan*/  git_blob_create_from_workdir (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_puts (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ git_oid_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_path_direach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*) ; 

int merge_test_workdir(git_repository *repo, const struct merge_index_entry expected[], size_t expected_len)
{
	size_t actual_len = 0, i;
	git_oid actual_oid, expected_oid;
	git_buf wd = GIT_BUF_INIT;

	git_buf_puts(&wd, repo->workdir);
	git_path_direach(&wd, 0, dircount, &actual_len);

	if (actual_len != expected_len)
		return 0;

	for (i = 0; i < expected_len; i++) {
		git_blob_create_from_workdir(&actual_oid, repo, expected[i].path);
		git_oid_fromstr(&expected_oid, expected[i].oid_str);

		if (git_oid_cmp(&actual_oid, &expected_oid) != 0)
			return 0;
	}

	git_buf_dispose(&wd);

	return 1;
}