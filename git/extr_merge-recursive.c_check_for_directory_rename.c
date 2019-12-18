#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tree {int dummy; } ;
struct merge_options {int dummy; } ;
struct hashmap {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  buf; } ;
struct dir_rename_entry {TYPE_1__ new_dir; int /*<<< orphan*/  dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 struct dir_rename_entry* check_dir_renamed (char const*,struct hashmap*) ; 
 struct dir_rename_entry* dir_rename_find_entry (struct hashmap*,int /*<<< orphan*/ ) ; 
 char* handle_path_level_conflicts (struct merge_options*,char const*,struct dir_rename_entry*,struct hashmap*,struct tree*) ; 
 int /*<<< orphan*/  output (struct merge_options*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *check_for_directory_rename(struct merge_options *opt,
					const char *path,
					struct tree *tree,
					struct hashmap *dir_renames,
					struct hashmap *dir_rename_exclusions,
					struct hashmap *collisions,
					int *clean_merge)
{
	char *new_path = NULL;
	struct dir_rename_entry *entry = check_dir_renamed(path, dir_renames);
	struct dir_rename_entry *oentry = NULL;

	if (!entry)
		return new_path;

	/*
	 * This next part is a little weird.  We do not want to do an
	 * implicit rename into a directory we renamed on our side, because
	 * that will result in a spurious rename/rename(1to2) conflict.  An
	 * example:
	 *   Base commit: dumbdir/afile, otherdir/bfile
	 *   Side 1:      smrtdir/afile, otherdir/bfile
	 *   Side 2:      dumbdir/afile, dumbdir/bfile
	 * Here, while working on Side 1, we could notice that otherdir was
	 * renamed/merged to dumbdir, and change the diff_filepair for
	 * otherdir/bfile into a rename into dumbdir/bfile.  However, Side
	 * 2 will notice the rename from dumbdir to smrtdir, and do the
	 * transitive rename to move it from dumbdir/bfile to
	 * smrtdir/bfile.  That gives us bfile in dumbdir vs being in
	 * smrtdir, a rename/rename(1to2) conflict.  We really just want
	 * the file to end up in smrtdir.  And the way to achieve that is
	 * to not let Side1 do the rename to dumbdir, since we know that is
	 * the source of one of our directory renames.
	 *
	 * That's why oentry and dir_rename_exclusions is here.
	 *
	 * As it turns out, this also prevents N-way transient rename
	 * confusion; See testcases 9c and 9d of t6043.
	 */
	oentry = dir_rename_find_entry(dir_rename_exclusions, entry->new_dir.buf);
	if (oentry) {
		output(opt, 1, _("WARNING: Avoiding applying %s -> %s rename "
			       "to %s, because %s itself was renamed."),
		       entry->dir, entry->new_dir.buf, path, entry->new_dir.buf);
	} else {
		new_path = handle_path_level_conflicts(opt, path, entry,
						       collisions, tree);
		*clean_merge &= (new_path != NULL);
	}

	return new_path;
}