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
struct TYPE_3__ {int /*<<< orphan*/  mode; int /*<<< orphan*/  oid; } ;
struct tree_desc {TYPE_1__ entry; scalar_t__ size; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 int base_name_entries_compare (TYPE_1__*,TYPE_1__*) ; 
 void* fill_tree_desc_strict (struct tree_desc*,struct object_id const*) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  oideq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ score_differs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ score_matches (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ score_missing (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_tree_entry (struct tree_desc*) ; 

__attribute__((used)) static int score_trees(const struct object_id *hash1, const struct object_id *hash2)
{
	struct tree_desc one;
	struct tree_desc two;
	void *one_buf = fill_tree_desc_strict(&one, hash1);
	void *two_buf = fill_tree_desc_strict(&two, hash2);
	int score = 0;

	for (;;) {
		int cmp;

		if (one.size && two.size)
			cmp = base_name_entries_compare(&one.entry, &two.entry);
		else if (one.size)
			/* two lacks this entry */
			cmp = -1;
		else if (two.size)
			/* two has more entries */
			cmp = 1;
		else
			break;

		if (cmp < 0) {
			/* path1 does not appear in two */
			score += score_missing(one.entry.mode);
			update_tree_entry(&one);
		} else if (cmp > 0) {
			/* path2 does not appear in one */
			score += score_missing(two.entry.mode);
			update_tree_entry(&two);
		} else {
			/* path appears in both */
			if (!oideq(&one.entry.oid, &two.entry.oid)) {
				/* they are different */
				score += score_differs(one.entry.mode,
						       two.entry.mode);
			} else {
				/* same subtree or blob */
				score += score_matches(one.entry.mode,
						       two.entry.mode);
			}
			update_tree_entry(&one);
			update_tree_entry(&two);
		}
	}
	free(one_buf);
	free(two_buf);
	return score;
}