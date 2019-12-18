#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct p_timeval {int tv_usec; scalar_t__ tv_sec; } ;
struct TYPE_15__ {int tv_nsec; scalar_t__ tv_sec; } ;
struct TYPE_16__ {TYPE_1__ mtime; } ;
struct TYPE_17__ {TYPE_2__ stamp; } ;
typedef  TYPE_3__ git_index ;
typedef  int /*<<< orphan*/  git_diff ;
struct TYPE_18__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_4__ git_buf ;

/* Variables and functions */
 TYPE_4__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_mkfile (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_4__*) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_index_to_workdir (int /*<<< orphan*/ **,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_num_deltas (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_add_bypath (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  git_index_free (TYPE_3__*) ; 
 int /*<<< orphan*/  git_index_path (TYPE_3__*) ; 
 int /*<<< orphan*/  git_index_read (TYPE_3__*,int) ; 
 int /*<<< orphan*/  git_index_write (TYPE_3__*) ; 
 int /*<<< orphan*/  git_repository_index (TYPE_3__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_workdir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_utimes (int /*<<< orphan*/ ,struct p_timeval*) ; 

void test_index_racy__write_index_just_after_file(void)
{
	git_index *index;
	git_diff *diff;
	git_buf path = GIT_BUF_INIT;
	struct p_timeval times[2];

	/* Make sure we do have a timestamp */
	cl_git_pass(git_repository_index(&index, g_repo));
	cl_git_pass(git_index_write(index));

	cl_git_pass(git_buf_joinpath(&path, git_repository_workdir(g_repo), "A"));
	cl_git_mkfile(path.ptr, "A");
	/* Force the file's timestamp to be a second after we wrote the index */
	times[0].tv_sec = index->stamp.mtime.tv_sec + 1;
	times[0].tv_usec = index->stamp.mtime.tv_nsec / 1000;
	times[1].tv_sec = index->stamp.mtime.tv_sec + 1;
	times[1].tv_usec = index->stamp.mtime.tv_nsec / 1000;
	cl_git_pass(p_utimes(path.ptr, times));

	/*
	 * Put 'A' into the index, the size field will be filled,
	 * because the index' on-disk timestamp does not match the
	 * file's timestamp.
	 */
	cl_git_pass(git_index_add_bypath(index, "A"));
	cl_git_pass(git_index_write(index));

	cl_git_mkfile(path.ptr, "B");
	/*
	 * Pretend this index' modification happened a second after the
	 * file update, and rewrite the file in that same second.
	 */
	times[0].tv_sec = index->stamp.mtime.tv_sec + 2;
	times[0].tv_usec = index->stamp.mtime.tv_nsec / 1000;
	times[1].tv_sec = index->stamp.mtime.tv_sec + 2;
	times[0].tv_usec = index->stamp.mtime.tv_nsec / 1000;

	cl_git_pass(p_utimes(git_index_path(index), times));
	cl_git_pass(p_utimes(path.ptr, times));

	cl_git_pass(git_index_read(index, true));

	cl_git_pass(git_diff_index_to_workdir(&diff, g_repo, index, NULL));
	cl_assert_equal_i(1, git_diff_num_deltas(diff));

	git_buf_dispose(&path);
	git_diff_free(diff);
	git_index_free(index);
}