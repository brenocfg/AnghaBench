#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct checkout_index_entry {int stage; int /*<<< orphan*/  path; int /*<<< orphan*/  oid_str; int /*<<< orphan*/  mode; } ;
struct TYPE_5__ {int /*<<< orphan*/  path; int /*<<< orphan*/  id; int /*<<< orphan*/  mode; } ;
typedef  TYPE_1__ git_index_entry ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_INDEX_ENTRY_STAGE_SET (TYPE_1__*,int) ; 
 int /*<<< orphan*/  TEST_REPO_PATH ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_index ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_joinpath (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_add (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  git_index_remove_bypath (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  p_unlink (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void create_index(struct checkout_index_entry *entries, size_t entries_len)
{
	git_buf path = GIT_BUF_INIT;
	size_t i;

	for (i = 0; i < entries_len; i++) {
		git_buf_joinpath(&path, TEST_REPO_PATH, entries[i].path);

		if (entries[i].stage == 3 && (i == 0 || strcmp(entries[i-1].path, entries[i].path) != 0 || entries[i-1].stage != 2))
			p_unlink(git_buf_cstr(&path));

		cl_git_pass(git_index_remove_bypath(g_index, entries[i].path));
	}

	for (i = 0; i < entries_len; i++) {
		git_index_entry entry;

		memset(&entry, 0x0, sizeof(git_index_entry));

		entry.mode = entries[i].mode;
		GIT_INDEX_ENTRY_STAGE_SET(&entry, entries[i].stage);
		git_oid_fromstr(&entry.id, entries[i].oid_str);
		entry.path = entries[i].path;

		cl_git_pass(git_index_add(g_index, &entry));
	}

	git_buf_dispose(&path);
}