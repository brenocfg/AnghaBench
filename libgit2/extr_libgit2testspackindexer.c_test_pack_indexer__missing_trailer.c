#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ git_indexer_progress ;
typedef  int /*<<< orphan*/  git_indexer ;
struct TYPE_6__ {int /*<<< orphan*/  klass; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_INDEXER ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 TYPE_4__* git_error_last () ; 
 int /*<<< orphan*/  git_indexer_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  git_indexer_commit (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_indexer_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_indexer_new (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  missing_trailer_pack ; 
 int /*<<< orphan*/  missing_trailer_pack_len ; 

void test_pack_indexer__missing_trailer(void)
{
	git_indexer *idx = 0;
	git_indexer_progress stats = { 0 };

	cl_git_pass(git_indexer_new(&idx, ".", 0, NULL, NULL));
	cl_git_pass(git_indexer_append(
		idx, missing_trailer_pack, missing_trailer_pack_len, &stats));
	cl_git_fail(git_indexer_commit(idx, &stats));

	cl_assert(git_error_last() != NULL);
	cl_assert_equal_i(git_error_last()->klass, GIT_ERROR_INDEXER);

	git_indexer_free(idx);
}