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
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object ;
typedef  int /*<<< orphan*/  git_index ;
struct TYPE_4__ {int checkout_strategy; } ;
typedef  TYPE_1__ git_checkout_options ;

/* Variables and functions */
 int GIT_CHECKOUT_DONT_WRITE_INDEX ; 
 int GIT_CHECKOUT_FORCE ; 
 TYPE_1__ GIT_CHECKOUT_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_OBJECT_ANY ; 
 int /*<<< orphan*/  GIT_RESET_HARD ; 
 int GIT_STATUS_INDEX_NEW ; 
 int GIT_STATUS_WT_NEW ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,unsigned int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_object ; 
 int /*<<< orphan*/  g_opts ; 
 int /*<<< orphan*/ * g_repo ; 
 int /*<<< orphan*/  git_checkout_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int git_path_isdir (char*) ; 
 unsigned int git_path_isfile (char*) ; 
 int /*<<< orphan*/  git_reference_name_to_id (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_open (int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/  git_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_revparse_single (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_status_file (unsigned int*,int /*<<< orphan*/ *,char*) ; 

void test_checkout_tree__can_update_but_not_write_index(void)
{
	git_oid oid;
	git_object *head;
	unsigned int status;
	git_checkout_options opts = GIT_CHECKOUT_OPTIONS_INIT;
	git_index *index;
	git_repository *other;

	opts.checkout_strategy |=
		GIT_CHECKOUT_FORCE | GIT_CHECKOUT_DONT_WRITE_INDEX;

	cl_git_pass(git_reference_name_to_id(&oid, g_repo, "HEAD"));
	cl_git_pass(git_object_lookup(&head, g_repo, &oid, GIT_OBJECT_ANY));

	cl_git_pass(git_reset(g_repo, head, GIT_RESET_HARD, &g_opts));

	cl_assert_equal_i(false, git_path_isdir("./testrepo/ab/"));

	cl_git_pass(git_revparse_single(&g_object, g_repo, "subtrees"));

	cl_git_pass(git_checkout_tree(g_repo, g_object, &opts));

	cl_assert_equal_i(true, git_path_isfile("./testrepo/ab/de/2.txt"));
	cl_git_pass(git_status_file(&status, g_repo, "ab/de/2.txt"));
	cl_assert_equal_i(GIT_STATUS_INDEX_NEW, status);

	cl_git_pass(git_repository_open(&other, "testrepo"));
	cl_git_pass(git_status_file(&status, other, "ab/de/2.txt"));
	cl_assert_equal_i(GIT_STATUS_WT_NEW, status);
	git_repository_free(other);

	cl_git_pass(git_repository_index(&index, g_repo));
	cl_git_pass(git_index_write(index));

	cl_git_pass(git_repository_open(&other, "testrepo"));
	cl_git_pass(git_status_file(&status, other, "ab/de/2.txt"));
	cl_assert_equal_i(GIT_STATUS_INDEX_NEW, status);
	git_repository_free(other);

	git_object_free(head);
	git_index_free(index);
}