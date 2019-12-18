#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  git_indexer ;

/* Variables and functions */
 int /*<<< orphan*/  _packbuilder ; 
 int /*<<< orphan*/  _stats ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  foreach_cb ; 
 int /*<<< orphan*/  git_indexer_commit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_indexer_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_indexer_new (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_packbuilder_foreach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seed_packbuilder () ; 

void test_pack_packbuilder__foreach(void)
{
	git_indexer *idx;

	seed_packbuilder();
	cl_git_pass(git_indexer_new(&idx, ".", 0, NULL, NULL));
	cl_git_pass(git_packbuilder_foreach(_packbuilder, foreach_cb, idx));
	cl_git_pass(git_indexer_commit(idx, &_stats));
	git_indexer_free(idx);
}