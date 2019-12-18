#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int expected_entry_count; char const** expected_paths; unsigned int const* expected_statuses; int /*<<< orphan*/  entry_count; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ status_entry_counts ;
struct TYPE_11__ {int flags; int /*<<< orphan*/  show; } ;
typedef  TYPE_2__ git_status_options ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_object ;
struct TYPE_12__ {int /*<<< orphan*/  mode; } ;
typedef  TYPE_3__ git_index_entry ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_OBJECT_COMMIT ; 
 int /*<<< orphan*/  GIT_RESET_HARD ; 
 TYPE_2__ GIT_STATUS_OPTIONS_INIT ; 
 int GIT_STATUS_OPT_DEFAULTS ; 
 int GIT_STATUS_OPT_UPDATE_INDEX ; 
 int /*<<< orphan*/  GIT_STATUS_SHOW_INDEX_AND_WORKDIR ; 
 unsigned int const GIT_STATUS_WT_NEW ; 
 TYPE_3__ const* S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cb_status__normal ; 
 int /*<<< orphan*/  cl_assert (TYPE_3__ const*) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_rewritefile (char*,char*) ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 TYPE_3__* git_index_get_bypath (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_read (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_peel (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_head (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_status_foreach_ext (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__*) ; 

void test_status_worktree__update_index_with_symlink_doesnt_change_mode(void)
{
	git_repository *repo = cl_git_sandbox_init("testrepo");
	git_reference *head;
	git_object *head_object;
	git_index *index;
	const git_index_entry *idx_entry;
	git_status_options opts = GIT_STATUS_OPTIONS_INIT;
	status_entry_counts counts = {0};
	const char *expected_paths[] = { "README" };
	const unsigned int expected_statuses[] = {GIT_STATUS_WT_NEW};

	opts.show = GIT_STATUS_SHOW_INDEX_AND_WORKDIR;
	opts.flags = GIT_STATUS_OPT_DEFAULTS | GIT_STATUS_OPT_UPDATE_INDEX;

	cl_git_pass(git_repository_head(&head, repo));
	cl_git_pass(git_reference_peel(&head_object, head, GIT_OBJECT_COMMIT));

	cl_git_pass(git_reset(repo, head_object, GIT_RESET_HARD, NULL));

	cl_git_rewritefile("testrepo/README", "This was rewritten.");

	/* this status rewrites the index because we have changed the
	 * contents of a tracked file
	 */
	counts.expected_entry_count = 1;
	counts.expected_paths = expected_paths;
	counts.expected_statuses = expected_statuses;

	cl_git_pass(
		git_status_foreach_ext(repo, &opts, cb_status__normal, &counts));
	cl_assert_equal_i(1, counts.entry_count);

	/* now ensure that the status's rewrite of the index did not screw
	 * up the mode of the symlink `link_to_new.txt`, particularly
	 * on platforms that don't support symlinks
	 */
	cl_git_pass(git_repository_index(&index, repo));
	cl_git_pass(git_index_read(index, true));

	cl_assert(idx_entry = git_index_get_bypath(index, "link_to_new.txt", 0));
	cl_assert(S_ISLNK(idx_entry->mode));

	git_index_free(index);
	git_object_free(head_object);
	git_reference_free(head);
}