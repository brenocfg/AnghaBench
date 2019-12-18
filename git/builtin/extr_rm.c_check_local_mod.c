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
struct string_list {int /*<<< orphan*/  nr; } ;
struct stat {int /*<<< orphan*/  st_mode; } ;
struct object_id {int dummy; } ;
struct cache_entry {scalar_t__ ce_mode; int /*<<< orphan*/  oid; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int nr; TYPE_1__* entry; } ;
struct TYPE_3__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  Q_ (char*,char*,int /*<<< orphan*/ ) ; 
 struct string_list STRING_LIST_INIT_NODUP ; 
 int SUBMODULE_REMOVAL_DIE_ON_ERROR ; 
 int SUBMODULE_REMOVAL_IGNORE_IGNORED_UNTRACKED ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISGITLINK (scalar_t__) ; 
 int /*<<< orphan*/  _ (char*) ; 
 struct cache_entry** active_cache ; 
 scalar_t__ bad_to_remove_submodule (int /*<<< orphan*/ ,int) ; 
 int cache_name_pos (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ce_intent_to_add (struct cache_entry const*) ; 
 scalar_t__ ce_match_stat (struct cache_entry const*,struct stat*,int /*<<< orphan*/ ) ; 
 scalar_t__ create_ce_mode (unsigned short) ; 
 int /*<<< orphan*/  errno ; 
 int get_ours_cache_pos (char const*,int) ; 
 scalar_t__ get_tree_entry (int /*<<< orphan*/ ,struct object_id*,char const*,struct object_id*,unsigned short*) ; 
 scalar_t__ is_empty_dir (char const*) ; 
 int /*<<< orphan*/  is_missing_file_error (int /*<<< orphan*/ ) ; 
 int is_null_oid (struct object_id*) ; 
 TYPE_2__ list ; 
 scalar_t__ lstat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  oideq (int /*<<< orphan*/ *,struct object_id*) ; 
 int /*<<< orphan*/  print_error_files (struct string_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  string_list_append (struct string_list*,char const*) ; 
 int /*<<< orphan*/  string_list_clear (struct string_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  warning_errno (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_local_mod(struct object_id *head, int index_only)
{
	/*
	 * Items in list are already sorted in the cache order,
	 * so we could do this a lot more efficiently by using
	 * tree_desc based traversal if we wanted to, but I am
	 * lazy, and who cares if removal of files is a tad
	 * slower than the theoretical maximum speed?
	 */
	int i, no_head;
	int errs = 0;
	struct string_list files_staged = STRING_LIST_INIT_NODUP;
	struct string_list files_cached = STRING_LIST_INIT_NODUP;
	struct string_list files_local = STRING_LIST_INIT_NODUP;

	no_head = is_null_oid(head);
	for (i = 0; i < list.nr; i++) {
		struct stat st;
		int pos;
		const struct cache_entry *ce;
		const char *name = list.entry[i].name;
		struct object_id oid;
		unsigned short mode;
		int local_changes = 0;
		int staged_changes = 0;

		pos = cache_name_pos(name, strlen(name));
		if (pos < 0) {
			/*
			 * Skip unmerged entries except for populated submodules
			 * that could lose history when removed.
			 */
			pos = get_ours_cache_pos(name, pos);
			if (pos < 0)
				continue;

			if (!S_ISGITLINK(active_cache[pos]->ce_mode) ||
			    is_empty_dir(name))
				continue;
		}
		ce = active_cache[pos];

		if (lstat(ce->name, &st) < 0) {
			if (!is_missing_file_error(errno))
				warning_errno(_("failed to stat '%s'"), ce->name);
			/* It already vanished from the working tree */
			continue;
		}
		else if (S_ISDIR(st.st_mode)) {
			/* if a file was removed and it is now a
			 * directory, that is the same as ENOENT as
			 * far as git is concerned; we do not track
			 * directories unless they are submodules.
			 */
			if (!S_ISGITLINK(ce->ce_mode))
				continue;
		}

		/*
		 * "rm" of a path that has changes need to be treated
		 * carefully not to allow losing local changes
		 * accidentally.  A local change could be (1) file in
		 * work tree is different since the index; and/or (2)
		 * the user staged a content that is different from
		 * the current commit in the index.
		 *
		 * In such a case, you would need to --force the
		 * removal.  However, "rm --cached" (remove only from
		 * the index) is safe if the index matches the file in
		 * the work tree or the HEAD commit, as it means that
		 * the content being removed is available elsewhere.
		 */

		/*
		 * Is the index different from the file in the work tree?
		 * If it's a submodule, is its work tree modified?
		 */
		if (ce_match_stat(ce, &st, 0) ||
		    (S_ISGITLINK(ce->ce_mode) &&
		     bad_to_remove_submodule(ce->name,
				SUBMODULE_REMOVAL_DIE_ON_ERROR |
				SUBMODULE_REMOVAL_IGNORE_IGNORED_UNTRACKED)))
			local_changes = 1;

		/*
		 * Is the index different from the HEAD commit?  By
		 * definition, before the very initial commit,
		 * anything staged in the index is treated by the same
		 * way as changed from the HEAD.
		 */
		if (no_head
		     || get_tree_entry(the_repository, head, name, &oid, &mode)
		     || ce->ce_mode != create_ce_mode(mode)
		     || !oideq(&ce->oid, &oid))
			staged_changes = 1;

		/*
		 * If the index does not match the file in the work
		 * tree and if it does not match the HEAD commit
		 * either, (1) "git rm" without --cached definitely
		 * will lose information; (2) "git rm --cached" will
		 * lose information unless it is about removing an
		 * "intent to add" entry.
		 */
		if (local_changes && staged_changes) {
			if (!index_only || !ce_intent_to_add(ce))
				string_list_append(&files_staged, name);
		}
		else if (!index_only) {
			if (staged_changes)
				string_list_append(&files_cached, name);
			if (local_changes)
				string_list_append(&files_local, name);
		}
	}
	print_error_files(&files_staged,
			  Q_("the following file has staged content different "
			     "from both the\nfile and the HEAD:",
			     "the following files have staged content different"
			     " from both the\nfile and the HEAD:",
			     files_staged.nr),
			  _("\n(use -f to force removal)"),
			  &errs);
	string_list_clear(&files_staged, 0);
	print_error_files(&files_cached,
			  Q_("the following file has changes "
			     "staged in the index:",
			     "the following files have changes "
			     "staged in the index:", files_cached.nr),
			  _("\n(use --cached to keep the file,"
			    " or -f to force removal)"),
			  &errs);
	string_list_clear(&files_cached, 0);

	print_error_files(&files_local,
			  Q_("the following file has local modifications:",
			     "the following files have local modifications:",
			     files_local.nr),
			  _("\n(use --cached to keep the file,"
			    " or -f to force removal)"),
			  &errs);
	string_list_clear(&files_local, 0);

	return errs;
}