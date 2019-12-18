#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int max_depth; } ;
struct TYPE_7__ {int iso_level; scalar_t__ joliet; scalar_t__ limit_dirs; scalar_t__ rr; int /*<<< orphan*/  limit_depth; } ;
struct iso9660 {scalar_t__ dircnt_max; TYPE_2__ joliet; TYPE_1__ opt; TYPE_2__ primary; } ;
struct archive_write {int /*<<< orphan*/  archive; struct iso9660* format_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_ERRNO_MISC ; 
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 scalar_t__ MAX_DEPTH ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  calculate_path_table_size (TYPE_2__*) ; 
 int isoent_alloc_path_table (struct archive_write*,TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  isoent_collect_dirs (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int isoent_make_path_table_2 (struct archive_write*,TYPE_2__*,int,int*) ; 
 int isoent_rr_move (struct archive_write*) ; 
 int isoent_traverse_tree (struct archive_write*,TYPE_2__*) ; 
 int /*<<< orphan*/  isofile_connect_hardlink_files (struct iso9660*) ; 

__attribute__((used)) static int
isoent_make_path_table(struct archive_write *a)
{
	struct iso9660 *iso9660 = a->format_data;
	int depth, r;
	int dir_number;

	/*
	 * Init Path Table.
	 */
	if (iso9660->dircnt_max >= MAX_DEPTH &&
	    (!iso9660->opt.limit_depth || iso9660->opt.iso_level == 4))
		r = isoent_alloc_path_table(a, &(iso9660->primary),
		    iso9660->dircnt_max + 1);
	else
		/* The number of levels in the hierarchy cannot exceed
		 * eight. */
		r = isoent_alloc_path_table(a, &(iso9660->primary),
		    MAX_DEPTH);
	if (r < 0)
		return (r);
	if (iso9660->opt.joliet) {
		r = isoent_alloc_path_table(a, &(iso9660->joliet),
		    iso9660->dircnt_max + 1);
		if (r < 0)
			return (r);
	}

	/* Step 0.
	 * - Collect directories for primary and joliet.
	 */
	isoent_collect_dirs(&(iso9660->primary), NULL, 0);
	if (iso9660->opt.joliet)
		isoent_collect_dirs(&(iso9660->joliet), NULL, 0);
	/*
	 * Rockridge; move deeper depth directories to rr_moved.
	 */
	if (iso9660->opt.rr) {
		r = isoent_rr_move(a);
		if (r < 0)
			return (r);
	}

 	/* Update nlink. */
	isofile_connect_hardlink_files(iso9660);

	/* Step 1.
	 * - Renew a value of the depth of that directories.
	 * - Resolve hardlinks.
 	 * - Convert pathnames to ISO9660 name or UCS2(joliet).
	 * - Sort files by each directory.
	 */
	r = isoent_traverse_tree(a, &(iso9660->primary));
	if (r < 0)
		return (r);
	if (iso9660->opt.joliet) {
		r = isoent_traverse_tree(a, &(iso9660->joliet));
		if (r < 0)
			return (r);
	}

	/* Step 2.
	 * - Sort directories.
	 * - Assign all directory number.
	 */
	dir_number = 1;
	for (depth = 0; depth < iso9660->primary.max_depth; depth++) {
		r = isoent_make_path_table_2(a, &(iso9660->primary),
		    depth, &dir_number);
		if (r < 0)
			return (r);
	}
	if (iso9660->opt.joliet) {
		dir_number = 1;
		for (depth = 0; depth < iso9660->joliet.max_depth; depth++) {
			r = isoent_make_path_table_2(a, &(iso9660->joliet),
			    depth, &dir_number);
			if (r < 0)
				return (r);
		}
	}
	if (iso9660->opt.limit_dirs && dir_number > 0xffff) {
		/*
		 * Maximum number of directories is 65535(0xffff)
		 * doe to size(16bit) of Parent Directory Number of
		 * the Path Table.
		 * See also ISO9660 Standard 9.4.
		 */
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Too many directories(%d) over 65535.", dir_number);
		return (ARCHIVE_FATAL);
	}

	/* Get the size of the Path Table. */
	calculate_path_table_size(&(iso9660->primary));
	if (iso9660->opt.joliet)
		calculate_path_table_size(&(iso9660->joliet));

	return (ARCHIVE_OK);
}