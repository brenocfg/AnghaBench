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
struct merge_diff_find_data {int /*<<< orphan*/  diff_list; int /*<<< orphan*/  df_data; } ;
typedef  int /*<<< orphan*/  git_index_entry ;

/* Variables and functions */
 scalar_t__ index_entry_cmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int merge_diff_list_insert_conflict (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const**) ; 
 int merge_diff_list_insert_unmodified (int /*<<< orphan*/ ,int /*<<< orphan*/  const**) ; 

__attribute__((used)) static int queue_difference(const git_index_entry **entries, void *data)
{
	struct merge_diff_find_data *find_data = data;
	bool item_modified = false;
	size_t i;

	if (!entries[0] || !entries[1] || !entries[2]) {
		item_modified = true;
	} else {
		for (i = 1; i < 3; i++) {
			if (index_entry_cmp(entries[0], entries[i]) != 0) {
				item_modified = true;
				break;
			}
		}
	}

	return item_modified ?
		merge_diff_list_insert_conflict(
			find_data->diff_list, &find_data->df_data, entries) :
		merge_diff_list_insert_unmodified(find_data->diff_list, entries);
}