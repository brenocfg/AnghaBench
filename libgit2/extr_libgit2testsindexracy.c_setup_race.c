#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct stat {scalar_t__ st_mtime_nsec; scalar_t__ st_mtime; } ;
typedef  void* int32_t ;
struct TYPE_8__ {void* nanoseconds; void* seconds; } ;
struct TYPE_9__ {TYPE_1__ mtime; } ;
typedef  TYPE_2__ git_index_entry ;
typedef  int /*<<< orphan*/  git_index ;
struct TYPE_10__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_3__ git_buf ;

/* Variables and functions */
 TYPE_3__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_assert (TYPE_2__*) ; 
 int /*<<< orphan*/  cl_git_mkfile (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_3__*) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_index_add_bypath (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ git_index_get_bypath (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index__weakptr (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_workdir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_stat (int /*<<< orphan*/ ,struct stat*) ; 

__attribute__((used)) static void setup_race(void)
{
	git_buf path = GIT_BUF_INIT;
	git_index *index;
	git_index_entry *entry;
	struct stat st;

	/* Make sure we do have a timestamp */
	cl_git_pass(git_repository_index__weakptr(&index, g_repo));
	cl_git_pass(git_index_write(index));

	cl_git_pass(git_buf_joinpath(&path, git_repository_workdir(g_repo), "A"));

	cl_git_mkfile(path.ptr, "A");
	cl_git_pass(git_index_add_bypath(index, "A"));

	cl_git_mkfile(path.ptr, "B");
	cl_git_pass(git_index_write(index));

	cl_git_mkfile(path.ptr, "");

	cl_git_pass(p_stat(path.ptr, &st));
	cl_assert(entry = (git_index_entry *)git_index_get_bypath(index, "A", 0));

	/* force a race */
	entry->mtime.seconds = (int32_t)st.st_mtime;
	entry->mtime.nanoseconds = (int32_t)st.st_mtime_nsec;

	git_buf_dispose(&path);
}