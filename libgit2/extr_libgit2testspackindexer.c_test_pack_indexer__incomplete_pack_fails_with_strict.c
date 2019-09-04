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
struct TYPE_7__ {int /*<<< orphan*/  indexed_objects; int /*<<< orphan*/  received_objects; int /*<<< orphan*/  total_objects; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ git_indexer_progress ;
struct TYPE_8__ {int verify; } ;
typedef  TYPE_2__ git_indexer_options ;
typedef  int /*<<< orphan*/  git_indexer ;

/* Variables and functions */
 TYPE_2__ GIT_INDEXER_OPTIONS_INIT ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_indexer_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  git_indexer_commit (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_indexer_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_indexer_new (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  incomplete_pack ; 
 int /*<<< orphan*/  incomplete_pack_len ; 

void test_pack_indexer__incomplete_pack_fails_with_strict(void)
{
	git_indexer_options opts = GIT_INDEXER_OPTIONS_INIT;
	git_indexer *idx = 0;
	git_indexer_progress stats = { 0 };

	opts.verify = 1;

	cl_git_pass(git_indexer_new(&idx, ".", 0, NULL, &opts));
	cl_git_pass(git_indexer_append(
		idx, incomplete_pack, incomplete_pack_len, &stats));
	cl_git_fail(git_indexer_commit(idx, &stats));

	cl_assert_equal_i(stats.total_objects, 2);
	cl_assert_equal_i(stats.received_objects, 2);
	cl_assert_equal_i(stats.indexed_objects, 2);

	git_indexer_free(idx);
}