#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  staged; int /*<<< orphan*/  pool; } ;
typedef  TYPE_1__ git_merge_diff_list ;
typedef  int /*<<< orphan*/  git_index_entry ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_pool_malloc (int /*<<< orphan*/ *,int) ; 
 int git_vector_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int index_entry_dup_pool (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int merge_diff_list_insert_unmodified(
	git_merge_diff_list *diff_list,
	const git_index_entry *tree_items[3])
{
	int error = 0;
	git_index_entry *entry;

	entry = git_pool_malloc(&diff_list->pool, sizeof(git_index_entry));
	GIT_ERROR_CHECK_ALLOC(entry);

	if ((error = index_entry_dup_pool(entry, &diff_list->pool, tree_items[0])) >= 0)
		error = git_vector_insert(&diff_list->staged, entry);

	return error;
}