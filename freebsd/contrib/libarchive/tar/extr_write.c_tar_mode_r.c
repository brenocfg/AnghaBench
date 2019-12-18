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
struct bsdtar {int fd; int /*<<< orphan*/  filename; int /*<<< orphan*/  cset; } ;
struct archive_entry {int dummy; } ;
struct archive {int dummy; } ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 scalar_t__ ARCHIVE_FILTER_NONE ; 
 int ARCHIVE_FORMAT_BASE_MASK ; 
 int ARCHIVE_FORMAT_EMPTY ; 
 int ARCHIVE_FORMAT_TAR_PAX_RESTRICTED ; 
 int ARCHIVE_OK ; 
 int O_BINARY ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  archive_errno (struct archive*) ; 
 int /*<<< orphan*/  archive_error_string (struct archive*) ; 
 scalar_t__ archive_filter_code (struct archive*,int /*<<< orphan*/ ) ; 
 int archive_format (struct archive*) ; 
 int /*<<< orphan*/  archive_read_free (struct archive*) ; 
 int /*<<< orphan*/  archive_read_header_position (struct archive*) ; 
 struct archive* archive_read_new () ; 
 scalar_t__ archive_read_next_header (struct archive*,struct archive_entry**) ; 
 int archive_read_open_fd (struct archive*,int,int) ; 
 int /*<<< orphan*/  archive_read_support_filter_all (struct archive*) ; 
 int /*<<< orphan*/  archive_read_support_format_empty (struct archive*) ; 
 int /*<<< orphan*/  archive_read_support_format_gnutar (struct archive*) ; 
 int /*<<< orphan*/  archive_read_support_format_tar (struct archive*) ; 
 struct archive* archive_write_new () ; 
 int archive_write_open_fd (struct archive*,int) ; 
 int /*<<< orphan*/  archive_write_set_format (struct archive*,int) ; 
 int /*<<< orphan*/  archive_write_set_format_by_name (struct archive*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/ * cset_get_format (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  lafe_errc (int,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* open (int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  set_reader_options (struct bsdtar*,struct archive*) ; 
 int /*<<< orphan*/  set_writer_options (struct bsdtar*,struct archive*) ; 
 int /*<<< orphan*/  test_for_append (struct bsdtar*) ; 
 int /*<<< orphan*/  write_archive (struct archive*,struct bsdtar*) ; 

void
tar_mode_r(struct bsdtar *bsdtar)
{
	int64_t	end_offset;
	int	format;
	struct archive *a;
	struct archive_entry *entry;
	int	r;

	/* Sanity-test some arguments and the file. */
	test_for_append(bsdtar);

	format = ARCHIVE_FORMAT_TAR_PAX_RESTRICTED;

#if defined(__BORLANDC__)
	bsdtar->fd = open(bsdtar->filename, O_RDWR | O_CREAT | O_BINARY);
#else
	bsdtar->fd = open(bsdtar->filename, O_RDWR | O_CREAT | O_BINARY, 0666);
#endif
	if (bsdtar->fd < 0)
		lafe_errc(1, errno,
		    "Cannot open %s", bsdtar->filename);

	a = archive_read_new();
	archive_read_support_filter_all(a);
	archive_read_support_format_empty(a);
	archive_read_support_format_tar(a);
	archive_read_support_format_gnutar(a);
	set_reader_options(bsdtar, a);
	r = archive_read_open_fd(a, bsdtar->fd, 10240);
	if (r != ARCHIVE_OK)
		lafe_errc(1, archive_errno(a),
		    "Can't read archive %s: %s", bsdtar->filename,
		    archive_error_string(a));
	while (0 == archive_read_next_header(a, &entry)) {
		if (archive_filter_code(a, 0) != ARCHIVE_FILTER_NONE) {
			archive_read_free(a);
			close(bsdtar->fd);
			lafe_errc(1, 0,
			    "Cannot append to compressed archive.");
		}
		/* Keep going until we hit end-of-archive */
		format = archive_format(a);
	}

	end_offset = archive_read_header_position(a);
	archive_read_free(a);

	/* Re-open archive for writing */
	a = archive_write_new();
	/*
	 * Set the format to be used for writing.  To allow people to
	 * extend empty files, we need to allow them to specify the format,
	 * which opens the possibility that they will specify a format that
	 * doesn't match the existing format.  Hence, the following bit
	 * of arcane ugliness.
	 */

	if (cset_get_format(bsdtar->cset) != NULL) {
		/* If the user requested a format, use that, but ... */
		archive_write_set_format_by_name(a,
		    cset_get_format(bsdtar->cset));
		/* ... complain if it's not compatible. */
		format &= ARCHIVE_FORMAT_BASE_MASK;
		if (format != (int)(archive_format(a) & ARCHIVE_FORMAT_BASE_MASK)
		    && format != ARCHIVE_FORMAT_EMPTY) {
			lafe_errc(1, 0,
			    "Format %s is incompatible with the archive %s.",
			    cset_get_format(bsdtar->cset), bsdtar->filename);
		}
	} else {
		/*
		 * Just preserve the current format, with a little care
		 * for formats that libarchive can't write.
		 */
		if (format == ARCHIVE_FORMAT_EMPTY)
			format = ARCHIVE_FORMAT_TAR_PAX_RESTRICTED;
		archive_write_set_format(a, format);
	}
	if (lseek(bsdtar->fd, end_offset, SEEK_SET) < 0)
		lafe_errc(1, errno, "Could not seek to archive end");
	set_writer_options(bsdtar, a);
	if (ARCHIVE_OK != archive_write_open_fd(a, bsdtar->fd))
		lafe_errc(1, 0, "%s", archive_error_string(a));

	write_archive(a, bsdtar); /* XXX check return val XXX */

	close(bsdtar->fd);
	bsdtar->fd = -1;
}