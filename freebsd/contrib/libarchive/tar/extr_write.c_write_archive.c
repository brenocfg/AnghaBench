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
struct bsdtar {int buff_size; int symlink_mode; char** argv; int return_value; int flags; struct archive* diskreader; int /*<<< orphan*/ * resolver; int /*<<< orphan*/ * buff; int /*<<< orphan*/ * names_from_file; int /*<<< orphan*/  readdisk_flags; int /*<<< orphan*/ * matching; scalar_t__ bytes_per_block; } ;
struct archive_entry {int dummy; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int OPTFLAG_TOTALS ; 
 scalar_t__ append_archive_filename (struct bsdtar*,struct archive*,char const*) ; 
 int /*<<< orphan*/  archive_entry_free (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_linkify (int /*<<< orphan*/ *,struct archive_entry**,struct archive_entry**) ; 
 int /*<<< orphan*/  archive_entry_linkresolver_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * archive_entry_linkresolver_new () ; 
 int /*<<< orphan*/  archive_entry_linkresolver_set_strategy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct archive_entry* archive_entry_new () ; 
 int /*<<< orphan*/  archive_entry_sourcepath (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_errno (struct archive*) ; 
 char* archive_error_string (struct archive*) ; 
 int /*<<< orphan*/  archive_filter_bytes (struct archive*,int) ; 
 int /*<<< orphan*/  archive_format (struct archive*) ; 
 int /*<<< orphan*/  archive_names_from_file (struct bsdtar*,struct archive*) ; 
 int /*<<< orphan*/  archive_read_close (struct archive*) ; 
 struct archive* archive_read_disk_new () ; 
 int archive_read_disk_open (struct archive*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_read_disk_set_behavior (struct archive*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_read_disk_set_matching (struct archive*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct bsdtar*) ; 
 int /*<<< orphan*/  archive_read_disk_set_metadata_filter_callback (struct archive*,int /*<<< orphan*/ *,struct bsdtar*) ; 
 int /*<<< orphan*/  archive_read_disk_set_standard_lookup (struct archive*) ; 
 int /*<<< orphan*/  archive_read_disk_set_symlink_hybrid (struct archive*) ; 
 int /*<<< orphan*/  archive_read_disk_set_symlink_logical (struct archive*) ; 
 int /*<<< orphan*/  archive_read_disk_set_symlink_physical (struct archive*) ; 
 int /*<<< orphan*/  archive_read_free (struct archive*) ; 
 int archive_read_next_header2 (struct archive*,struct archive_entry*) ; 
 scalar_t__ archive_write_close (struct archive*) ; 
 int /*<<< orphan*/  archive_write_free (struct archive*) ; 
 int /*<<< orphan*/  do_chdir (struct bsdtar*) ; 
 int /*<<< orphan*/ * excluded_callback ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lafe_errc (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lafe_warnc (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/ * metadata_filter ; 
 int /*<<< orphan*/  set_chdir (struct bsdtar*,char const*) ; 
 int /*<<< orphan*/  stderr ; 
 char* tar_i64toa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_file (struct bsdtar*,struct archive*,struct archive_entry*) ; 
 int /*<<< orphan*/  write_hierarchy (struct bsdtar*,struct archive*,char const*) ; 

__attribute__((used)) static void
write_archive(struct archive *a, struct bsdtar *bsdtar)
{
	const char *arg;
	struct archive_entry *entry, *sparse_entry;

	/* Choose a suitable copy buffer size */
	bsdtar->buff_size = 64 * 1024;
	while (bsdtar->buff_size < (size_t)bsdtar->bytes_per_block)
	  bsdtar->buff_size *= 2;
	/* Try to compensate for space we'll lose to alignment. */
	bsdtar->buff_size += 16 * 1024;

	/* Allocate a buffer for file data. */
	if ((bsdtar->buff = malloc(bsdtar->buff_size)) == NULL)
		lafe_errc(1, 0, "cannot allocate memory");

	if ((bsdtar->resolver = archive_entry_linkresolver_new()) == NULL)
		lafe_errc(1, 0, "cannot create link resolver");
	archive_entry_linkresolver_set_strategy(bsdtar->resolver,
	    archive_format(a));

	/* Create a read_disk object. */
	if ((bsdtar->diskreader = archive_read_disk_new()) == NULL)
		lafe_errc(1, 0, "Cannot create read_disk object");
	/* Tell the read_disk how handle symlink. */
	switch (bsdtar->symlink_mode) {
	case 'H':
		archive_read_disk_set_symlink_hybrid(bsdtar->diskreader);
		break;
	case 'L':
		archive_read_disk_set_symlink_logical(bsdtar->diskreader);
		break;
	default:
		archive_read_disk_set_symlink_physical(bsdtar->diskreader);
		break;
	}
	/* Register entry filters. */
	archive_read_disk_set_matching(bsdtar->diskreader,
	    bsdtar->matching, excluded_callback, bsdtar);
	archive_read_disk_set_metadata_filter_callback(
	    bsdtar->diskreader, metadata_filter, bsdtar);
	/* Set the behavior of archive_read_disk. */
	archive_read_disk_set_behavior(bsdtar->diskreader,
	    bsdtar->readdisk_flags);
	archive_read_disk_set_standard_lookup(bsdtar->diskreader);

	if (bsdtar->names_from_file != NULL)
		archive_names_from_file(bsdtar, a);

	while (*bsdtar->argv) {
		arg = *bsdtar->argv;
		if (arg[0] == '-' && arg[1] == 'C') {
			arg += 2;
			if (*arg == '\0') {
				bsdtar->argv++;
				arg = *bsdtar->argv;
				if (arg == NULL) {
					lafe_warnc(0, "%s",
					    "Missing argument for -C");
					bsdtar->return_value = 1;
					goto cleanup;
				}
				if (*arg == '\0') {
					lafe_warnc(0,
					    "Meaningless argument for -C: ''");
					bsdtar->return_value = 1;
					goto cleanup;
				}
			}
			set_chdir(bsdtar, arg);
		} else {
			if (*arg != '/')
				do_chdir(bsdtar); /* Handle a deferred -C */
			if (*arg == '@') {
				if (append_archive_filename(bsdtar, a,
				    arg + 1) != 0)
					break;
			} else
				write_hierarchy(bsdtar, a, arg);
		}
		bsdtar->argv++;
	}

	archive_read_disk_set_matching(bsdtar->diskreader, NULL, NULL, NULL);
	archive_read_disk_set_metadata_filter_callback(
	    bsdtar->diskreader, NULL, NULL);
	entry = NULL;
	archive_entry_linkify(bsdtar->resolver, &entry, &sparse_entry);
	while (entry != NULL) {
		int r;
		struct archive_entry *entry2;
		struct archive *disk = bsdtar->diskreader;

		/*
		 * This tricky code here is to correctly read the contents
		 * of the entry because the disk reader bsdtar->diskreader
		 * is pointing at does not have any information about the
		 * entry by this time and using archive_read_data_block()
		 * with the disk reader consequently must fail. And we
		 * have to re-open the entry to read the contents.
		 */
		/* TODO: Work with -C option as well. */
		r = archive_read_disk_open(disk,
			archive_entry_sourcepath(entry));
		if (r != ARCHIVE_OK) {
			lafe_warnc(archive_errno(disk),
			    "%s", archive_error_string(disk));
			bsdtar->return_value = 1;
			goto next_entry;
		}

		/*
		 * Invoke archive_read_next_header2() to work
		 * archive_read_data_block(), which is called via write_file(),
		 * without failure.
		 */
		entry2 = archive_entry_new();
		r = archive_read_next_header2(disk, entry2);
		archive_entry_free(entry2);
		if (r != ARCHIVE_OK) {
			lafe_warnc(archive_errno(disk),
			    "%s", archive_error_string(disk));
			if (r == ARCHIVE_FATAL)
				bsdtar->return_value = 1;
			archive_read_close(disk);
			goto next_entry;
		}

		write_file(bsdtar, a, entry);
		archive_read_close(disk);
next_entry:
		archive_entry_free(entry);
		entry = NULL;
		archive_entry_linkify(bsdtar->resolver, &entry, &sparse_entry);
	}

	if (archive_write_close(a)) {
		lafe_warnc(0, "%s", archive_error_string(a));
		bsdtar->return_value = 1;
	}

cleanup:
	/* Free file data buffer. */
	free(bsdtar->buff);
	archive_entry_linkresolver_free(bsdtar->resolver);
	bsdtar->resolver = NULL;
	archive_read_free(bsdtar->diskreader);
	bsdtar->diskreader = NULL;

	if (bsdtar->flags & OPTFLAG_TOTALS) {
		fprintf(stderr, "Total bytes written: %s\n",
		    tar_i64toa(archive_filter_bytes(a, -1)));
	}

	archive_write_free(a);
}