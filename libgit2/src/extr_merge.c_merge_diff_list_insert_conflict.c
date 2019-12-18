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
struct merge_diff_df_data {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  conflicts; } ;
typedef  TYPE_1__ git_merge_diff_list ;
typedef  int /*<<< orphan*/  git_merge_diff ;
typedef  int /*<<< orphan*/  git_index_entry ;

/* Variables and functions */
 scalar_t__ git_vector_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ merge_diff_detect_df_conflict (struct merge_diff_df_data*,int /*<<< orphan*/ *) ; 
 scalar_t__ merge_diff_detect_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * merge_diff_from_index_entries (TYPE_1__*,int /*<<< orphan*/  const**) ; 

__attribute__((used)) static int merge_diff_list_insert_conflict(
	git_merge_diff_list *diff_list,
	struct merge_diff_df_data *merge_df_data,
	const git_index_entry *tree_items[3])
{
	git_merge_diff *conflict;

	if ((conflict = merge_diff_from_index_entries(diff_list, tree_items)) == NULL ||
		merge_diff_detect_type(conflict) < 0 ||
		merge_diff_detect_df_conflict(merge_df_data, conflict) < 0 ||
		git_vector_insert(&diff_list->conflicts, conflict) < 0)
		return -1;

	return 0;
}