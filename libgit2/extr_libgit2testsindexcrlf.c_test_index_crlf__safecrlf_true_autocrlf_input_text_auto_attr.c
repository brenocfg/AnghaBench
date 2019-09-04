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
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ git_index_entry ;

/* Variables and functions */
 char* FILE_CONTENTS_CRLF ; 
 char* FILE_CONTENTS_LF ; 
 int /*<<< orphan*/  FILE_OID_LF ; 
 int /*<<< orphan*/  cl_assert (TYPE_1__ const*) ; 
 int /*<<< orphan*/  cl_assert_equal_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_repo_set_bool (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  cl_repo_set_string (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  g_index ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_index_add_bypath (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* git_index_get_bypath (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void test_index_crlf__safecrlf_true_autocrlf_input_text_auto_attr(void)
{
	const git_index_entry *entry;
	git_oid oid;

	cl_git_mkfile("./crlf/.gitattributes", "* text=auto\n");

	cl_repo_set_string(g_repo, "core.autocrlf", "input");
	cl_repo_set_bool(g_repo, "core.safecrlf", true);

	cl_git_mkfile("./crlf/newfile.txt", FILE_CONTENTS_LF);

	cl_git_pass(git_index_add_bypath(g_index, "newfile.txt"));
	entry = git_index_get_bypath(g_index, "newfile.txt", 0);
	cl_assert(entry);

	cl_git_pass(git_oid_fromstr(&oid, FILE_OID_LF));
	cl_assert_equal_oid(&oid, &entry->id);

	cl_git_mkfile("./crlf/newfile2.txt", FILE_CONTENTS_CRLF);
	cl_git_fail(git_index_add_bypath(g_index, "newfile2.txt"));
}