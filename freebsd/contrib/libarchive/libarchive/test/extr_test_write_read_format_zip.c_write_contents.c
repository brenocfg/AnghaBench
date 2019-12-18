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
 int AE_IFLNK ; 
 int AE_IFREG ; 
 int ARCHIVE_OK ; 
 int S_IFDIR ; 
 int /*<<< orphan*/  archive_entry_copy_pathname (struct archive_entry*,char*) ; 
 int /*<<< orphan*/  archive_entry_copy_symlink (struct archive_entry*,char*) ; 
 int /*<<< orphan*/  archive_entry_free (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_mode (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_mtime (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_mtime_nsec (struct archive_entry*) ; 
 struct archive_entry* archive_entry_new () ; 
 int /*<<< orphan*/  archive_entry_pathname (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_set_mode (struct archive_entry*,int) ; 
 int /*<<< orphan*/  archive_entry_set_mtime (struct archive_entry*,int,int) ; 
 int /*<<< orphan*/  archive_entry_set_size (struct archive_entry*,int) ; 
 int /*<<< orphan*/  archive_entry_size (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_symlink (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_unset_size (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_write_close (struct archive*) ; 
 int /*<<< orphan*/  archive_write_data (struct archive*,char*,int) ; 
 int /*<<< orphan*/  archive_write_finish_entry (struct archive*) ; 
 int /*<<< orphan*/  archive_write_free (struct archive*) ; 
 int /*<<< orphan*/  archive_write_header (struct archive*,struct archive_entry*) ; 
 int /*<<< orphan*/  archive_write_zip_set_compression_deflate (struct archive*) ; 
 int /*<<< orphan*/  archive_write_zip_set_compression_store (struct archive*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualInt (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualIntA (struct archive*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualString (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  failure (char*) ; 

__attribute__((used)) static void
write_contents(struct archive *a)
{
	struct archive_entry *ae;

	/*
	 * First write things with the "default" compression.
	 * The library will choose "deflate" for most things if it's
	 * available, else "store".
	 */

	/*
	 * Write a file to it.
	 */
	assert((ae = archive_entry_new()) != NULL);
	archive_entry_set_mtime(ae, 1, 10);
	archive_entry_copy_pathname(ae, "file");
	archive_entry_set_mode(ae, AE_IFREG | 0755);
	archive_entry_set_size(ae, 8);
	assertEqualInt(0, archive_write_header(a, ae));
	archive_entry_free(ae);
	assertEqualInt(8, archive_write_data(a, "12345678", 9));
	assertEqualInt(0, archive_write_data(a, "1", 1));

	/*
	 * Write another file to it.
	 */
	assert((ae = archive_entry_new()) != NULL);
	archive_entry_set_mtime(ae, 1, 10);
	archive_entry_copy_pathname(ae, "file2");
	archive_entry_set_mode(ae, AE_IFREG | 0755);
	archive_entry_set_size(ae, 4);
	assertEqualInt(ARCHIVE_OK, archive_write_header(a, ae));
	archive_entry_free(ae);
	assertEqualInt(4, archive_write_data(a, "1234", 4));

	/*
	 * Write a file with an unknown size.
	 */
	assert((ae = archive_entry_new()) != NULL);
	archive_entry_set_mtime(ae, 2, 15);
	archive_entry_copy_pathname(ae, "file3");
	archive_entry_set_mode(ae, AE_IFREG | 0621);
	archive_entry_unset_size(ae);
	assertEqualInt(ARCHIVE_OK, archive_write_header(a, ae));
	archive_entry_free(ae);
	assertEqualInt(5, archive_write_data(a, "mnopq", 5));

	/*
	 * Write symbolic link.
	 */
	assert((ae = archive_entry_new()) != NULL);
	archive_entry_set_mtime(ae, 1, 10);
	assertEqualInt(1, archive_entry_mtime(ae));
	assertEqualInt(10, archive_entry_mtime_nsec(ae));
	archive_entry_copy_pathname(ae, "symlink");
	assertEqualString("symlink", archive_entry_pathname(ae));
	archive_entry_copy_symlink(ae, "file1");
	assertEqualString("file1", archive_entry_symlink(ae));
	archive_entry_set_mode(ae, AE_IFLNK | 0755);
	assertEqualInt((AE_IFLNK | 0755), archive_entry_mode(ae));
	archive_entry_set_size(ae, 4);

	assertEqualInt(ARCHIVE_OK, archive_write_header(a, ae));
	archive_entry_free(ae);

	/*
	 * Write a directory to it.
	 */
	assert((ae = archive_entry_new()) != NULL);
	archive_entry_set_mtime(ae, 11, 110);
	archive_entry_copy_pathname(ae, "dir");
	archive_entry_set_mode(ae, S_IFDIR | 0755);
	archive_entry_set_size(ae, 512);
	assertEqualIntA(a, ARCHIVE_OK, archive_write_header(a, ae));
	failure("size should be zero so that applications know not to write");
	assertEqualInt(0, archive_entry_size(ae));
	archive_entry_free(ae);
	assertEqualIntA(a, 0, archive_write_data(a, "12345678", 9));

	/*
	 * Force "deflate" compression if the platform supports it.
	 */
#ifdef HAVE_ZLIB_H
	assertEqualIntA(a, ARCHIVE_OK, archive_write_zip_set_compression_deflate(a));

	/*
	 * Write a file to it.
	 */
	assert((ae = archive_entry_new()) != NULL);
	archive_entry_set_mtime(ae, 1, 10);
	archive_entry_copy_pathname(ae, "file_deflate");
	archive_entry_set_mode(ae, AE_IFREG | 0755);
	archive_entry_set_size(ae, 8);
	assertEqualIntA(a, ARCHIVE_OK, archive_write_header(a, ae));
	archive_entry_free(ae);
	assertEqualInt(8, archive_write_data(a, "12345678", 9));
	assertEqualInt(0, archive_write_data(a, "1", 1));

	/*
	 * Write another file to it.
	 */
	assert((ae = archive_entry_new()) != NULL);
	archive_entry_set_mtime(ae, 1, 10);
	archive_entry_copy_pathname(ae, "file2_deflate");
	archive_entry_set_mode(ae, AE_IFREG | 0755);
	archive_entry_set_size(ae, 4);
	assertEqualIntA(a, ARCHIVE_OK, archive_write_header(a, ae));
	archive_entry_free(ae);
	assertEqualInt(4, archive_write_data(a, "1234", 4));

	/*
	 * Write a file with an unknown size.
	 */
	assert((ae = archive_entry_new()) != NULL);
	archive_entry_set_mtime(ae, 2, 15);
	archive_entry_copy_pathname(ae, "file3_deflate");
	archive_entry_set_mode(ae, AE_IFREG | 0621);
	archive_entry_unset_size(ae);
	assertEqualInt(ARCHIVE_OK, archive_write_header(a, ae));
	archive_entry_free(ae);
	assertEqualInt(5, archive_write_data(a, "ghijk", 5));

	/*
	 * Write symbolic like file to it.
	 */
	assert((ae = archive_entry_new()) != NULL);
	archive_entry_set_mtime(ae, 1, 10);
	archive_entry_copy_pathname(ae, "symlink_deflate");
	archive_entry_copy_symlink(ae, "file1");
	archive_entry_set_mode(ae, AE_IFLNK | 0755);
	archive_entry_set_size(ae, 4);
	assertEqualInt(ARCHIVE_OK, archive_write_header(a, ae));
	archive_entry_free(ae);

	/*
	 * Write a directory to it.
	 */
	assert((ae = archive_entry_new()) != NULL);
	archive_entry_set_mtime(ae, 11, 110);
	archive_entry_copy_pathname(ae, "dir_deflate");
	archive_entry_set_mode(ae, S_IFDIR | 0755);
	archive_entry_set_size(ae, 512);
	assertEqualIntA(a, ARCHIVE_OK, archive_write_header(a, ae));
	failure("size should be zero so that applications know not to write");
	assertEqualInt(0, archive_entry_size(ae));
	archive_entry_free(ae);
	assertEqualIntA(a, 0, archive_write_data(a, "12345678", 9));
	assertEqualIntA(a, ARCHIVE_OK, archive_write_finish_entry(a));
#endif

	/*
	 * Now write a bunch of entries with "store" compression.
	 */
	assertEqualIntA(a, ARCHIVE_OK, archive_write_zip_set_compression_store(a));

	/*
	 * Write a file to it.
	 */
	assert((ae = archive_entry_new()) != NULL);
	archive_entry_set_mtime(ae, 1, 10);
	archive_entry_copy_pathname(ae, "file_stored");
	archive_entry_set_mode(ae, AE_IFREG | 0755);
	archive_entry_set_size(ae, 8);
	assertEqualInt(0, archive_write_header(a, ae));
	archive_entry_free(ae);
	assertEqualInt(8, archive_write_data(a, "12345678", 9));
	assertEqualInt(0, archive_write_data(a, "1", 1));

	/*
	 * Write another file to it.
	 */
	assert((ae = archive_entry_new()) != NULL);
	archive_entry_set_mtime(ae, 1, 10);
	archive_entry_copy_pathname(ae, "file2_stored");
	archive_entry_set_mode(ae, AE_IFREG | 0755);
	archive_entry_set_size(ae, 4);
	assertEqualInt(ARCHIVE_OK, archive_write_header(a, ae));
	archive_entry_free(ae);
	assertEqualInt(4, archive_write_data(a, "ACEG", 4));

	/*
	 * Write a file with an unknown size.
	 */
	assert((ae = archive_entry_new()) != NULL);
	archive_entry_set_mtime(ae, 2, 15);
	archive_entry_copy_pathname(ae, "file3_stored");
	archive_entry_set_mode(ae, AE_IFREG | 0621);
	archive_entry_unset_size(ae);
	assertEqualInt(ARCHIVE_OK, archive_write_header(a, ae));
	archive_entry_free(ae);
	assertEqualInt(5, archive_write_data(a, "ijklm", 5));

	/*
	 * Write symbolic like file to it.
	 */
	assert((ae = archive_entry_new()) != NULL);
	archive_entry_set_mtime(ae, 1, 10);
	archive_entry_copy_pathname(ae, "symlink_stored");
	archive_entry_copy_symlink(ae, "file1");
	archive_entry_set_mode(ae, AE_IFLNK | 0755);
	archive_entry_set_size(ae, 4);
	assertEqualInt(ARCHIVE_OK, archive_write_header(a, ae));
	archive_entry_free(ae);

	/*
	 * Write a directory to it.
	 */
	assert((ae = archive_entry_new()) != NULL);
	archive_entry_set_mtime(ae, 11, 110);
	archive_entry_copy_pathname(ae, "dir_stored");
	archive_entry_set_mode(ae, S_IFDIR | 0755);
	archive_entry_set_size(ae, 512);
	assertEqualIntA(a, ARCHIVE_OK, archive_write_header(a, ae));
	failure("size should be zero so that applications know not to write");
	assertEqualInt(0, archive_entry_size(ae));
	archive_entry_free(ae);
	assertEqualIntA(a, 0, archive_write_data(a, "12345678", 9));


	/* Close out the archive. */
	assertEqualInt(ARCHIVE_OK, archive_write_close(a));
	assertEqualInt(ARCHIVE_OK, archive_write_free(a));
}