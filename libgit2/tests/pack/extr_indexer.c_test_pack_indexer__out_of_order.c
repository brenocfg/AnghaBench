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
struct TYPE_4__ {int /*<<< orphan*/  indexed_objects; int /*<<< orphan*/  received_objects; int /*<<< orphan*/  total_objects; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ git_indexer_progress ;
typedef  int /*<<< orphan*/  git_indexer ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_indexer_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  git_indexer_commit (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_indexer_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_indexer_new (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  out_of_order_pack ; 
 int /*<<< orphan*/  out_of_order_pack_len ; 

void test_pack_indexer__out_of_order(void)
{
	git_indexer *idx = 0;
	git_indexer_progress stats = { 0 };

	cl_git_pass(git_indexer_new(&idx, ".", 0, NULL, NULL));
	cl_git_pass(git_indexer_append(
		idx, out_of_order_pack, out_of_order_pack_len, &stats));
	cl_git_pass(git_indexer_commit(idx, &stats));

	cl_assert_equal_i(stats.total_objects, 3);
	cl_assert_equal_i(stats.received_objects, 3);
	cl_assert_equal_i(stats.indexed_objects, 3);

	git_indexer_free(idx);
}