#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ status; int /*<<< orphan*/  entry; } ;
struct TYPE_6__ {scalar_t__ status; int /*<<< orphan*/  entry; } ;
struct TYPE_8__ {int /*<<< orphan*/  entry; } ;
struct merge_index_conflict_data {TYPE_2__ theirs; TYPE_1__ ours; TYPE_3__ ancestor; } ;
struct TYPE_9__ {scalar_t__ our_status; scalar_t__ their_status; int /*<<< orphan*/  their_entry; int /*<<< orphan*/  our_entry; int /*<<< orphan*/  ancestor_entry; } ;
typedef  TYPE_4__ git_merge_diff ;

/* Variables and functions */
 int /*<<< orphan*/  index_entry_eq_merge_index_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int index_conflict_data_eq_merge_diff(const struct merge_index_conflict_data *expected, git_merge_diff *actual)
{
	if (!index_entry_eq_merge_index_entry(&expected->ancestor.entry, &actual->ancestor_entry) ||
		!index_entry_eq_merge_index_entry(&expected->ours.entry, &actual->our_entry) ||
		!index_entry_eq_merge_index_entry(&expected->theirs.entry, &actual->their_entry))
		return 0;

	if (expected->ours.status != actual->our_status ||
		expected->theirs.status != actual->their_status)
		return 0;

	return 1;
}