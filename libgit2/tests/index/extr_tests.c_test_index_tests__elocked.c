#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_7__ {int /*<<< orphan*/  index_file_path; } ;
typedef  TYPE_1__ git_index ;
typedef  int /*<<< orphan*/  git_filebuf ;
struct TYPE_8__ {int /*<<< orphan*/  klass; } ;
typedef  TYPE_2__ git_error ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ELOCKED ; 
 int GIT_ERROR_INDEX ; 
 int /*<<< orphan*/  GIT_FILEBUF_INIT ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_set_cleanup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cleanup_myrepo ; 
 TYPE_2__* git_error_last () ; 
 int /*<<< orphan*/  git_filebuf_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_filebuf_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  git_index_free (TYPE_1__*) ; 
 int git_index_write (TYPE_1__*) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (TYPE_1__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_init (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ) ; 

void test_index_tests__elocked(void)
{
	git_repository *repo;
	git_index *index;
	git_filebuf file = GIT_FILEBUF_INIT;
	const git_error *err;
	int error;

	cl_set_cleanup(&cleanup_myrepo, NULL);

	cl_git_pass(git_repository_init(&repo, "./myrepo", 0));
	cl_git_pass(git_repository_index(&index, repo));

	/* Lock the index file so we fail to lock it */
	cl_git_pass(git_filebuf_open(&file, index->index_file_path, 0, 0666));
	error = git_index_write(index);
	cl_assert_equal_i(GIT_ELOCKED, error);

	err = git_error_last();
	cl_assert_equal_i(err->klass, GIT_ERROR_INDEX);

	git_filebuf_cleanup(&file);
	git_index_free(index);
	git_repository_free(repo);
}