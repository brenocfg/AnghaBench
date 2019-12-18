#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct rename {char dir_rename_original_type; int /*<<< orphan*/  dir_rename_original_dest; } ;
struct merge_options {scalar_t__ detect_directory_renames; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 scalar_t__ MERGE_DIRECTORY_RENAMES_NONE ; 
 scalar_t__ MERGE_DIRECTORY_RENAMES_TRUE ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dir_rename_warning (char const*,int,int,struct merge_options*,struct rename*) ; 

__attribute__((used)) static int warn_about_dir_renamed_entries(struct merge_options *opt,
					  struct rename *ren)
{
	const char *msg;
	int clean = 1, is_add;

	if (!ren)
		return clean;

	/* Return early if ren was not affected/created by a directory rename */
	if (!ren->dir_rename_original_dest)
		return clean;

	/* Sanity checks */
	assert(opt->detect_directory_renames > MERGE_DIRECTORY_RENAMES_NONE);
	assert(ren->dir_rename_original_type == 'A' ||
	       ren->dir_rename_original_type == 'R');

	/* Check whether to treat directory renames as a conflict */
	clean = (opt->detect_directory_renames == MERGE_DIRECTORY_RENAMES_TRUE);

	is_add = (ren->dir_rename_original_type == 'A');
	if (ren->dir_rename_original_type == 'A' && clean) {
		msg = _("Path updated: %s added in %s inside a "
			"directory that was renamed in %s; moving it to %s.");
	} else if (ren->dir_rename_original_type == 'A' && !clean) {
		msg = _("CONFLICT (file location): %s added in %s "
			"inside a directory that was renamed in %s, "
			"suggesting it should perhaps be moved to %s.");
	} else if (ren->dir_rename_original_type == 'R' && clean) {
		msg = _("Path updated: %s renamed to %s in %s, inside a "
			"directory that was renamed in %s; moving it to %s.");
	} else if (ren->dir_rename_original_type == 'R' && !clean) {
		msg = _("CONFLICT (file location): %s renamed to %s in %s, "
			"inside a directory that was renamed in %s, "
			"suggesting it should perhaps be moved to %s.");
	} else {
		BUG("Impossible dir_rename_original_type/clean combination");
	}
	dir_rename_warning(msg, is_add, clean, opt, ren);

	return clean;
}