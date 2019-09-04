#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tree {int dummy; } ;
struct string_list {int dummy; } ;
struct merge_options {int /*<<< orphan*/  branch2; int /*<<< orphan*/  branch1; } ;
struct hashmap_iter {int dummy; } ;
struct hashmap {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  buf; } ;
struct dir_rename_entry {TYPE_2__ new_dir; int /*<<< orphan*/  dir; int /*<<< orphan*/  non_unique_new_dir; } ;
struct TYPE_5__ {struct dir_rename_entry* util; } ;

/* Variables and functions */
 struct string_list STRING_LIST_INIT_NODUP ; 
 int /*<<< orphan*/  _ (char*) ; 
 struct dir_rename_entry* dir_rename_find_entry (struct hashmap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashmap_iter_init (struct hashmap*,struct hashmap_iter*) ; 
 struct dir_rename_entry* hashmap_iter_next (struct hashmap_iter*) ; 
 int /*<<< orphan*/  output (struct merge_options*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_hashmap_entries (struct hashmap*,struct string_list*) ; 
 int /*<<< orphan*/  strbuf_cmp (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  strbuf_release (TYPE_2__*) ; 
 TYPE_1__* string_list_append (struct string_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ tree_has_path (struct tree*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_directory_level_conflicts(struct merge_options *o,
					     struct hashmap *dir_re_head,
					     struct tree *head,
					     struct hashmap *dir_re_merge,
					     struct tree *merge)
{
	struct hashmap_iter iter;
	struct dir_rename_entry *head_ent;
	struct dir_rename_entry *merge_ent;

	struct string_list remove_from_head = STRING_LIST_INIT_NODUP;
	struct string_list remove_from_merge = STRING_LIST_INIT_NODUP;

	hashmap_iter_init(dir_re_head, &iter);
	while ((head_ent = hashmap_iter_next(&iter))) {
		merge_ent = dir_rename_find_entry(dir_re_merge, head_ent->dir);
		if (merge_ent &&
		    !head_ent->non_unique_new_dir &&
		    !merge_ent->non_unique_new_dir &&
		    !strbuf_cmp(&head_ent->new_dir, &merge_ent->new_dir)) {
			/* 1. Renamed identically; remove it from both sides */
			string_list_append(&remove_from_head,
					   head_ent->dir)->util = head_ent;
			strbuf_release(&head_ent->new_dir);
			string_list_append(&remove_from_merge,
					   merge_ent->dir)->util = merge_ent;
			strbuf_release(&merge_ent->new_dir);
		} else if (tree_has_path(head, head_ent->dir)) {
			/* 2. This wasn't a directory rename after all */
			string_list_append(&remove_from_head,
					   head_ent->dir)->util = head_ent;
			strbuf_release(&head_ent->new_dir);
		}
	}

	remove_hashmap_entries(dir_re_head, &remove_from_head);
	remove_hashmap_entries(dir_re_merge, &remove_from_merge);

	hashmap_iter_init(dir_re_merge, &iter);
	while ((merge_ent = hashmap_iter_next(&iter))) {
		head_ent = dir_rename_find_entry(dir_re_head, merge_ent->dir);
		if (tree_has_path(merge, merge_ent->dir)) {
			/* 2. This wasn't a directory rename after all */
			string_list_append(&remove_from_merge,
					   merge_ent->dir)->util = merge_ent;
		} else if (head_ent &&
			   !head_ent->non_unique_new_dir &&
			   !merge_ent->non_unique_new_dir) {
			/* 3. rename/rename(1to2) */
			/*
			 * We can assume it's not rename/rename(1to1) because
			 * that was case (1), already checked above.  So we
			 * know that head_ent->new_dir and merge_ent->new_dir
			 * are different strings.
			 */
			output(o, 1, _("CONFLICT (rename/rename): "
				       "Rename directory %s->%s in %s. "
				       "Rename directory %s->%s in %s"),
			       head_ent->dir, head_ent->new_dir.buf, o->branch1,
			       head_ent->dir, merge_ent->new_dir.buf, o->branch2);
			string_list_append(&remove_from_head,
					   head_ent->dir)->util = head_ent;
			strbuf_release(&head_ent->new_dir);
			string_list_append(&remove_from_merge,
					   merge_ent->dir)->util = merge_ent;
			strbuf_release(&merge_ent->new_dir);
		}
	}

	remove_hashmap_entries(dir_re_head, &remove_from_head);
	remove_hashmap_entries(dir_re_merge, &remove_from_merge);
}