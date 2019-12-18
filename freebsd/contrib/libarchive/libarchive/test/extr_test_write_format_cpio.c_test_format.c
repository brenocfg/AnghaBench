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
typedef  struct archive archive ;

/* Variables and functions */
 int /*<<< orphan*/  AE_IFREG ; 
 int ARCHIVE_FAILED ; 
 int ARCHIVE_OK ; 
 int ARCHIVE_WARN ; 
 int S_IFDIR ; 
 int S_IFREG ; 
 scalar_t__ archive_entry_atime (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_copy_pathname (struct archive_entry*,char*) ; 
 scalar_t__ archive_entry_ctime (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_free (struct archive_entry*) ; 
 scalar_t__ archive_entry_mode (struct archive_entry*) ; 
 scalar_t__ archive_entry_mtime (struct archive_entry*) ; 
 int archive_entry_mtime_nsec (struct archive_entry*) ; 
 struct archive_entry* archive_entry_new () ; 
 int /*<<< orphan*/  archive_entry_pathname (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_set_filetype (struct archive_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_set_mode (struct archive_entry*,int) ; 
 int /*<<< orphan*/  archive_entry_set_mtime (struct archive_entry*,int,int) ; 
 int /*<<< orphan*/  archive_entry_set_size (struct archive_entry*,int) ; 
 scalar_t__ archive_entry_size (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_unset_size (struct archive_entry*) ; 
 int /*<<< orphan*/ * archive_error_string (struct archive*) ; 
 int archive_read_close (struct archive*) ; 
 int archive_read_data (struct archive*,char*,int) ; 
 scalar_t__ archive_read_free (struct archive*) ; 
 struct archive* archive_read_new () ; 
 int archive_read_next_header (struct archive*,struct archive_entry**) ; 
 scalar_t__ archive_read_open_memory (struct archive*,char*,size_t) ; 
 scalar_t__ archive_read_support_filter_all (struct archive*) ; 
 scalar_t__ archive_read_support_format_all (struct archive*) ; 
 scalar_t__ archive_write_add_filter_none (struct archive*) ; 
 int archive_write_close (struct archive*) ; 
 int archive_write_data (struct archive*,char*,int) ; 
 scalar_t__ archive_write_free (struct archive*) ; 
 scalar_t__ archive_write_header (struct archive*,struct archive_entry*) ; 
 struct archive* archive_write_new () ; 
 scalar_t__ archive_write_open_memory (struct archive*,char*,size_t,size_t*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assertA (int) ; 
 int /*<<< orphan*/  assertEqualInt (int,scalar_t__) ; 
 int /*<<< orphan*/  assertEqualIntA (struct archive*,int,int) ; 
 int /*<<< orphan*/  assertEqualMem (char*,char*,int) ; 
 int /*<<< orphan*/  assertEqualString (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  failure (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 char* strdup (char*) ; 
 int stub1 (struct archive*) ; 

__attribute__((used)) static void
test_format(int	(*set_format)(struct archive *))
{
	char filedata[64];
	struct archive_entry *ae;
	struct archive *a;
	char *p;
	size_t used;
	size_t buffsize = 1000000;
	char *buff;
	int damaged = 0;

	buff = malloc(buffsize);

	/* Create a new archive in memory. */
	assert((a = archive_write_new()) != NULL);
	assertA(0 == (*set_format)(a));
	assertA(0 == archive_write_add_filter_none(a));
	assertA(0 == archive_write_open_memory(a, buff, buffsize, &used));

	/*
	 * Write a file to it.
	 */
	assert((ae = archive_entry_new()) != NULL);
	archive_entry_set_mtime(ae, 1, 10);
	assert(1 == archive_entry_mtime(ae));
	assert(10 == archive_entry_mtime_nsec(ae));
	p = strdup("file");
	archive_entry_copy_pathname(ae, p);
	strcpy(p, "XXXX");
	free(p);
	assertEqualString("file", archive_entry_pathname(ae));
	archive_entry_set_mode(ae, S_IFREG | 0755);
	assert((S_IFREG | 0755) == archive_entry_mode(ae));
	archive_entry_set_size(ae, 8);

	assertA(0 == archive_write_header(a, ae));
	archive_entry_free(ae);
	assertA(8 == archive_write_data(a, "12345678", 9));

	/*
	 * Write another file to it.
	 */
	assert((ae = archive_entry_new()) != NULL);
	archive_entry_set_mtime(ae, 1, 10);
	assert(1 == archive_entry_mtime(ae));
	assert(10 == archive_entry_mtime_nsec(ae));
	p = strdup("file2");
	archive_entry_copy_pathname(ae, p);
	strcpy(p, "XXXX");
	free(p);
	assertEqualString("file2", archive_entry_pathname(ae));
	archive_entry_set_mode(ae, S_IFREG | 0755);
	assert((S_IFREG | 0755) == archive_entry_mode(ae));
	archive_entry_set_size(ae, 4);

	assertA(0 == archive_write_header(a, ae));
	archive_entry_free(ae);
	assertA(4 == archive_write_data(a, "1234", 5));

	/*
	 * Write a file with a name, filetype, and size.
	 */
	assert((ae = archive_entry_new()) != NULL);
	archive_entry_copy_pathname(ae, "name");
	archive_entry_set_size(ae, 0);
	archive_entry_set_filetype(ae, AE_IFREG);
	assertEqualInt(ARCHIVE_OK, archive_write_header(a, ae));
	assert(archive_error_string(a) == NULL);
	archive_entry_free(ae);

	/*
	 * Write a file with a name and filetype but no size.
	 */
	assert((ae = archive_entry_new()) != NULL);
	archive_entry_copy_pathname(ae, "name");
	archive_entry_unset_size(ae);
	archive_entry_set_filetype(ae, AE_IFREG);
	assertEqualInt(ARCHIVE_FAILED, archive_write_header(a, ae));
	assert(archive_error_string(a) != NULL);
	archive_entry_free(ae);

	/*
	 * Write a file with a name and size but no filetype.
	 */
	assert((ae = archive_entry_new()) != NULL);
	archive_entry_copy_pathname(ae, "name");
	archive_entry_set_size(ae, 0);
	assertEqualInt(ARCHIVE_FAILED, archive_write_header(a, ae));
	assert(archive_error_string(a) != NULL);
	archive_entry_free(ae);

	/*
	 * Write a file with a size and filetype but no name.
	 */
	assert((ae = archive_entry_new()) != NULL);
	archive_entry_set_size(ae, 0);
	archive_entry_set_filetype(ae, AE_IFREG);
	assertEqualInt(ARCHIVE_FAILED, archive_write_header(a, ae));
	assert(archive_error_string(a) != NULL);
	archive_entry_free(ae);

	/*
	 * Write a directory to it.
	 */
	assert((ae = archive_entry_new()) != NULL);
	archive_entry_set_mtime(ae, 11, 110);
	archive_entry_copy_pathname(ae, "dir");
	archive_entry_set_mode(ae, S_IFDIR | 0755);
	archive_entry_set_size(ae, 512);

	assertA(0 == archive_write_header(a, ae));
	assertEqualInt(0, archive_entry_size(ae));
	archive_entry_free(ae);
	assertEqualIntA(a, 0, archive_write_data(a, "12345678", 9));


	/* Close out the archive. */
	assertEqualIntA(a, ARCHIVE_OK, archive_write_close(a));
	assertEqualInt(ARCHIVE_OK, archive_write_free(a));

	/*
	 * Damage the second entry to test the search-ahead recovery.
	 * TODO: Move the damage-recovery checking to a separate test;
	 * it doesn't really belong in this write test.
	 */
	{
		int i;
		for (i = 80; i < 150; i++) {
			if (memcmp(buff + i, "07070", 5) == 0) {
				damaged = 1;
				buff[i] = 'X';
				break;
			}
		}
	}
	failure("Unable to locate the second header for damage-recovery test.");
	assert(damaged == 1);

	/*
	 * Now, read the data back.
	 */
	assert((a = archive_read_new()) != NULL);
	assertA(0 == archive_read_support_format_all(a));
	assertA(0 == archive_read_support_filter_all(a));
	assertA(0 == archive_read_open_memory(a, buff, used));

	if (!assertEqualIntA(a, 0, archive_read_next_header(a, &ae))) {
		archive_read_free(a);
		return;
	}

	assertEqualInt(1, archive_entry_mtime(ae));
	/* Not the same as above: cpio doesn't store hi-res times. */
	assert(0 == archive_entry_mtime_nsec(ae));
	assert(0 == archive_entry_atime(ae));
	assert(0 == archive_entry_ctime(ae));
	assertEqualString("file", archive_entry_pathname(ae));
	assertEqualInt((S_IFREG | 0755), archive_entry_mode(ae));
	assertEqualInt(8, archive_entry_size(ae));
	assertA(8 == archive_read_data(a, filedata, 10));
	assertEqualMem(filedata, "12345678", 8);

	/*
	 * The second file can't be read because we damaged its header.
	 */

	/*
	 * Read the third file back.
	 * ARCHIVE_WARN here because the damaged entry was skipped.
	 */
	assertEqualIntA(a, ARCHIVE_WARN, archive_read_next_header(a, &ae));
	assertEqualString("name", archive_entry_pathname(ae));

	/*
	 * Read the dir entry back.
	 */
	assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header(a, &ae));
	assertEqualInt(11, archive_entry_mtime(ae));
	assert(0 == archive_entry_mtime_nsec(ae));
	assert(0 == archive_entry_atime(ae));
	assert(0 == archive_entry_ctime(ae));
	assertEqualString("dir", archive_entry_pathname(ae));
	assertEqualInt((S_IFDIR | 0755), archive_entry_mode(ae));
	assertEqualInt(0, archive_entry_size(ae));
	assertEqualIntA(a, 0, archive_read_data(a, filedata, 10));

	/* Verify the end of the archive. */
	assertEqualIntA(a, 1, archive_read_next_header(a, &ae));
	assertEqualIntA(a, ARCHIVE_OK, archive_read_close(a));
	assertEqualInt(ARCHIVE_OK, archive_read_free(a));

	free(buff);
}