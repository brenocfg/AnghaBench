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
typedef  int /*<<< orphan*/  buff ;

/* Variables and functions */
 int ARCHIVE_FAILED ; 
 int ARCHIVE_OK ; 
 int S_IFDIR ; 
 int S_IFREG ; 
 int /*<<< orphan*/  archive_entry_copy_pathname (struct archive_entry*,char*) ; 
 int /*<<< orphan*/  archive_entry_free (struct archive_entry*) ; 
 int archive_entry_mode (struct archive_entry*) ; 
 struct archive_entry* archive_entry_new () ; 
 int /*<<< orphan*/  archive_entry_pathname (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_set_mode (struct archive_entry*,int) ; 
 int /*<<< orphan*/  archive_read_close (struct archive*) ; 
 scalar_t__ archive_read_free (struct archive*) ; 
 struct archive* archive_read_new () ; 
 scalar_t__ archive_read_next_header (struct archive*,struct archive_entry**) ; 
 scalar_t__ archive_read_open_memory (struct archive*,char*,size_t) ; 
 scalar_t__ archive_read_support_filter_all (struct archive*) ; 
 scalar_t__ archive_read_support_format_all (struct archive*) ; 
 scalar_t__ archive_write_add_filter_none (struct archive*) ; 
 int /*<<< orphan*/  archive_write_close (struct archive*) ; 
 scalar_t__ archive_write_free (struct archive*) ; 
 int /*<<< orphan*/  archive_write_header (struct archive*,struct archive_entry*) ; 
 struct archive* archive_write_new () ; 
 scalar_t__ archive_write_open_memory (struct archive*,char*,int,size_t*) ; 
 scalar_t__ archive_write_set_bytes_per_block (struct archive*,int /*<<< orphan*/ ) ; 
 scalar_t__ archive_write_set_format_ustar (struct archive*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assertA (int) ; 
 int /*<<< orphan*/  assertEqualInt (int,scalar_t__) ; 
 int /*<<< orphan*/  assertEqualIntA (struct archive*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualString (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  failure (char*,int,int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static void
test_filename(const char *prefix, int dlen, int flen)
{
	char buff[8192];
	char filename[400];
	char dirname[400];
	struct archive_entry *ae;
	struct archive *a;
	size_t used;
	int separator = 0;
	int i = 0;

	if (prefix != NULL) {
		strcpy(filename, prefix);
		i = (int)strlen(prefix);
	}
	if (dlen > 0) {
		for (; i < dlen; i++)
			filename[i] = 'a';
		filename[i++] = '/';
		separator = 1;
	}
	for (; i < dlen + flen + separator; i++)
		filename[i] = 'b';
	filename[i] = '\0';

	strcpy(dirname, filename);

	/* Create a new archive in memory. */
	assert((a = archive_write_new()) != NULL);
	assertA(0 == archive_write_set_format_ustar(a));
	assertA(0 == archive_write_add_filter_none(a));
	assertA(0 == archive_write_set_bytes_per_block(a,0));
	assertA(0 == archive_write_open_memory(a, buff, sizeof(buff), &used));

	/*
	 * Write a file to it.
	 */
	assert((ae = archive_entry_new()) != NULL);
	archive_entry_copy_pathname(ae, filename);
	archive_entry_set_mode(ae, S_IFREG | 0755);
	failure("dlen=%d, flen=%d", dlen, flen);
	if (flen > 100) {
		assertEqualIntA(a, ARCHIVE_FAILED, archive_write_header(a, ae));
	} else {
		assertEqualIntA(a, 0, archive_write_header(a, ae));
	}
	archive_entry_free(ae);

	/*
	 * Write a dir to it (without trailing '/').
	 */
	assert((ae = archive_entry_new()) != NULL);
	archive_entry_copy_pathname(ae, dirname);
	archive_entry_set_mode(ae, S_IFDIR | 0755);
	failure("dlen=%d, flen=%d", dlen, flen);
	if (flen >= 100) {
		assertEqualIntA(a, ARCHIVE_FAILED, archive_write_header(a, ae));
	} else {
		assertEqualIntA(a, 0, archive_write_header(a, ae));
	}
	archive_entry_free(ae);

	/* Tar adds a '/' to directory names. */
	strcat(dirname, "/");

	/*
	 * Write a dir to it (with trailing '/').
	 */
	assert((ae = archive_entry_new()) != NULL);
	archive_entry_copy_pathname(ae, dirname);
	archive_entry_set_mode(ae, S_IFDIR | 0755);
	failure("dlen=%d, flen=%d", dlen, flen);
	if (flen >= 100) {
		assertEqualIntA(a, ARCHIVE_FAILED, archive_write_header(a, ae));
	} else {
		assertEqualIntA(a, 0, archive_write_header(a, ae));
	}
	archive_entry_free(ae);

	/* Close out the archive. */
	assertEqualIntA(a, ARCHIVE_OK, archive_write_close(a));
	assertEqualInt(ARCHIVE_OK, archive_write_free(a));

	/*
	 * Now, read the data back.
	 */
	assert((a = archive_read_new()) != NULL);
	assertA(0 == archive_read_support_format_all(a));
	assertA(0 == archive_read_support_filter_all(a));
	assertA(0 == archive_read_open_memory(a, buff, used));

	if (flen <= 100) {
		/* Read the file and check the filename. */
		assertA(0 == archive_read_next_header(a, &ae));
		failure("dlen=%d, flen=%d", dlen, flen);
		assertEqualString(filename, archive_entry_pathname(ae));
		assertEqualInt((S_IFREG | 0755), archive_entry_mode(ae));
	}

	/*
	 * Read the two dirs and check the names.
	 *
	 * Both dirs should read back with the same name, since
	 * tar should add a trailing '/' to any dir that doesn't
	 * already have one.
	 */
	if (flen <= 99) {
		assertA(0 == archive_read_next_header(a, &ae));
		assert((S_IFDIR | 0755) == archive_entry_mode(ae));
		failure("dlen=%d, flen=%d", dlen, flen);
		assertEqualString(dirname, archive_entry_pathname(ae));
	}

	if (flen <= 99) {
		assertA(0 == archive_read_next_header(a, &ae));
		assert((S_IFDIR | 0755) == archive_entry_mode(ae));
		assertEqualString(dirname, archive_entry_pathname(ae));
	}

	/* Verify the end of the archive. */
	failure("This fails if entries were written that should not have been written.  dlen=%d, flen=%d", dlen, flen);
	assertEqualInt(1, archive_read_next_header(a, &ae));
	assertEqualIntA(a, ARCHIVE_OK, archive_read_close(a));
	assertEqualInt(ARCHIVE_OK, archive_read_free(a));
}