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
struct archive_entry {int dummy; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int AE_IFREG ; 
 int ARCHIVE_EOF ; 
 int ARCHIVE_FATAL ; 
 int ARCHIVE_FILTER_LRZIP ; 
 int ARCHIVE_FORMAT_TAR_USTAR ; 
 int ARCHIVE_OK ; 
 int ARCHIVE_WARN ; 
 int /*<<< orphan*/  archive_entry_atime (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_copy_pathname (struct archive_entry*,char*) ; 
 int /*<<< orphan*/  archive_entry_ctime (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_filetype (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_free (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_mode (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_mtime (struct archive_entry*) ; 
 struct archive_entry* archive_entry_new () ; 
 int /*<<< orphan*/  archive_entry_pathname (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_set_atime (struct archive_entry*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_set_ctime (struct archive_entry*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_set_mode (struct archive_entry*,int) ; 
 int /*<<< orphan*/  archive_entry_set_mtime (struct archive_entry*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_set_size (struct archive_entry*,int) ; 
 int /*<<< orphan*/  archive_entry_size (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_error_string (struct archive*) ; 
 int archive_filter_code (struct archive*,int /*<<< orphan*/ ) ; 
 int archive_format (struct archive*) ; 
 int /*<<< orphan*/  archive_read_close (struct archive*) ; 
 int /*<<< orphan*/  archive_read_free (struct archive*) ; 
 struct archive* archive_read_new () ; 
 int archive_read_next_header (struct archive*,struct archive_entry**) ; 
 int archive_read_open_memory (struct archive*,char*,size_t) ; 
 int archive_read_support_filter_all (struct archive*) ; 
 int archive_read_support_format_all (struct archive*) ; 
 int archive_write_add_filter_by_name (struct archive*,char const*) ; 
 int archive_write_close (struct archive*) ; 
 int /*<<< orphan*/  archive_write_data (struct archive*,char*,int) ; 
 int /*<<< orphan*/  archive_write_free (struct archive*) ; 
 int /*<<< orphan*/  archive_write_header (struct archive*,struct archive_entry*) ; 
 struct archive* archive_write_new () ; 
 int archive_write_open_memory (struct archive*,char*,size_t,size_t*) ; 
 int archive_write_set_bytes_per_block (struct archive*,int) ; 
 int archive_write_set_format_ustar (struct archive*) ; 
 int archive_write_set_options (struct archive*,char*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualInt (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualIntA (struct archive*,int,int) ; 
 int /*<<< orphan*/  assertEqualString (char*,int /*<<< orphan*/ ) ; 
 char* calloc (int,size_t) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  skipping (char*,char const*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
test_filter_by_name(const char *filter_name, int filter_code,
    int (*can_filter_prog)(void))
{
	struct archive_entry *ae;
	struct archive *a;
	size_t used;
	size_t buffsize = 1024 * 128;
	char *buff;
	int r;

	assert((buff = calloc(1, buffsize)) != NULL);
	if (buff == NULL)
		return;

	/* Create a new archive in memory. */
	assert((a = archive_write_new()) != NULL);
	assertEqualIntA(a, ARCHIVE_OK, archive_write_set_format_ustar(a));
	r = archive_write_add_filter_by_name(a, filter_name);
	if (r == ARCHIVE_WARN) {
		if (!can_filter_prog()) {
			skipping("%s filter not supported on this platform",
			    filter_name);
			assertEqualInt(ARCHIVE_OK, archive_write_free(a));
			free(buff);
			return;
		}
	} else if (r == ARCHIVE_FATAL &&
	    (strcmp(archive_error_string(a),
		   "lzma compression not supported on this platform") == 0 ||
	     strcmp(archive_error_string(a),
		   "xz compression not supported on this platform") == 0)) {
		skipping("%s filter not supported on this platform", filter_name);
		assertEqualInt(ARCHIVE_OK, archive_write_free(a));
		free(buff);
		return;
	} else {
		if (!assertEqualIntA(a, ARCHIVE_OK, r)) {
			assertEqualInt(ARCHIVE_OK, archive_write_free(a));
			free(buff);
			return;
		}
	}
	if (filter_code == ARCHIVE_FILTER_LRZIP)
	{
		/*
		 * There's a bug in lrzip (as of release 0.612) where 2nd stage
		 * compression can't be performed on smaller files. Set lrzip to
		 * use no 2nd stage compression.
		 */
		assertEqualIntA(a, ARCHIVE_OK,
			archive_write_set_options(a, "lrzip:compression=none"));
	}
	assertEqualIntA(a, ARCHIVE_OK, archive_write_set_bytes_per_block(a, 10));
	assertEqualIntA(a, ARCHIVE_OK,
	    archive_write_open_memory(a, buff, buffsize, &used));

	/*
	 * Write a file to it.
	 */
	assert((ae = archive_entry_new()) != NULL);
	archive_entry_set_mtime(ae, 1, 0);
	assertEqualInt(1, archive_entry_mtime(ae));
	archive_entry_set_ctime(ae, 1, 0);
	assertEqualInt(1, archive_entry_ctime(ae));
	archive_entry_set_atime(ae, 1, 0);
	assertEqualInt(1, archive_entry_atime(ae));
	archive_entry_copy_pathname(ae, "file");
	assertEqualString("file", archive_entry_pathname(ae));
	archive_entry_set_mode(ae, AE_IFREG | 0755);
	assertEqualInt((AE_IFREG | 0755), archive_entry_mode(ae));
	archive_entry_set_size(ae, 8);
	assertEqualInt(0, archive_write_header(a, ae));
	archive_entry_free(ae);
	assertEqualInt(8, archive_write_data(a, "12345678", 8));

	/* Close out the archive. */
	assertEqualIntA(a, ARCHIVE_OK, archive_write_close(a));
	assertEqualInt(ARCHIVE_OK, archive_write_free(a));

	/*
	 * Now, read the data back.
	 */
	assert((a = archive_read_new()) != NULL);
	assertEqualIntA(a, ARCHIVE_OK, archive_read_support_format_all(a));
	assertEqualIntA(a, ARCHIVE_OK, archive_read_support_filter_all(a));
	assertEqualIntA(a, ARCHIVE_OK, archive_read_open_memory(a, buff, used));

	/*
	 * Read and verify the file.
	 */
	assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header(a, &ae));
	assertEqualInt(1, archive_entry_mtime(ae));
	assertEqualString("file", archive_entry_pathname(ae));
	assertEqualInt(AE_IFREG, archive_entry_filetype(ae));
	assertEqualInt(8, archive_entry_size(ae));

	/* Verify the end of the archive. */
	assertEqualIntA(a, ARCHIVE_EOF, archive_read_next_header(a, &ae));

	/* Verify archive format. */
	assertEqualIntA(a, filter_code, archive_filter_code(a, 0));
	assertEqualIntA(a, ARCHIVE_FORMAT_TAR_USTAR, archive_format(a));

	assertEqualInt(ARCHIVE_OK, archive_read_close(a));
	assertEqualInt(ARCHIVE_OK, archive_read_free(a));
	free(buff);
}