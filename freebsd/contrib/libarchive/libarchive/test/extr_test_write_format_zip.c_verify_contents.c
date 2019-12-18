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
typedef  int /*<<< orphan*/  filedata ;

/* Variables and functions */
 int AE_IFDIR ; 
 int AE_IFLNK ; 
 int AE_IFREG ; 
 int ARCHIVE_EOF ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  archive_entry_atime (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_ctime (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_mode (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_mtime (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_mtime_nsec (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_pathname (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_size (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_size_is_set (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_symlink (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_read_close (struct archive*) ; 
 int /*<<< orphan*/  archive_read_data (struct archive*,char*,int) ; 
 int /*<<< orphan*/  archive_read_free (struct archive*) ; 
 int /*<<< orphan*/  archive_read_next_header (struct archive*,struct archive_entry**) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualInt (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualIntA (struct archive*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assertEqualMem (char*,char*,int) ; 
 int /*<<< orphan*/  assertEqualString (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
verify_contents(struct archive *a, int seeking, int content)
{
	char filedata[64];
	struct archive_entry *ae;

	/*
	 * Default compression options:
	 */

	/* Read and verify first file. */
	assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header(a, &ae));
	assertEqualInt(1, archive_entry_mtime(ae));
	/* Zip doesn't store high-resolution mtime. */
	assertEqualInt(0, archive_entry_mtime_nsec(ae));
	assertEqualInt(0, archive_entry_atime(ae));
	assertEqualInt(0, archive_entry_ctime(ae));
	assertEqualString("file", archive_entry_pathname(ae));
	if (seeking) {
		assertEqualInt(AE_IFREG | 0755, archive_entry_mode(ae));
	}
	assert(archive_entry_size_is_set(ae));
	assertEqualInt(8, archive_entry_size(ae));
	if (content) {
		assertEqualIntA(a, 8,
		    archive_read_data(a, filedata, sizeof(filedata)));
		assertEqualMem(filedata, "12345678", 8);
	}

	/* Read the second file back. */
	assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header(a, &ae));
	assertEqualInt(1, archive_entry_mtime(ae));
	assertEqualInt(0, archive_entry_mtime_nsec(ae));
	assertEqualInt(0, archive_entry_atime(ae));
	assertEqualInt(0, archive_entry_ctime(ae));
	assertEqualString("file2", archive_entry_pathname(ae));
	if (seeking) {
		assertEqualInt(AE_IFREG | 0755, archive_entry_mode(ae));
	}
	assertEqualInt(4, archive_entry_size(ae));
	assert(archive_entry_size_is_set(ae));
	if (content) {
		assertEqualIntA(a, 4,
		    archive_read_data(a, filedata, sizeof(filedata)));
		assertEqualMem(filedata, "1234", 4);
	}

	/* Read the third file back. */
	assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header(a, &ae));
	assertEqualInt(2, archive_entry_mtime(ae));
	assertEqualInt(0, archive_entry_mtime_nsec(ae));
	assertEqualInt(0, archive_entry_atime(ae));
	assertEqualInt(0, archive_entry_ctime(ae));
	assertEqualString("file3", archive_entry_pathname(ae));
	if (seeking) {
		assertEqualInt(5, archive_entry_size(ae));
		assertEqualInt(AE_IFREG | 0621, archive_entry_mode(ae));
	} else {
		assertEqualInt(0, archive_entry_size_is_set(ae));
	}
	if (content) {
		assertEqualIntA(a, 5,
		    archive_read_data(a, filedata, sizeof(filedata)));
		assertEqualMem(filedata, "mnopq", 5);
	}

	/* Read symlink. */
	assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header(a, &ae));
	assertEqualInt(1, archive_entry_mtime(ae));
	assertEqualInt(0, archive_entry_mtime_nsec(ae));
	assertEqualInt(0, archive_entry_atime(ae));
	assertEqualInt(0, archive_entry_ctime(ae));
	assertEqualString("symlink", archive_entry_pathname(ae));
	assertEqualInt(AE_IFLNK | 0755, archive_entry_mode(ae));
	assertEqualInt(0, archive_entry_size(ae));
	assertEqualString("file1", archive_entry_symlink(ae));

	/* Read the dir entry back. */
	assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header(a, &ae));
	assertEqualInt(11, archive_entry_mtime(ae));
	assertEqualInt(0, archive_entry_mtime_nsec(ae));
	assertEqualInt(0, archive_entry_atime(ae));
	assertEqualInt(0, archive_entry_ctime(ae));
	assertEqualString("dir/", archive_entry_pathname(ae));
	if (seeking)
		assertEqualInt(AE_IFDIR | 0755, archive_entry_mode(ae));
	assertEqualInt(0, archive_entry_size(ae));
	if (content) {
		assertEqualIntA(a, 0, archive_read_data(a, filedata, 10));
	}

#ifdef HAVE_ZLIB_H
	/*
	 * Deflate compression option:
	 */

	/* Read and verify first file. */
	assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header(a, &ae));
	assertEqualInt(1, archive_entry_mtime(ae));
	/* Zip doesn't store high-resolution mtime. */
	assertEqualInt(0, archive_entry_mtime_nsec(ae));
	assertEqualInt(0, archive_entry_atime(ae));
	assertEqualInt(0, archive_entry_ctime(ae));
	assertEqualString("file_deflate", archive_entry_pathname(ae));
	if (seeking)
		assertEqualInt(AE_IFREG | 0755, archive_entry_mode(ae));
	assertEqualInt(8, archive_entry_size(ae));
	assert(archive_entry_size_is_set(ae));
	if (content) {
		assertEqualIntA(a, 8,
		    archive_read_data(a, filedata, sizeof(filedata)));
		assertEqualMem(filedata, "12345678", 8);
	}


	/* Read the second file back. */
	assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header(a, &ae));
	assertEqualInt(1, archive_entry_mtime(ae));
	assertEqualInt(0, archive_entry_mtime_nsec(ae));
	assertEqualInt(0, archive_entry_atime(ae));
	assertEqualInt(0, archive_entry_ctime(ae));
	assertEqualString("file2_deflate", archive_entry_pathname(ae));
	if (seeking)
		assertEqualInt(AE_IFREG | 0755, archive_entry_mode(ae));
	assertEqualInt(4, archive_entry_size(ae));
	assert(archive_entry_size_is_set(ae));
	if (content) {
		assertEqualIntA(a, 4,
		    archive_read_data(a, filedata, sizeof(filedata)));
		assertEqualMem(filedata, "1234", 4);
	}

	/* Read the third file back. */
	assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header(a, &ae));
	assertEqualInt(2, archive_entry_mtime(ae));
	assertEqualInt(0, archive_entry_mtime_nsec(ae));
	assertEqualInt(0, archive_entry_atime(ae));
	assertEqualInt(0, archive_entry_ctime(ae));
	assertEqualString("file3_deflate", archive_entry_pathname(ae));
	if (seeking) {
		assertEqualInt(5, archive_entry_size(ae));
		assertEqualInt(AE_IFREG | 0621, archive_entry_mode(ae));
	} else {
		assertEqualInt(0, archive_entry_size_is_set(ae));
	}
	if (content) {
		assertEqualIntA(a, 5,
		    archive_read_data(a, filedata, sizeof(filedata)));
		assertEqualMem(filedata, "ghijk", 4);
	}

	/* Read symlink. */
	assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header(a, &ae));
	assertEqualInt(1, archive_entry_mtime(ae));
	assertEqualInt(0, archive_entry_mtime_nsec(ae));
	assertEqualInt(0, archive_entry_atime(ae));
	assertEqualInt(0, archive_entry_ctime(ae));
	assertEqualString("symlink_deflate", archive_entry_pathname(ae));
	assertEqualInt(AE_IFLNK | 0755, archive_entry_mode(ae));
	assertEqualInt(0, archive_entry_size(ae));
	assertEqualString("file1", archive_entry_symlink(ae));

	/* Read the dir entry back. */
	assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header(a, &ae));
	assertEqualInt(11, archive_entry_mtime(ae));
	assertEqualInt(0, archive_entry_mtime_nsec(ae));
	assertEqualInt(0, archive_entry_atime(ae));
	assertEqualInt(0, archive_entry_ctime(ae));
	assertEqualString("dir_deflate/", archive_entry_pathname(ae));
	if (seeking) {
		assertEqualInt(AE_IFDIR | 0755, archive_entry_mode(ae));
	}
	assertEqualInt(0, archive_entry_size(ae));
	if (content) {
		assertEqualIntA(a, 0, archive_read_data(a, filedata, 10));
	}
#endif

	/*
	 * Store compression option:
	 */

	/* Read and verify first file. */
	assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header(a, &ae));
	assertEqualInt(1, archive_entry_mtime(ae));
	/* Zip doesn't store high-resolution mtime. */
	assertEqualInt(0, archive_entry_mtime_nsec(ae));
	assertEqualInt(0, archive_entry_atime(ae));
	assertEqualInt(0, archive_entry_ctime(ae));
	assertEqualString("file_stored", archive_entry_pathname(ae));
	if (seeking)
		assertEqualInt(AE_IFREG | 0755, archive_entry_mode(ae));
	assert(archive_entry_size_is_set(ae));
	assertEqualInt(8, archive_entry_size(ae));
	if (content) {
		assertEqualIntA(a, 8,
		    archive_read_data(a, filedata, sizeof(filedata)));
		assertEqualMem(filedata, "12345678", 8);
	}


	/* Read the second file back. */
	assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header(a, &ae));
	assertEqualInt(1, archive_entry_mtime(ae));
	assertEqualInt(0, archive_entry_mtime_nsec(ae));
	assertEqualInt(0, archive_entry_atime(ae));
	assertEqualInt(0, archive_entry_ctime(ae));
	assertEqualString("file2_stored", archive_entry_pathname(ae));
	if (seeking)
		assertEqualInt(AE_IFREG | 0755, archive_entry_mode(ae));
	assertEqualInt(4, archive_entry_size(ae));
	assert(archive_entry_size_is_set(ae));
	if (content) {
		assertEqualIntA(a, 4,
		    archive_read_data(a, filedata, sizeof(filedata)));
		assertEqualMem(filedata, "ACEG", 4);
	}

	/* Read the third file back. */
	assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header(a, &ae));
	assertEqualInt(2, archive_entry_mtime(ae));
	assertEqualInt(0, archive_entry_mtime_nsec(ae));
	assertEqualInt(0, archive_entry_atime(ae));
	assertEqualInt(0, archive_entry_ctime(ae));
	assertEqualString("file3_stored", archive_entry_pathname(ae));
	if (seeking) {
		assertEqualInt(5, archive_entry_size(ae));
		assertEqualInt(AE_IFREG | 0621, archive_entry_mode(ae));
	} else {
		assertEqualInt(0, archive_entry_size_is_set(ae));
	}
	if (content) {
		assertEqualIntA(a, 5,
		    archive_read_data(a, filedata, sizeof(filedata)));
		assertEqualMem(filedata, "ijklm", 4);
	}

	/* Read symlink. */
	assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header(a, &ae));
	assertEqualInt(1, archive_entry_mtime(ae));
	assertEqualInt(0, archive_entry_mtime_nsec(ae));
	assertEqualInt(0, archive_entry_atime(ae));
	assertEqualInt(0, archive_entry_ctime(ae));
	assertEqualString("symlink_stored", archive_entry_pathname(ae));
	assertEqualInt(AE_IFLNK | 0755, archive_entry_mode(ae));
	assertEqualInt(0, archive_entry_size(ae));
	assertEqualString("file1", archive_entry_symlink(ae));

	/* Read the dir entry back. */
	assertEqualIntA(a, ARCHIVE_OK, archive_read_next_header(a, &ae));
	assertEqualInt(11, archive_entry_mtime(ae));
	assertEqualInt(0, archive_entry_mtime_nsec(ae));
	assertEqualInt(0, archive_entry_atime(ae));
	assertEqualInt(0, archive_entry_ctime(ae));
	assertEqualString("dir_stored/", archive_entry_pathname(ae));
	if (seeking)
		assertEqualInt(AE_IFDIR | 0755, archive_entry_mode(ae));
	assertEqualInt(0, archive_entry_size(ae));
	if (content) {
		assertEqualIntA(a, 0, archive_read_data(a, filedata, 10));
	}

	/* Verify the end of the archive. */
	assertEqualIntA(a, ARCHIVE_EOF, archive_read_next_header(a, &ae));
	assertEqualInt(ARCHIVE_OK, archive_read_close(a));
	assertEqualInt(ARCHIVE_OK, archive_read_free(a));
}