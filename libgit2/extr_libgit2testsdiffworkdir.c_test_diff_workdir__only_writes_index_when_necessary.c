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
struct stat {scalar_t__ st_mtime; } ;
struct p_timeval {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object ;
typedef  int /*<<< orphan*/  git_index ;
struct TYPE_4__ {int flags; } ;
typedef  TYPE_1__ git_diff_options ;
typedef  int /*<<< orphan*/  git_diff ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int GIT_DIFF_INCLUDE_UNTRACKED ; 
 TYPE_1__ GIT_DIFF_OPTIONS_INIT ; 
 int GIT_DIFF_UPDATE_INDEX ; 
 int /*<<< orphan*/  GIT_OBJECT_COMMIT ; 
 int /*<<< orphan*/  GIT_RESET_HARD ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_sets (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_index_to_workdir (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_index_checksum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_path_direach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_peel (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_head (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_stat (char*,struct stat*) ; 
 int /*<<< orphan*/  p_utimes (char*,struct p_timeval*) ; 
 int /*<<< orphan*/  touch_file ; 

void test_diff_workdir__only_writes_index_when_necessary(void)
{
	git_index *index;
	git_diff_options opts = GIT_DIFF_OPTIONS_INIT;
	git_diff *diff = NULL;
	git_reference *head;
	git_object *head_object;
	git_oid initial, first, second;
	git_buf path = GIT_BUF_INIT;
	struct stat st;
	struct p_timeval times[2];

	opts.flags |= GIT_DIFF_INCLUDE_UNTRACKED | GIT_DIFF_UPDATE_INDEX;

	g_repo = cl_git_sandbox_init("status");

	cl_git_pass(git_repository_index(&index, g_repo));
	cl_git_pass(git_repository_head(&head, g_repo));
	cl_git_pass(git_reference_peel(&head_object, head, GIT_OBJECT_COMMIT));

	cl_git_pass(git_reset(g_repo, head_object, GIT_RESET_HARD, NULL));

	git_oid_cpy(&initial, git_index_checksum(index));

	/* update the index timestamp to avoid raciness */
	cl_must_pass(p_stat("status/.git/index", &st));

	times[0].tv_sec = st.st_mtime + 5;
	times[0].tv_usec = 0;
	times[1].tv_sec = st.st_mtime + 5;
	times[1].tv_usec = 0;

	cl_must_pass(p_utimes("status/.git/index", times));

	/* ensure diff doesn't touch the index */
	cl_git_pass(git_diff_index_to_workdir(&diff, g_repo, NULL, &opts));
	git_diff_free(diff);

	git_oid_cpy(&first, git_index_checksum(index));
	cl_assert(!git_oid_equal(&initial, &first));

	/* touch all the files so stat times are different */
	cl_git_pass(git_buf_sets(&path, "status"));
	cl_git_pass(git_path_direach(&path, 0, touch_file, NULL));

	cl_git_pass(git_diff_index_to_workdir(&diff, g_repo, NULL, &opts));
	git_diff_free(diff);

	/* ensure the second diff did update the index */
	git_oid_cpy(&second, git_index_checksum(index));
	cl_assert(!git_oid_equal(&first, &second));

	git_buf_dispose(&path);
	git_object_free(head_object);
	git_reference_free(head);
	git_index_free(index);
}