#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct string_list_item {char* string; struct stage_data* util; } ;
struct string_list {int nr; struct string_list_item* items; int /*<<< orphan*/  cmp; } ;
struct stage_data {TYPE_2__* stages; } ;
struct merge_options {TYPE_1__* priv; } ;
struct TYPE_6__ {struct stage_data* util; } ;
struct TYPE_5__ {int /*<<< orphan*/  mode; } ;
struct TYPE_4__ {struct string_list df_conflict_file_set; scalar_t__ call_depth; } ;

/* Variables and functions */
 struct string_list STRING_LIST_INIT_NODUP ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (char const*,char const*,int) ; 
 TYPE_3__* string_list_append (struct string_list*,char*) ; 
 int /*<<< orphan*/  string_list_clear (struct string_list*,int) ; 
 int /*<<< orphan*/  string_list_df_name_compare ; 
 int /*<<< orphan*/  string_list_insert (struct string_list*,char const*) ; 
 int /*<<< orphan*/  string_list_sort (struct string_list*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void record_df_conflict_files(struct merge_options *opt,
				     struct string_list *entries)
{
	/* If there is a D/F conflict and the file for such a conflict
	 * currently exists in the working tree, we want to allow it to be
	 * removed to make room for the corresponding directory if needed.
	 * The files underneath the directories of such D/F conflicts will
	 * be processed before the corresponding file involved in the D/F
	 * conflict.  If the D/F directory ends up being removed by the
	 * merge, then we won't have to touch the D/F file.  If the D/F
	 * directory needs to be written to the working copy, then the D/F
	 * file will simply be removed (in make_room_for_path()) to make
	 * room for the necessary paths.  Note that if both the directory
	 * and the file need to be present, then the D/F file will be
	 * reinstated with a new unique name at the time it is processed.
	 */
	struct string_list df_sorted_entries = STRING_LIST_INIT_NODUP;
	const char *last_file = NULL;
	int last_len = 0;
	int i;

	/*
	 * If we're merging merge-bases, we don't want to bother with
	 * any working directory changes.
	 */
	if (opt->priv->call_depth)
		return;

	/* Ensure D/F conflicts are adjacent in the entries list. */
	for (i = 0; i < entries->nr; i++) {
		struct string_list_item *next = &entries->items[i];
		string_list_append(&df_sorted_entries, next->string)->util =
				   next->util;
	}
	df_sorted_entries.cmp = string_list_df_name_compare;
	string_list_sort(&df_sorted_entries);

	string_list_clear(&opt->priv->df_conflict_file_set, 1);
	for (i = 0; i < df_sorted_entries.nr; i++) {
		const char *path = df_sorted_entries.items[i].string;
		int len = strlen(path);
		struct stage_data *e = df_sorted_entries.items[i].util;

		/*
		 * Check if last_file & path correspond to a D/F conflict;
		 * i.e. whether path is last_file+'/'+<something>.
		 * If so, record that it's okay to remove last_file to make
		 * room for path and friends if needed.
		 */
		if (last_file &&
		    len > last_len &&
		    memcmp(path, last_file, last_len) == 0 &&
		    path[last_len] == '/') {
			string_list_insert(&opt->priv->df_conflict_file_set, last_file);
		}

		/*
		 * Determine whether path could exist as a file in the
		 * working directory as a possible D/F conflict.  This
		 * will only occur when it exists in stage 2 as a
		 * file.
		 */
		if (S_ISREG(e->stages[2].mode) || S_ISLNK(e->stages[2].mode)) {
			last_file = path;
			last_len = len;
		} else {
			last_file = NULL;
		}
	}
	string_list_clear(&df_sorted_entries, 0);
}