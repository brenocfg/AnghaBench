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
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_3__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ git_index_entry ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_CONTENTS_CRLF ; 
 int /*<<< orphan*/  FILE_CONTENTS_LF ; 
 int /*<<< orphan*/  FILE_OID_CRLF ; 
 int /*<<< orphan*/  FILE_OID_LF ; 
 scalar_t__ GIT_EOL_CRLF ; 
 scalar_t__ GIT_EOL_NATIVE ; 
 int /*<<< orphan*/  cl_assert_equal_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_repo_set_bool (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  g_index ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_index_add_bypath (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* git_index_get_bypath (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void test_index_crlf__autocrlf_false_no_attrs(void)
{
	const git_index_entry *entry;
	git_oid oid;

	cl_repo_set_bool(g_repo, "core.autocrlf", false);

	cl_git_mkfile("./crlf/newfile.txt",
		(GIT_EOL_NATIVE == GIT_EOL_CRLF) ? FILE_CONTENTS_CRLF : FILE_CONTENTS_LF);

	cl_git_pass(git_index_add_bypath(g_index, "newfile.txt"));
	entry = git_index_get_bypath(g_index, "newfile.txt", 0);

	cl_git_pass(git_oid_fromstr(&oid,
		(GIT_EOL_NATIVE == GIT_EOL_CRLF) ? FILE_OID_CRLF : FILE_OID_LF));
	cl_assert_equal_oid(&oid, &entry->id);
}