#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct string_list_item {struct rename* util; } ;
struct string_list {int nr; TYPE_5__* items; } ;
struct rename {int processed; char dir_rename_original_type; TYPE_6__* dst_entry; TYPE_4__* pair; TYPE_2__* src_entry; } ;
struct merge_options {int dummy; } ;
struct diff_filespec {char* path; scalar_t__ mode; int /*<<< orphan*/  oid; } ;
typedef  enum rename_type { ____Placeholder_rename_type } rename_type ;
struct TYPE_14__ {void* util; } ;
struct TYPE_13__ {int processed; TYPE_3__* stages; } ;
struct TYPE_12__ {char const* string; struct rename* util; } ;
struct TYPE_11__ {struct diff_filespec* two; struct diff_filespec* one; } ;
struct TYPE_10__ {scalar_t__ mode; int /*<<< orphan*/  oid; } ;
struct TYPE_9__ {int processed; TYPE_1__* stages; } ;
struct TYPE_8__ {scalar_t__ mode; int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 int RENAME_ADD ; 
 int RENAME_DELETE ; 
 int RENAME_NORMAL ; 
 int RENAME_ONE_FILE_TO_ONE ; 
 int RENAME_ONE_FILE_TO_TWO ; 
 int RENAME_TWO_FILES_TO_ONE ; 
 int RENAME_VIA_DIR ; 
 struct string_list STRING_LIST_INIT_NODUP ; 
 int /*<<< orphan*/  SWAP (struct rename*,struct rename*) ; 
 int /*<<< orphan*/  null_oid ; 
 scalar_t__ oid_eq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_file (struct merge_options*,int,char const*,int) ; 
 int /*<<< orphan*/  setup_rename_conflict_info (int,struct merge_options*,struct rename*,struct rename*) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  string_list_clear (struct string_list*,int /*<<< orphan*/ ) ; 
 TYPE_7__* string_list_insert (struct string_list*,char*) ; 
 struct string_list_item* string_list_lookup (struct string_list*,char const*) ; 
 int /*<<< orphan*/  update_entry (TYPE_6__*,struct diff_filespec*,struct diff_filespec*,struct diff_filespec*) ; 
 scalar_t__ update_file_flags (struct merge_options*,struct diff_filespec*,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  was_tracked (struct merge_options*,char const*) ; 

__attribute__((used)) static int process_renames(struct merge_options *opt,
			   struct string_list *a_renames,
			   struct string_list *b_renames)
{
	int clean_merge = 1, i, j;
	struct string_list a_by_dst = STRING_LIST_INIT_NODUP;
	struct string_list b_by_dst = STRING_LIST_INIT_NODUP;
	const struct rename *sre;

	for (i = 0; i < a_renames->nr; i++) {
		sre = a_renames->items[i].util;
		string_list_insert(&a_by_dst, sre->pair->two->path)->util
			= (void *)sre;
	}
	for (i = 0; i < b_renames->nr; i++) {
		sre = b_renames->items[i].util;
		string_list_insert(&b_by_dst, sre->pair->two->path)->util
			= (void *)sre;
	}

	for (i = 0, j = 0; i < a_renames->nr || j < b_renames->nr;) {
		struct string_list *renames1, *renames2Dst;
		struct rename *ren1 = NULL, *ren2 = NULL;
		const char *ren1_src, *ren1_dst;
		struct string_list_item *lookup;

		if (i >= a_renames->nr) {
			ren2 = b_renames->items[j++].util;
		} else if (j >= b_renames->nr) {
			ren1 = a_renames->items[i++].util;
		} else {
			int compare = strcmp(a_renames->items[i].string,
					     b_renames->items[j].string);
			if (compare <= 0)
				ren1 = a_renames->items[i++].util;
			if (compare >= 0)
				ren2 = b_renames->items[j++].util;
		}

		/* TODO: refactor, so that 1/2 are not needed */
		if (ren1) {
			renames1 = a_renames;
			renames2Dst = &b_by_dst;
		} else {
			renames1 = b_renames;
			renames2Dst = &a_by_dst;
			SWAP(ren2, ren1);
		}

		if (ren1->processed)
			continue;
		ren1->processed = 1;
		ren1->dst_entry->processed = 1;
		/* BUG: We should only mark src_entry as processed if we
		 * are not dealing with a rename + add-source case.
		 */
		ren1->src_entry->processed = 1;

		ren1_src = ren1->pair->one->path;
		ren1_dst = ren1->pair->two->path;

		if (ren2) {
			/* One file renamed on both sides */
			const char *ren2_src = ren2->pair->one->path;
			const char *ren2_dst = ren2->pair->two->path;
			enum rename_type rename_type;
			if (strcmp(ren1_src, ren2_src) != 0)
				BUG("ren1_src != ren2_src");
			ren2->dst_entry->processed = 1;
			ren2->processed = 1;
			if (strcmp(ren1_dst, ren2_dst) != 0) {
				rename_type = RENAME_ONE_FILE_TO_TWO;
				clean_merge = 0;
			} else {
				rename_type = RENAME_ONE_FILE_TO_ONE;
				/* BUG: We should only remove ren1_src in
				 * the base stage (think of rename +
				 * add-source cases).
				 */
				remove_file(opt, 1, ren1_src, 1);
				update_entry(ren1->dst_entry,
					     ren1->pair->one,
					     ren1->pair->two,
					     ren2->pair->two);
			}
			setup_rename_conflict_info(rename_type, opt, ren1, ren2);
		} else if ((lookup = string_list_lookup(renames2Dst, ren1_dst))) {
			/* Two different files renamed to the same thing */
			char *ren2_dst;
			ren2 = lookup->util;
			ren2_dst = ren2->pair->two->path;
			if (strcmp(ren1_dst, ren2_dst) != 0)
				BUG("ren1_dst != ren2_dst");

			clean_merge = 0;
			ren2->processed = 1;
			/*
			 * BUG: We should only mark src_entry as processed
			 * if we are not dealing with a rename + add-source
			 * case.
			 */
			ren2->src_entry->processed = 1;

			setup_rename_conflict_info(RENAME_TWO_FILES_TO_ONE,
						   opt, ren1, ren2);
		} else {
			/* Renamed in 1, maybe changed in 2 */
			/* we only use sha1 and mode of these */
			struct diff_filespec src_other, dst_other;
			int try_merge;

			/*
			 * unpack_trees loads entries from common-commit
			 * into stage 1, from head-commit into stage 2, and
			 * from merge-commit into stage 3.  We keep track
			 * of which side corresponds to the rename.
			 */
			int renamed_stage = a_renames == renames1 ? 2 : 3;
			int other_stage =   a_renames == renames1 ? 3 : 2;

			/* BUG: We should only remove ren1_src in the base
			 * stage and in other_stage (think of rename +
			 * add-source case).
			 */
			remove_file(opt, 1, ren1_src,
				    renamed_stage == 2 || !was_tracked(opt, ren1_src));

			oidcpy(&src_other.oid,
			       &ren1->src_entry->stages[other_stage].oid);
			src_other.mode = ren1->src_entry->stages[other_stage].mode;
			oidcpy(&dst_other.oid,
			       &ren1->dst_entry->stages[other_stage].oid);
			dst_other.mode = ren1->dst_entry->stages[other_stage].mode;
			try_merge = 0;

			if (oid_eq(&src_other.oid, &null_oid) &&
			    ren1->dir_rename_original_type == 'A') {
				setup_rename_conflict_info(RENAME_VIA_DIR,
							   opt, ren1, NULL);
			} else if (oid_eq(&src_other.oid, &null_oid)) {
				setup_rename_conflict_info(RENAME_DELETE,
							   opt, ren1, NULL);
			} else if ((dst_other.mode == ren1->pair->two->mode) &&
				   oid_eq(&dst_other.oid, &ren1->pair->two->oid)) {
				/*
				 * Added file on the other side identical to
				 * the file being renamed: clean merge.
				 * Also, there is no need to overwrite the
				 * file already in the working copy, so call
				 * update_file_flags() instead of
				 * update_file().
				 */
				if (update_file_flags(opt,
						      ren1->pair->two,
						      ren1_dst,
						      1, /* update_cache */
						      0  /* update_wd    */))
					clean_merge = -1;
			} else if (!oid_eq(&dst_other.oid, &null_oid)) {
				/*
				 * Probably not a clean merge, but it's
				 * premature to set clean_merge to 0 here,
				 * because if the rename merges cleanly and
				 * the merge exactly matches the newly added
				 * file, then the merge will be clean.
				 */
				setup_rename_conflict_info(RENAME_ADD,
							   opt, ren1, NULL);
			} else
				try_merge = 1;

			if (clean_merge < 0)
				goto cleanup_and_return;
			if (try_merge) {
				struct diff_filespec *o, *a, *b;
				src_other.path = (char *)ren1_src;

				o = ren1->pair->one;
				if (a_renames == renames1) {
					a = ren1->pair->two;
					b = &src_other;
				} else {
					b = ren1->pair->two;
					a = &src_other;
				}
				update_entry(ren1->dst_entry, o, a, b);
				setup_rename_conflict_info(RENAME_NORMAL,
							   opt, ren1, NULL);
			}
		}
	}
cleanup_and_return:
	string_list_clear(&a_by_dst, 0);
	string_list_clear(&b_by_dst, 0);

	return clean_merge;
}