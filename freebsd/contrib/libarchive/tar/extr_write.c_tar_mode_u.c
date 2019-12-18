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
struct bsdtar {int fd; struct archive_dir* archive_dir; int /*<<< orphan*/  bytes_in_last_block; int /*<<< orphan*/  bytes_per_block; struct archive* matching; int /*<<< orphan*/  filename; } ;
struct archive_entry {int dummy; } ;
struct archive_dir_entry {struct archive_dir_entry* name; struct archive_dir_entry* next; } ;
struct archive_dir {int /*<<< orphan*/ * tail; struct archive_dir_entry* head; } ;
struct archive {int dummy; } ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  archive_dir ;

/* Variables and functions */
 scalar_t__ ARCHIVE_FILTER_NONE ; 
 int ARCHIVE_FORMAT_TAR_PAX_RESTRICTED ; 
 int ARCHIVE_MATCH_EQUAL ; 
 int ARCHIVE_MATCH_MTIME ; 
 int ARCHIVE_MATCH_OLDER ; 
 scalar_t__ ARCHIVE_OK ; 
 int O_BINARY ; 
 int O_RDWR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  archive_error_string (struct archive*) ; 
 scalar_t__ archive_filter_code (struct archive*,int /*<<< orphan*/ ) ; 
 int archive_format (struct archive*) ; 
 scalar_t__ archive_match_exclude_entry (struct archive*,int,struct archive_entry*) ; 
 int /*<<< orphan*/  archive_read_free (struct archive*) ; 
 int /*<<< orphan*/  archive_read_header_position (struct archive*) ; 
 struct archive* archive_read_new () ; 
 scalar_t__ archive_read_next_header (struct archive*,struct archive_entry**) ; 
 scalar_t__ archive_read_open_fd (struct archive*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_read_support_filter_all (struct archive*) ; 
 int /*<<< orphan*/  archive_read_support_format_gnutar (struct archive*) ; 
 int /*<<< orphan*/  archive_read_support_format_tar (struct archive*) ; 
 struct archive* archive_write_new () ; 
 scalar_t__ archive_write_open_fd (struct archive*,int) ; 
 int /*<<< orphan*/  archive_write_set_bytes_in_last_block (struct archive*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_write_set_bytes_per_block (struct archive*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_write_set_format (struct archive*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (struct archive_dir_entry*) ; 
 int /*<<< orphan*/  lafe_errc (int,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct archive_dir*,int /*<<< orphan*/ ,int) ; 
 int open (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_reader_options (struct bsdtar*,struct archive*) ; 
 int /*<<< orphan*/  set_writer_options (struct bsdtar*,struct archive*) ; 
 int /*<<< orphan*/  test_for_append (struct bsdtar*) ; 
 int /*<<< orphan*/  write_archive (struct archive*,struct bsdtar*) ; 

void
tar_mode_u(struct bsdtar *bsdtar)
{
	int64_t			 end_offset;
	struct archive		*a;
	struct archive_entry	*entry;
	int			 format;
	struct archive_dir_entry	*p;
	struct archive_dir	 archive_dir;

	bsdtar->archive_dir = &archive_dir;
	memset(&archive_dir, 0, sizeof(archive_dir));

	format = ARCHIVE_FORMAT_TAR_PAX_RESTRICTED;

	/* Sanity-test some arguments and the file. */
	test_for_append(bsdtar);

	bsdtar->fd = open(bsdtar->filename, O_RDWR | O_BINARY);
	if (bsdtar->fd < 0)
		lafe_errc(1, errno,
		    "Cannot open %s", bsdtar->filename);

	a = archive_read_new();
	archive_read_support_filter_all(a);
	archive_read_support_format_tar(a);
	archive_read_support_format_gnutar(a);
	set_reader_options(bsdtar, a);
	if (archive_read_open_fd(a, bsdtar->fd, bsdtar->bytes_per_block)
	    != ARCHIVE_OK) {
		lafe_errc(1, 0,
		    "Can't open %s: %s", bsdtar->filename,
		    archive_error_string(a));
	}

	/* Build a list of all entries and their recorded mod times. */
	while (0 == archive_read_next_header(a, &entry)) {
		if (archive_filter_code(a, 0) != ARCHIVE_FILTER_NONE) {
			archive_read_free(a);
			close(bsdtar->fd);
			lafe_errc(1, 0,
			    "Cannot append to compressed archive.");
		}
		if (archive_match_exclude_entry(bsdtar->matching,
		    ARCHIVE_MATCH_MTIME | ARCHIVE_MATCH_OLDER |
		    ARCHIVE_MATCH_EQUAL, entry) != ARCHIVE_OK)
			lafe_errc(1, 0, "Error : %s",
			    archive_error_string(bsdtar->matching));
		/* Record the last format determination we see */
		format = archive_format(a);
		/* Keep going until we hit end-of-archive */
	}

	end_offset = archive_read_header_position(a);
	archive_read_free(a);

	/* Re-open archive for writing. */
	a = archive_write_new();
	/*
	 * Set format to same one auto-detected above.
	 */
	archive_write_set_format(a, format);
	archive_write_set_bytes_per_block(a, bsdtar->bytes_per_block);
	archive_write_set_bytes_in_last_block(a, bsdtar->bytes_in_last_block);

	if (lseek(bsdtar->fd, end_offset, SEEK_SET) < 0)
		lafe_errc(1, errno, "Could not seek to archive end");
	set_writer_options(bsdtar, a);
	if (ARCHIVE_OK != archive_write_open_fd(a, bsdtar->fd))
		lafe_errc(1, 0, "%s", archive_error_string(a));

	write_archive(a, bsdtar);

	close(bsdtar->fd);
	bsdtar->fd = -1;

	while (bsdtar->archive_dir->head != NULL) {
		p = bsdtar->archive_dir->head->next;
		free(bsdtar->archive_dir->head->name);
		free(bsdtar->archive_dir->head);
		bsdtar->archive_dir->head = p;
	}
	bsdtar->archive_dir->tail = NULL;
}