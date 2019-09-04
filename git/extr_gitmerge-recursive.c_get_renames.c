#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tree {int dummy; } ;
struct string_list_item {struct rename* util; } ;
struct string_list {int dummy; } ;
struct rename {struct rename* dst_entry; struct diff_filepair* pair; struct rename* src_entry; scalar_t__ add_turned_into_rename; scalar_t__ processed; } ;
struct merge_options {int dummy; } ;
struct hashmap_iter {int dummy; } ;
struct hashmap {int dummy; } ;
struct diff_queue_struct {int nr; struct diff_filepair** queue; } ;
struct diff_filepair {char status; TYPE_2__* one; TYPE_1__* two; } ;
struct collision_entry {int /*<<< orphan*/  source_files; int /*<<< orphan*/  target_file; } ;
struct TYPE_4__ {int /*<<< orphan*/  path; } ;
struct TYPE_3__ {int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  apply_directory_rename_modifications (struct merge_options*,struct diff_filepair*,char*,struct rename*,struct tree*,struct tree*,struct tree*,struct tree*,struct string_list*) ; 
 char* check_for_directory_rename (struct merge_options*,int /*<<< orphan*/ ,struct tree*,struct hashmap*,struct hashmap*,struct hashmap*,int*) ; 
 int /*<<< orphan*/  compute_collisions (struct hashmap*,struct hashmap*,struct diff_queue_struct*) ; 
 int /*<<< orphan*/  diff_free_filepair (struct diff_filepair*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashmap_free (struct hashmap*,int) ; 
 int /*<<< orphan*/  hashmap_iter_init (struct hashmap*,struct hashmap_iter*) ; 
 struct collision_entry* hashmap_iter_next (struct hashmap_iter*) ; 
 void* insert_stage_data (int /*<<< orphan*/ ,struct tree*,struct tree*,struct tree*,struct string_list*) ; 
 int /*<<< orphan*/  string_list_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct string_list_item* string_list_insert (struct string_list*,int /*<<< orphan*/ ) ; 
 struct string_list_item* string_list_lookup (struct string_list*,int /*<<< orphan*/ ) ; 
 struct string_list* xcalloc (int,int) ; 
 struct rename* xmalloc (int) ; 

__attribute__((used)) static struct string_list *get_renames(struct merge_options *o,
				       struct diff_queue_struct *pairs,
				       struct hashmap *dir_renames,
				       struct hashmap *dir_rename_exclusions,
				       struct tree *tree,
				       struct tree *o_tree,
				       struct tree *a_tree,
				       struct tree *b_tree,
				       struct string_list *entries,
				       int *clean_merge)
{
	int i;
	struct hashmap collisions;
	struct hashmap_iter iter;
	struct collision_entry *e;
	struct string_list *renames;

	compute_collisions(&collisions, dir_renames, pairs);
	renames = xcalloc(1, sizeof(struct string_list));

	for (i = 0; i < pairs->nr; ++i) {
		struct string_list_item *item;
		struct rename *re;
		struct diff_filepair *pair = pairs->queue[i];
		char *new_path; /* non-NULL only with directory renames */

		if (pair->status != 'A' && pair->status != 'R') {
			diff_free_filepair(pair);
			continue;
		}
		new_path = check_for_directory_rename(o, pair->two->path, tree,
						      dir_renames,
						      dir_rename_exclusions,
						      &collisions,
						      clean_merge);
		if (pair->status != 'R' && !new_path) {
			diff_free_filepair(pair);
			continue;
		}

		re = xmalloc(sizeof(*re));
		re->processed = 0;
		re->add_turned_into_rename = 0;
		re->pair = pair;
		item = string_list_lookup(entries, re->pair->one->path);
		if (!item)
			re->src_entry = insert_stage_data(re->pair->one->path,
					o_tree, a_tree, b_tree, entries);
		else
			re->src_entry = item->util;

		item = string_list_lookup(entries, re->pair->two->path);
		if (!item)
			re->dst_entry = insert_stage_data(re->pair->two->path,
					o_tree, a_tree, b_tree, entries);
		else
			re->dst_entry = item->util;
		item = string_list_insert(renames, pair->one->path);
		item->util = re;
		if (new_path)
			apply_directory_rename_modifications(o, pair, new_path,
							     re, tree, o_tree,
							     a_tree, b_tree,
							     entries);
	}

	hashmap_iter_init(&collisions, &iter);
	while ((e = hashmap_iter_next(&iter))) {
		free(e->target_file);
		string_list_clear(&e->source_files, 0);
	}
	hashmap_free(&collisions, 1);
	return renames;
}