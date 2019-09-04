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
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_index ;
struct TYPE_5__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_mkfile (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_1__*,char*,char const*) ; 
 int /*<<< orphan*/  git_index_add_bypath (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ git_index_entrycount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_unlink (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void add_invalid_filename(git_repository *repo, const char *fn)
{
	git_index *index;
	git_buf path = GIT_BUF_INIT;

	cl_git_pass(git_repository_index(&index, repo));
	cl_assert(git_index_entrycount(index) == 0);

	git_buf_joinpath(&path, "./invalid", fn);

	cl_git_mkfile(path.ptr, NULL);
	cl_git_fail(git_index_add_bypath(index, fn));
	cl_must_pass(p_unlink(path.ptr));

	cl_assert(git_index_entrycount(index) == 0);

	git_buf_dispose(&path);
	git_index_free(index);
}