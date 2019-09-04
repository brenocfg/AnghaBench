#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct string_list_item {int* util; } ;
struct hashmap_iter {int dummy; } ;
struct hashmap {int dummy; } ;
struct TYPE_11__ {int nr; int strdup_strings; TYPE_3__* items; } ;
struct TYPE_12__ {scalar_t__ len; } ;
struct dir_rename_entry {int non_unique_new_dir; TYPE_4__ possible_new_dirs; TYPE_7__ new_dir; } ;
struct diff_queue_struct {int nr; struct diff_filepair** queue; } ;
struct diff_filepair {char status; TYPE_2__* two; TYPE_1__* one; } ;
struct TYPE_10__ {int* util; char* string; } ;
struct TYPE_9__ {int /*<<< orphan*/  path; } ;
struct TYPE_8__ {int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dir_rename_entry_init (struct dir_rename_entry*,char*) ; 
 struct dir_rename_entry* dir_rename_find_entry (struct hashmap*,char*) ; 
 int /*<<< orphan*/  dir_rename_init (struct hashmap*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  get_renamed_dir_portion (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**,char**) ; 
 int /*<<< orphan*/  hashmap_iter_init (struct hashmap*,struct hashmap_iter*) ; 
 struct dir_rename_entry* hashmap_iter_next (struct hashmap_iter*) ; 
 int /*<<< orphan*/  hashmap_put (struct hashmap*,struct dir_rename_entry*) ; 
 int /*<<< orphan*/  strbuf_addstr (TYPE_7__*,char*) ; 
 int /*<<< orphan*/  string_list_clear (TYPE_4__*,int) ; 
 struct string_list_item* string_list_insert (TYPE_4__*,char*) ; 
 struct string_list_item* string_list_lookup (TYPE_4__*,char*) ; 
 int* xcalloc (int,int) ; 
 void* xmalloc (int) ; 

__attribute__((used)) static struct hashmap *get_directory_renames(struct diff_queue_struct *pairs)
{
	struct hashmap *dir_renames;
	struct hashmap_iter iter;
	struct dir_rename_entry *entry;
	int i;

	/*
	 * Typically, we think of a directory rename as all files from a
	 * certain directory being moved to a target directory.  However,
	 * what if someone first moved two files from the original
	 * directory in one commit, and then renamed the directory
	 * somewhere else in a later commit?  At merge time, we just know
	 * that files from the original directory went to two different
	 * places, and that the bulk of them ended up in the same place.
	 * We want each directory rename to represent where the bulk of the
	 * files from that directory end up; this function exists to find
	 * where the bulk of the files went.
	 *
	 * The first loop below simply iterates through the list of file
	 * renames, finding out how often each directory rename pair
	 * possibility occurs.
	 */
	dir_renames = xmalloc(sizeof(*dir_renames));
	dir_rename_init(dir_renames);
	for (i = 0; i < pairs->nr; ++i) {
		struct string_list_item *item;
		int *count;
		struct diff_filepair *pair = pairs->queue[i];
		char *old_dir, *new_dir;

		/* File not part of directory rename if it wasn't renamed */
		if (pair->status != 'R')
			continue;

		get_renamed_dir_portion(pair->one->path, pair->two->path,
					&old_dir,        &new_dir);
		if (!old_dir)
			/* Directory didn't change at all; ignore this one. */
			continue;

		entry = dir_rename_find_entry(dir_renames, old_dir);
		if (!entry) {
			entry = xmalloc(sizeof(*entry));
			dir_rename_entry_init(entry, old_dir);
			hashmap_put(dir_renames, entry);
		} else {
			free(old_dir);
		}
		item = string_list_lookup(&entry->possible_new_dirs, new_dir);
		if (!item) {
			item = string_list_insert(&entry->possible_new_dirs,
						  new_dir);
			item->util = xcalloc(1, sizeof(int));
		} else {
			free(new_dir);
		}
		count = item->util;
		*count += 1;
	}

	/*
	 * For each directory with files moved out of it, we find out which
	 * target directory received the most files so we can declare it to
	 * be the "winning" target location for the directory rename.  This
	 * winner gets recorded in new_dir.  If there is no winner
	 * (multiple target directories received the same number of files),
	 * we set non_unique_new_dir.  Once we've determined the winner (or
	 * that there is no winner), we no longer need possible_new_dirs.
	 */
	hashmap_iter_init(dir_renames, &iter);
	while ((entry = hashmap_iter_next(&iter))) {
		int max = 0;
		int bad_max = 0;
		char *best = NULL;

		for (i = 0; i < entry->possible_new_dirs.nr; i++) {
			int *count = entry->possible_new_dirs.items[i].util;

			if (*count == max)
				bad_max = max;
			else if (*count > max) {
				max = *count;
				best = entry->possible_new_dirs.items[i].string;
			}
		}
		if (bad_max == max)
			entry->non_unique_new_dir = 1;
		else {
			assert(entry->new_dir.len == 0);
			strbuf_addstr(&entry->new_dir, best);
		}
		/*
		 * The relevant directory sub-portion of the original full
		 * filepaths were xstrndup'ed before inserting into
		 * possible_new_dirs, and instead of manually iterating the
		 * list and free'ing each, just lie and tell
		 * possible_new_dirs that it did the strdup'ing so that it
		 * will free them for us.
		 */
		entry->possible_new_dirs.strdup_strings = 1;
		string_list_clear(&entry->possible_new_dirs, 1);
	}

	return dir_renames;
}