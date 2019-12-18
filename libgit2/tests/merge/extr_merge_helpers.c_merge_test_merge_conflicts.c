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
struct merge_index_conflict_data {int dummy; } ;
struct TYPE_3__ {size_t length; int /*<<< orphan*/ ** contents; } ;
typedef  TYPE_1__ git_vector ;
typedef  int /*<<< orphan*/  git_merge_diff ;

/* Variables and functions */
 int /*<<< orphan*/  index_conflict_data_eq_merge_diff (struct merge_index_conflict_data const*,int /*<<< orphan*/ *) ; 

int merge_test_merge_conflicts(git_vector *conflicts, const struct merge_index_conflict_data expected[], size_t expected_len)
{
	git_merge_diff *actual;
	size_t i;

	if (conflicts->length != expected_len)
		return 0;

	for (i = 0; i < expected_len; i++) {
		actual = conflicts->contents[i];

		if (!index_conflict_data_eq_merge_diff(&expected[i], actual))
			return 0;
	}

	return 1;
}