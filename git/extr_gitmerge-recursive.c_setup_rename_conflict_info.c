#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct stage_data {TYPE_4__* stages; struct rename_conflict_info* rename_conflict_info; scalar_t__ processed; } ;
struct TYPE_7__ {int /*<<< orphan*/  mode; int /*<<< orphan*/  oid; int /*<<< orphan*/  path; } ;
struct TYPE_5__ {int /*<<< orphan*/  mode; int /*<<< orphan*/  oid; int /*<<< orphan*/  path; } ;
struct rename_conflict_info {int rename_type; char const* branch1; char const* branch2; TYPE_3__ ren2_other; TYPE_1__ ren1_other; struct diff_filepair* pair2; struct stage_data* dst_entry2; struct stage_data* dst_entry1; struct diff_filepair* pair1; } ;
struct merge_options {char const* branch1; } ;
struct diff_filepair {TYPE_2__* one; } ;
typedef  enum rename_type { ____Placeholder_rename_type } rename_type ;
struct TYPE_8__ {int /*<<< orphan*/  mode; int /*<<< orphan*/  oid; } ;
struct TYPE_6__ {int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int RENAME_ADD ; 
 int RENAME_TWO_FILES_TO_ONE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct rename_conflict_info* xcalloc (int,int) ; 

__attribute__((used)) static inline void setup_rename_conflict_info(enum rename_type rename_type,
					      struct diff_filepair *pair1,
					      struct diff_filepair *pair2,
					      const char *branch1,
					      const char *branch2,
					      struct stage_data *dst_entry1,
					      struct stage_data *dst_entry2,
					      struct merge_options *o,
					      struct stage_data *src_entry1,
					      struct stage_data *src_entry2)
{
	int ostage1 = 0, ostage2;
	struct rename_conflict_info *ci;

	/*
	 * When we have two renames involved, it's easiest to get the
	 * correct things into stage 2 and 3, and to make sure that the
	 * content merge puts HEAD before the other branch if we just
	 * ensure that branch1 == o->branch1.  So, simply flip arguments
	 * around if we don't have that.
	 */
	if (dst_entry2 && branch1 != o->branch1) {
		setup_rename_conflict_info(rename_type,
					   pair2,      pair1,
					   branch2,    branch1,
					   dst_entry2, dst_entry1,
					   o,
					   src_entry2, src_entry1);
		return;
	}

	ci = xcalloc(1, sizeof(struct rename_conflict_info));
	ci->rename_type = rename_type;
	ci->pair1 = pair1;
	ci->branch1 = branch1;
	ci->branch2 = branch2;

	ci->dst_entry1 = dst_entry1;
	dst_entry1->rename_conflict_info = ci;
	dst_entry1->processed = 0;

	assert(!pair2 == !dst_entry2);
	if (dst_entry2) {
		ci->dst_entry2 = dst_entry2;
		ci->pair2 = pair2;
		dst_entry2->rename_conflict_info = ci;
	}

	/*
	 * For each rename, there could have been
	 * modifications on the side of history where that
	 * file was not renamed.
	 */
	if (rename_type == RENAME_ADD ||
	    rename_type == RENAME_TWO_FILES_TO_ONE) {
		ostage1 = o->branch1 == branch1 ? 3 : 2;

		ci->ren1_other.path = pair1->one->path;
		oidcpy(&ci->ren1_other.oid, &src_entry1->stages[ostage1].oid);
		ci->ren1_other.mode = src_entry1->stages[ostage1].mode;
	}

	if (rename_type == RENAME_TWO_FILES_TO_ONE) {
		ostage2 = ostage1 ^ 1;

		ci->ren2_other.path = pair2->one->path;
		oidcpy(&ci->ren2_other.oid, &src_entry2->stages[ostage2].oid);
		ci->ren2_other.mode = src_entry2->stages[ostage2].mode;
	}
}