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
struct bsdtar {int flags; int verbose; int /*<<< orphan*/  matching; } ;
struct archive_entry {int dummy; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_EOF ; 
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int ARCHIVE_WARN ; 
 int OPTFLAG_INTERACTIVE ; 
 int /*<<< orphan*/  archive_entry_pathname (struct archive_entry*) ; 
 scalar_t__ archive_entry_size (struct archive_entry*) ; 
 char* archive_error_string (struct archive*) ; 
 scalar_t__ archive_match_excluded (int /*<<< orphan*/ ,struct archive_entry*) ; 
 int /*<<< orphan*/  archive_read_data_skip (struct archive*) ; 
 int archive_read_next_header (struct archive*,struct archive_entry**) ; 
 int archive_write_header (struct archive*,struct archive_entry*) ; 
 scalar_t__ copy_file_data_block (struct bsdtar*,struct archive*,struct archive*,struct archive_entry*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  lafe_warnc (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  list_item_verbose (struct bsdtar*,int /*<<< orphan*/ ,struct archive_entry*) ; 
 scalar_t__ need_report () ; 
 int /*<<< orphan*/  report_write (struct bsdtar*,struct archive*,struct archive_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  safe_fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  yes (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
append_archive(struct bsdtar *bsdtar, struct archive *a, struct archive *ina)
{
	struct archive_entry *in_entry;
	int e;

	while (ARCHIVE_OK == (e = archive_read_next_header(ina, &in_entry))) {
		if (archive_match_excluded(bsdtar->matching, in_entry))
			continue;
		if ((bsdtar->flags & OPTFLAG_INTERACTIVE) &&
		    !yes("copy '%s'", archive_entry_pathname(in_entry)))
			continue;
		if (bsdtar->verbose > 1) {
			safe_fprintf(stderr, "a ");
			list_item_verbose(bsdtar, stderr, in_entry);
		} else if (bsdtar->verbose > 0)
			safe_fprintf(stderr, "a %s",
			    archive_entry_pathname(in_entry));
		if (need_report())
			report_write(bsdtar, a, in_entry, 0);

		e = archive_write_header(a, in_entry);
		if (e != ARCHIVE_OK) {
			if (!bsdtar->verbose)
				lafe_warnc(0, "%s: %s",
				    archive_entry_pathname(in_entry),
				    archive_error_string(a));
			else
				fprintf(stderr, ": %s", archive_error_string(a));
		}
		if (e == ARCHIVE_FATAL)
			exit(1);

		if (e >= ARCHIVE_WARN) {
			if (archive_entry_size(in_entry) == 0)
				archive_read_data_skip(ina);
			else if (copy_file_data_block(bsdtar, a, ina, in_entry))
				exit(1);
		}

		if (bsdtar->verbose)
			fprintf(stderr, "\n");
	}

	return (e == ARCHIVE_EOF ? ARCHIVE_OK : e);
}