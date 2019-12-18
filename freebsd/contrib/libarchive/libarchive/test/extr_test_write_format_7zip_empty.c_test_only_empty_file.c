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
 int ARCHIVE_FILTER_NONE ; 
 int ARCHIVE_FORMAT_7ZIP ; 
 int ARCHIVE_OK ; 
 int S_IFREG ; 
 size_t archive_entry_atime (struct archive_entry*) ; 
 size_t archive_entry_atime_nsec (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_copy_pathname (struct archive_entry*,char*) ; 
 size_t archive_entry_ctime (struct archive_entry*) ; 
 size_t archive_entry_ctime_nsec (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_free (struct archive_entry*) ; 
 size_t archive_entry_mode (struct archive_entry*) ; 
 size_t archive_entry_mtime (struct archive_entry*) ; 
 size_t archive_entry_mtime_nsec (struct archive_entry*) ; 
 struct archive_entry* archive_entry_new () ; 
 int /*<<< orphan*/  archive_entry_pathname (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_set_atime (struct archive_entry*,int,int) ; 
 int /*<<< orphan*/  archive_entry_set_ctime (struct archive_entry*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  archive_entry_set_mode (struct archive_entry*,int) ; 
 int /*<<< orphan*/  archive_entry_set_mtime (struct archive_entry*,int,int) ; 
 size_t archive_entry_size (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_filter_code (struct archive*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_format (struct archive*) ; 
 size_t archive_read_close (struct archive*) ; 
 size_t archive_read_free (struct archive*) ; 
 struct archive* archive_read_new () ; 
 int /*<<< orphan*/  archive_read_next_header (struct archive*,struct archive_entry**) ; 
 int /*<<< orphan*/  archive_read_support_filter_all (struct archive*) ; 
 int /*<<< orphan*/  archive_read_support_format_all (struct archive*) ; 
 int /*<<< orphan*/  archive_write_add_filter_none (struct archive*) ; 
 size_t archive_write_close (struct archive*) ; 
 size_t archive_write_free (struct archive*) ; 
 size_t archive_write_header (struct archive*,struct archive_entry*) ; 
 struct archive* archive_write_new () ; 
 int /*<<< orphan*/  archive_write_open_memory (struct archive*,char*,size_t,size_t*) ; 
 int /*<<< orphan*/  archive_write_set_format_7zip (struct archive*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualInt (int,size_t) ; 
 int /*<<< orphan*/  assertEqualIntA (struct archive*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualMem (char*,char*,int) ; 
 int /*<<< orphan*/  assertEqualString (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  read_open_memory_seek (struct archive*,char*,size_t,int) ; 

__attribute__((used)) static void
test_only_empty_file(void)
{
	struct archive *a;
	struct archive_entry *ae;
	size_t buffsize = 1000;
	char *buff;
	size_t used;

	buff = malloc(buffsize);

	/* Create a new archive in memory. */
	assert((a = archive_write_new()) != NULL);
	assertEqualIntA(a, ARCHIVE_OK, archive_write_set_format_7zip(a));
	assertEqualIntA(a, ARCHIVE_OK, archive_write_add_filter_none(a));
	assertEqualIntA(a, ARCHIVE_OK,
	    archive_write_open_memory(a, buff, buffsize, &used));

	/*
	 * Write an empty file to it.
	 */
	assert((ae = archive_entry_new()) != NULL);
	archive_entry_set_mtime(ae, 1, 10);
	assertEqualInt(1, archive_entry_mtime(ae));
	assertEqualInt(10, archive_entry_mtime_nsec(ae));
	archive_entry_set_atime(ae, 2, 20);
	assertEqualInt(2, archive_entry_atime(ae));
	assertEqualInt(20, archive_entry_atime_nsec(ae));
	archive_entry_set_ctime(ae, 0, 100);
	assertEqualInt(0, archive_entry_ctime(ae));
	assertEqualInt(100, archive_entry_ctime_nsec(ae));
	archive_entry_copy_pathname(ae, "empty");
	assertEqualString("empty", archive_entry_pathname(ae));
	archive_entry_set_mode(ae, AE_IFREG | 0755);
	assertEqualInt((S_IFREG | 0755), archive_entry_mode(ae));

	assertEqualInt(ARCHIVE_OK, archive_write_header(a, ae));
	archive_entry_free(ae);

	/* Close out the archive. */
	assertEqualInt(ARCHIVE_OK, archive_write_close(a));
	assertEqualInt(ARCHIVE_OK, archive_write_free(a));

	/* Verify the archive file size. */
	assertEqualInt(102, used);

	/* Verify the initial header. */
	assertEqualMem(buff,
		"\x37\x7a\xbc\xaf\x27\x1c\x00\x03"
		"\x00\x5b\x58\x25\x00\x00\x00\x00"
		"\x00\x00\x00\x00\x46\x00\x00\x00"
		"\x00\x00\x00\x00\x8f\xce\x1d\xf3", 32);

	/*
	 * Now, read the data back.
	 */
	/* With the test memory reader -- seeking mode. */
	assert((a = archive_read_new()) != NULL);
	assertEqualIntA(a, ARCHIVE_OK, archive_read_support_format_all(a));
	assertEqualIntA(a, ARCHIVE_OK, archive_read_support_filter_all(a));
	assertEqualIntA(a, ARCHIVE_OK, read_open_memory_seek(a, buff, used, 7));

	/*
	 * Read and verify an empty file.
	 */
	assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header(a, &ae));
	assertEqualInt(1, archive_entry_mtime(ae));
	assertEqualInt(0, archive_entry_mtime_nsec(ae));
	assertEqualInt(2, archive_entry_atime(ae));
	assertEqualInt(0, archive_entry_atime_nsec(ae));
	assertEqualInt(0, archive_entry_ctime(ae));
	assertEqualInt(100, archive_entry_ctime_nsec(ae));
	assertEqualString("empty", archive_entry_pathname(ae));
	assertEqualInt(AE_IFREG | 0755, archive_entry_mode(ae));
	assertEqualInt(0, archive_entry_size(ae));

	/* Verify the end of the archive. */
	assertEqualIntA(a, ARCHIVE_EOF, archive_read_next_header(a, &ae));

	/* Verify archive format. */
	assertEqualIntA(a, ARCHIVE_FILTER_NONE, archive_filter_code(a, 0));
	assertEqualIntA(a, ARCHIVE_FORMAT_7ZIP, archive_format(a));

	assertEqualInt(ARCHIVE_OK, archive_read_close(a));
	assertEqualInt(ARCHIVE_OK, archive_read_free(a));

	free(buff);
}