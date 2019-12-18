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
struct bsdtar {int return_value; int first_fs; int verbose; int /*<<< orphan*/  resolver; int /*<<< orphan*/  gname; int /*<<< orphan*/  uname; int /*<<< orphan*/  gid; struct archive* diskreader; int /*<<< orphan*/  uid; } ;
struct archive_entry {int dummy; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 scalar_t__ AE_IFREG ; 
 int ARCHIVE_EOF ; 
 int ARCHIVE_FAILED ; 
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int ARCHIVE_WARN ; 
 scalar_t__ archive_entry_filetype (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_free (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_linkify (int /*<<< orphan*/ ,struct archive_entry**,struct archive_entry**) ; 
 struct archive_entry* archive_entry_new () ; 
 int /*<<< orphan*/  archive_entry_pathname (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_set_gid (struct archive_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_set_gname (struct archive_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_set_size (struct archive_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_set_uid (struct archive_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_set_uname (struct archive_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_errno (struct archive*) ; 
 int /*<<< orphan*/  archive_error_string (struct archive*) ; 
 int /*<<< orphan*/  archive_read_close (struct archive*) ; 
 int /*<<< orphan*/  archive_read_disk_gname (struct archive*,int /*<<< orphan*/ ) ; 
 int archive_read_disk_open (struct archive*,char const*) ; 
 int /*<<< orphan*/  archive_read_disk_uname (struct archive*,int /*<<< orphan*/ ) ; 
 int archive_read_next_header2 (struct archive*,struct archive_entry*) ; 
 scalar_t__ edit_pathname (struct bsdtar*,struct archive_entry*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lafe_warnc (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_item_verbose (struct bsdtar*,int /*<<< orphan*/ ,struct archive_entry*) ; 
 int /*<<< orphan*/  safe_fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  write_file (struct bsdtar*,struct archive*,struct archive_entry*) ; 

__attribute__((used)) static void
write_hierarchy(struct bsdtar *bsdtar, struct archive *a, const char *path)
{
	struct archive *disk = bsdtar->diskreader;
	struct archive_entry *entry = NULL, *spare_entry = NULL;
	int r;

	r = archive_read_disk_open(disk, path);
	if (r != ARCHIVE_OK) {
		lafe_warnc(archive_errno(disk),
		    "%s", archive_error_string(disk));
		bsdtar->return_value = 1;
		return;
	}
	bsdtar->first_fs = -1;

	for (;;) {
		archive_entry_free(entry);
		entry = archive_entry_new();
		r = archive_read_next_header2(disk, entry);
		if (r == ARCHIVE_EOF)
			break;
		else if (r != ARCHIVE_OK) {
			lafe_warnc(archive_errno(disk),
			    "%s", archive_error_string(disk));
			if (r == ARCHIVE_FATAL || r == ARCHIVE_FAILED) {
				bsdtar->return_value = 1;
				archive_entry_free(entry);
				archive_read_close(disk);
				return;
			} else if (r < ARCHIVE_WARN)
				continue;
		}

		if (bsdtar->uid >= 0) {
			archive_entry_set_uid(entry, bsdtar->uid);
			if (!bsdtar->uname)
				archive_entry_set_uname(entry,
				    archive_read_disk_uname(bsdtar->diskreader,
					bsdtar->uid));
		}
		if (bsdtar->gid >= 0) {
			archive_entry_set_gid(entry, bsdtar->gid);
			if (!bsdtar->gname)
				archive_entry_set_gname(entry,
				    archive_read_disk_gname(bsdtar->diskreader,
					bsdtar->gid));
		}
		if (bsdtar->uname)
			archive_entry_set_uname(entry, bsdtar->uname);
		if (bsdtar->gname)
			archive_entry_set_gname(entry, bsdtar->gname);

		/*
		 * Rewrite the pathname to be archived.  If rewrite
		 * fails, skip the entry.
		 */
		if (edit_pathname(bsdtar, entry))
			continue;

		/* Display entry as we process it. */
		if (bsdtar->verbose > 1) {
			safe_fprintf(stderr, "a ");
			list_item_verbose(bsdtar, stderr, entry);
		} else if (bsdtar->verbose > 0) {
		/* This format is required by SUSv2. */
			safe_fprintf(stderr, "a %s",
			    archive_entry_pathname(entry));
		}

		/* Non-regular files get archived with zero size. */
		if (archive_entry_filetype(entry) != AE_IFREG)
			archive_entry_set_size(entry, 0);

		archive_entry_linkify(bsdtar->resolver, &entry, &spare_entry);

		while (entry != NULL) {
			write_file(bsdtar, a, entry);
			archive_entry_free(entry);
			entry = spare_entry;
			spare_entry = NULL;
		}

		if (bsdtar->verbose)
			fprintf(stderr, "\n");
	}
	archive_entry_free(entry);
	archive_read_close(disk);
}