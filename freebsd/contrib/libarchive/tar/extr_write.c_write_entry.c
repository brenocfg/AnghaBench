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
struct bsdtar {int verbose; int /*<<< orphan*/  diskreader; } ;
struct archive_entry {int dummy; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int ARCHIVE_WARN ; 
 int /*<<< orphan*/  archive_entry_pathname (struct archive_entry*) ; 
 scalar_t__ archive_entry_size (struct archive_entry*) ; 
 char* archive_error_string (struct archive*) ; 
 int archive_write_header (struct archive*,struct archive_entry*) ; 
 scalar_t__ copy_file_data_block (struct bsdtar*,struct archive*,int /*<<< orphan*/ ,struct archive_entry*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  lafe_warnc (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  list_item_verbose (struct bsdtar*,int /*<<< orphan*/ ,struct archive_entry*) ; 
 int /*<<< orphan*/  safe_fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
write_entry(struct bsdtar *bsdtar, struct archive *a,
    struct archive_entry *entry)
{
	int e;

	e = archive_write_header(a, entry);
	if (e != ARCHIVE_OK) {
		if (bsdtar->verbose > 1) {
			safe_fprintf(stderr, "a ");
			list_item_verbose(bsdtar, stderr, entry);
			lafe_warnc(0, ": %s", archive_error_string(a));
		} else if (bsdtar->verbose > 0) {
			lafe_warnc(0, "%s: %s",
			    archive_entry_pathname(entry),
			    archive_error_string(a));
		} else
			fprintf(stderr, ": %s", archive_error_string(a));
	}

	if (e == ARCHIVE_FATAL)
		exit(1);

	/*
	 * If we opened a file earlier, write it out now.  Note that
	 * the format handler might have reset the size field to zero
	 * to inform us that the archive body won't get stored.  In
	 * that case, just skip the write.
	 */
	if (e >= ARCHIVE_WARN && archive_entry_size(entry) > 0) {
		if (copy_file_data_block(bsdtar, a, bsdtar->diskreader, entry))
			exit(1);
	}
}